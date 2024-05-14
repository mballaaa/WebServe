#include "../../includes/Multiplex.hpp"

#include "../../includes/Request/Http_req.hpp"
#include "../../includes/Response/Response.hpp"
#include "../../includes/cgi/Cgi.hpp"
SOCKET Multiplex::epollFD;
Multiplex::listeners_t Multiplex::listeners;
Multiplex::requests_t Multiplex::requests;
Multiplex::response_t Multiplex::response;// For "JaQen" Response
Multiplex::epoll_event_t Multiplex::events[SOMAXCONN] = {};
Multiplex::host_port_map_t Multiplex::hostPortMap;

void Multiplex::setup(const servers_t &servers)
{
    
    if (servers.empty())
    {
        throw std::runtime_error("Servers are not set");
        return;
    }

    servers_t::const_iterator servIt = servers.begin();
    epollFD = SocketManager::createEpoll();
    while (servIt != servers.end())
    {
        SOCKET sfd;
        std::string id = servIt->getHost() + ":" + servIt->getPort();
        if (hostPortMap.find(id) != hostPortMap.end()) // host:port already binded
            sfd = hostPortMap[id];
        else // create new socket, bind, listen and add to epoll finally add it to hostPortMap
        {
            sfd = SocketManager::createSocket(*servIt, AF_INET, SOCK_STREAM, AI_PASSIVE);
            SocketManager::makeSocketNonBlocking(sfd);
            SocketManager::startListening(sfd);
            SocketManager::epollCtlSocket(sfd, EPOLL_CTL_ADD);
            hostPortMap.insert(std::make_pair(id, sfd));
        }
        listeners[sfd].push_back(*servIt);
        servIt++;
    }
}

void Multiplex::cleanAll(int eFD){
    delete requests[eFD] ;
    requests.erase(eFD) ;
    delete response[eFD] ;
    response.erase(eFD) ;
}
void Multiplex::start(void)
{
    int s;
    Http_req::initErrorTexts() ;
    while (1)
    {
        int eventCount = 0;
        eventCount = epoll_wait(epollFD, events, SOMAXCONN, -1); // Waiting for new event to occur
        for (int i = 0; i < eventCount; i++)
        {
            int eFD = events[i].data.fd ;
            if (listeners.find(eFD) == listeners.end() && (!requests[eFD] || !response[eFD]))
            {
                continue ;
            }
            if (events[i].events & EPOLLHUP)
            {
                delete requests[eFD] ;
                requests.erase(eFD) ;
                delete response[eFD] ;
                response.erase(eFD) ;
                continue;
            }
            else if (events[i].events & EPOLLOUT)
            {
                if (difftime(time(NULL), requests[eFD]->lastActive) > TIMEOUT)
                {
                    requests[eFD]->_status = 408 ;
                    if (requests[eFD]->fd > 0)
                        close(requests[eFD]->fd) ;
                    requests[eFD]->fd = open(requests[eFD]->getErrorPage().c_str(), O_RDWR) ;
                    unlink(requests[eFD]->make_name.c_str());
                    requests[eFD]->in_out = true ;
                }
            }
            if (listeners.find(eFD) != listeners.end()) // Check if socket belong to a server
            {
                struct sockaddr in_addr;
                socklen_t in_len;
                int infd;

                in_len = sizeof(in_addr);
                infd = accept(eFD, &in_addr, &in_len); // Accept connection
                if (!ISVALIDSOCKET(infd))
                {
                    if ((errno == EAGAIN) ||
                        (errno == EWOULDBLOCK))
                    {
                        /* We have processed all incoming
                            connections. */
                        continue;
                    }
                    else
                        continue;
                }
                SocketManager::makeSocketNonBlocking(infd);
                SocketManager::epollCtlSocket(infd, EPOLL_CTL_ADD);
                if (requests[infd])
                    delete requests[infd] ;
                if (response[infd])
                    delete response[infd] ;
                requests[infd] = new Http_req(listeners[eFD]);
                response[infd] = new Response(infd);
                continue;
            }
            else if (events[i].events & EPOLLIN  && requests[eFD]->getFlag() == false)   // check if we have EPOLLIN (connection socket ready to read)
            {
                requests[eFD]->lastActive = time(0) ;
                ssize_t bytesReceived;
                char buf[R_SIZE] = {0};

                bytesReceived = read(eFD, buf,  R_SIZE - 1);
                if (bytesReceived == -1 || bytesReceived == 0 || requests[eFD]->error == true)
                {
                    if (bytesReceived == -1)
                    cleanAll(eFD);
                    continue;
                }
                std::string toSTing(buf,bytesReceived);
                requests[eFD]->parse_re(toSTing, bytesReceived);

            }
            else if (events[i].events & EPOLLOUT && requests[eFD] && requests[eFD]->getFlag() == true)
            {
                requests[eFD]->to_file.clear();
                requests[eFD]->lastActive = time(0) ;
                if(requests[eFD]->CGI_FLAG && requests[eFD]->error != true) {
                    if(requests[eFD]->sendHeaders == true)
                        response[eFD]->cgi._setupEnv(*requests[eFD]);
                    if(response[eFD]->cgi._waitreturn){
                        response[eFD]->fillResponseBody(*requests[eFD]);

                        s = write (eFD, response[eFD]->getResponse().c_str(), response[eFD]->getResponse().size());
                        if(response[eFD]->getResBody() == "\r\n0\r\n\r\n" || requests[eFD]->getMethod() == "HEAD"||s<=0){
                            unlink(response[eFD]->cgi.cgifile.c_str());
                            cleanAll(eFD);
                            continue ;
                        }
                        else
                            requests[eFD]->sendHeaders = false; 
                    }
                }
                else{
                    response[eFD]->fillResponseBody(*requests[eFD]);
                    s = write (eFD, response[eFD]->getResponse().c_str(), response[eFD]->getResponse().size());
                    if(response[eFD]->getResBody() == "\r\n0\r\n\r\n" || s<=0||requests[eFD]->getMethod() == "HEAD"){
                        cleanAll(eFD);
                        continue ;
                    }
                    else
                        requests[eFD]->sendHeaders = false;
                }
            }
        }
    }
}
