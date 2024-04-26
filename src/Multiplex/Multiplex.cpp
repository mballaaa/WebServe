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
            sfd = hostPortMap[id];
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

    /* The event loop */
    Http_req reqqq;

    while (1)
    {
        int eventCount;

        eventCount = epoll_wait(epollFD, events, SOMAXCONN, -1); // Waiting for new event to occur
        // std::cerr << eventCount << " events ready" << std::endl;
        for (int i = 0; i < eventCount; i++)
        {
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

            if ((events[i].events & EPOLLERR)
                || events[i].events & EPOLLHUP)
            {

                close(events[i].data.fd);
                perror("EPOLLERR");
                 close (events[i].data.fd);
                requests.erase(events[i].data.fd) ;
                continue;
            }
            else 
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
                    // printf("Accepted connection on descriptor %d "
                    //         "(host=%s, port=%s)\n", infd, hbuf, sbuf);
                }

                SocketManager::makeSocketNonBlocking(infd);
                SocketManager::epollCtlSocket(infd, EPOLL_CTL_ADD);
                requests.insert(std::make_pair(infd, Http_req(listeners[events[i].data.fd])));
                requests[events[i].data.fd].i = 0;
                response[events[i].data.fd].cgi._waitstatus = 0;
                response[events[i].data.fd].cgi._waitreturn = 1;
                continue;
            }
            else if (events[i].events & EPOLLIN  )   // check if we have EPOLLIN (connection socket ready to read)
            {
                ssize_t bytesReceived;
                char buf[R_SIZE] = {0};

                bytesReceived = read(events[i].data.fd, buf,  R_SIZE - 1);
                if (bytesReceived == -1 || bytesReceived == 0)
                {

                    close(events[i].data.fd);
                    requests.erase(events[i].data.fd);
                    continue;
                }
                 // std::ofstream outputFile("reqq.txt", std::ios_base::app);

    // if (outputFile.is_open())
    // {
    //     // Output body to the file
    //     outputFile << buf;

    //     // Close the file
        
    // }
    // outputFile.close();
                std::string toSTing(buf,bytesReceived);


               requests[events[i].data.fd].parse_re(toSTing, bytesReceived);

            }
            else if (events[i].events & EPOLLOUT && requests[events[i].data.fd].getFlag() == true)
            {
                std::cout << "=?>>>>> STOPP2"<< std::endl;
                if(requests[events[i].data.fd]._loca.getCgi() == true){

                    response[events[i].data.fd].cgi._setupEnv(requests[events[i].data.fd]);
                    std::cout << response[events[i].data.fd].cgi._waitreturn << std::endl;

                    if(response[events[i].data.fd].cgi._waitreturn){
                        response[events[i].data.fd].fillResponseBody(requests[events[i].data.fd]);
                        s = write (events[i].data.fd, response[events[i].data.fd].getResponse().c_str(), response[events[i].data.fd].getResponse().size());
                        close (events[i].data.fd);
                        requests.erase(events[i].data.fd) ;
                        response.erase(events[i].data.fd) ;

                        std::cout << "=?>>>>> STOPP"<< std::endl;
                    }
                }
                else{
                    std::cout << "=?WIHOUT"<< std::endl;
                    response[events[i].data.fd].fillResponseBody(requests[events[i].data.fd]);
                    s = write (events[i].data.fd, response[events[i].data.fd].getResponse().c_str(), response[events[i].data.fd].getResponse().size());
                    close (events[i].data.fd);
                    requests.erase(events[i].data.fd) ;
                    response.erase(events[i].data.fd) ;
                }
                std::cerr << "Response Sent" << std::endl;
            }
        }
    }
    // close (sfd);
}
