#include "../../includes/Multiplex.hpp"

#include "../../includes/Request/Http_req.hpp"
#include "../../includes/Response/Response.hpp"
#include "../../includes/cgi/Cgi.hpp"
SOCKET Multiplex::epollFD;
Multiplex::listeners_t Multiplex::listeners;
Multiplex::requests_t Multiplex::requests;
Multiplex::response_t Multiplex::response;// For "JaQen" Response
// Multiplex::cgi_t Multiplex::cgi;// For "JaQen" Response
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
        std::cerr << "Listening on: " << id << "..." << std::endl;
        if (hostPortMap.find(id) != hostPortMap.end()) // host:port already binded
        {
            // sfd = hostPortMap[id];
            servIt++ ;
            continue ;
        }
        else // create new socket, bind, listen and add to epoll finally add it to hostPortMap
        {
            sfd = SocketManager::createSocket(servIt->getHost().c_str(), servIt->getPort().c_str(), AF_INET, SOCK_STREAM, AI_PASSIVE);
            SocketManager::makeSocketNonBlocking(sfd);
            SocketManager::startListening(sfd);
            SocketManager::epollCtlSocket(sfd, EPOLL_CTL_ADD);
            hostPortMap.insert(std::make_pair(id, sfd));
        }
        listeners[sfd] = *servIt;
        servIt++;
    }
}

void Multiplex::start(void)
{
    int s;
    std::map<int, std::string> eventName;

    eventName[EPOLLIN] = "EPOLLIN";
    eventName[EPOLLET] = "EPOLLET";
    eventName[EPOLLOUT] = "EPOLLOUT";
    eventName[EPOLLERR] = "EPOLLERR";
    eventName[EPOLLHUP] = "EPOLLHUP";

    while (1)
    {
        int eventCount = 0;
        eventCount = epoll_wait(epollFD, events, SOMAXCONN, -1); // Waiting for new event to occur
        for (int i = 0; i < eventCount; i++)
        {
            // std::cout << "fd: " << events[i].data.fd << std::endl ;
            // std::cerr << "descriptor " << events[i].data.fd << " ";
            // if (events[i].events & EPOLLOUT)
            //     std::cerr << eventName[EPOLLOUT];
            // if (events[i].events & EPOLLIN)
            //     std::cerr << eventName[EPOLLIN];
            // if (events[i].events & EPOLLET)
            //     std::cerr << eventName[EPOLLET];
            // if (events[i].events & EPOLLERR)
            //     std::cerr << eventName[EPOLLERR];
            // if (events[i].events & EPOLLHUP)
            //     std::cerr << eventName[EPOLLHUP];
            // std::cerr << std::endl;

            // if ((events[i].events & EPOLLERR)
            //     || events[i].events & EPOLLHUP)
            // {
            //     close(events[i].data.fd);
                // perror("EPOLLERR");
            //      close (events[i].data.fd);
            //     requests.erase(events[i].data.fd) ;
            //     continue;
            // }
            // else 
            if (events[i].events & EPOLLOUT)
            {
                if (difftime(time(NULL), requests[events[i].data.fd]->lastActive) > TIMEOUT)
                {
                    requests[events[i].data.fd]->fd = open("www/html/408.html", O_RDWR) ;
                    unlink(requests[events[i].data.fd]->make_name.c_str());
                    requests[events[i].data.fd]->in_out = true ;
                    requests[events[i].data.fd]->_status["408"] = "Request Timeout" ;
                    std::cout << "fd: " << events[i].data.fd << " time diff: " << difftime(time(NULL), requests[events[i].data.fd]->lastActive) << std::endl ;
                }
            }
            if (listeners.find(events[i].data.fd) != listeners.end()) // Check if socket belong to a server
            {
                struct sockaddr in_addr;
                socklen_t in_len;
                int infd;
                char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                in_len = sizeof in_addr;
                infd = accept(events[i].data.fd, &in_addr, &in_len); // Accept connection
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
                    {
                        perror("accept");
                        continue;
                    }
                }

                s = getnameinfo(&in_addr, in_len,
                                hbuf, sizeof hbuf,
                                sbuf, sizeof sbuf,
                                NI_NUMERICHOST | NI_NUMERICSERV);
                if (s == 0)
                {
                    printf("Accepted connection on descriptor %d "
                            "(host=%s, port=%s)\n", infd, hbuf, sbuf);
                }

                SocketManager::makeSocketNonBlocking(infd);
                SocketManager::epollCtlSocket(infd, EPOLL_CTL_ADD);
                requests.insert(std::make_pair(infd, new Http_req(listeners[events[i].data.fd])));
                response.insert(std::make_pair(infd, new Response()));
                continue;
            }
            else if (events[i].events & EPOLLIN  && requests[events[i].data.fd]->getFlag() == false)   // check if we have EPOLLIN (connection socket ready to read)
            {
                requests[events[i].data.fd]->lastActive = time(0) ;
                ssize_t bytesReceived;
                char buf[R_SIZE] = {0};

                bytesReceived = read(events[i].data.fd, buf,  R_SIZE - 1);
                std ::cout << bytesReceived << std ::endl;
                if (bytesReceived == -1 || bytesReceived == 0)
                {
                    std::cout << "client closed " << std::endl ;
                    std ::cout << "====>" << bytesReceived << std ::endl;
                    close(events[i].data.fd);
                    delete requests[events[i].data.fd] ;
                    requests.erase(events[i].data.fd) ;
                    delete response[events[i].data.fd] ;
                    response.erase(events[i].data.fd) ;
                    continue;
                }
                std::string toSTing(buf,bytesReceived);
                requests[events[i].data.fd]->parse_re(toSTing, bytesReceived);
            }
            else if (events[i].events & EPOLLOUT && requests[events[i].data.fd] && requests[events[i].data.fd]->getFlag() == true)
            {
                requests[events[i].data.fd]->lastActive = time(0) ;

                if(requests[events[i].data.fd]->_loca.getCgi() == true && requests[events[i].data.fd]->CGI_FLAG == true) {
                    if(requests[events[i].data.fd]->sendHeaders == true)
                        response[events[i].data.fd]->cgi._setupEnv(*requests[events[i].data.fd]);
                    if(response[events[i].data.fd]->cgi._waitreturn){
                        response[events[i].data.fd]->fillResponseBody(*requests[events[i].data.fd]);

                        s = write (events[i].data.fd, response[events[i].data.fd]->getResponse().c_str(), response[events[i].data.fd]->getResponse().size());
                        if(response[events[i].data.fd]->getResBody() == "\r\n0\r\n\r\n"){
                            unlink(response[events[i].data.fd]->cgi.cgifile.c_str());
                            delete requests[events[i].data.fd] ;
                            requests.erase(events[i].data.fd) ;
                            delete response[events[i].data.fd] ;
                            response.erase(events[i].data.fd) ;
                            close (events[i].data.fd);
                        }
                        else
                            requests[events[i].data.fd]->sendHeaders = false;
                    }
                }
                else{
                    response[events[i].data.fd]->fillResponseBody(*requests[events[i].data.fd]);
                    s = write (events[i].data.fd, response[events[i].data.fd]->getResponse().c_str(), response[events[i].data.fd]->getResponse().size());
                    if(response[events[i].data.fd]->getResBody() == "\r\n0\r\n\r\n"){
                        delete requests[events[i].data.fd] ;
                        requests.erase(events[i].data.fd) ;
                        delete response[events[i].data.fd] ;
                        response.erase(events[i].data.fd) ;
                        close (events[i].data.fd);
                    }
                    else
                        requests[events[i].data.fd]->sendHeaders = false;
                }
            }
        }
    }
    // close (sfd);
}
