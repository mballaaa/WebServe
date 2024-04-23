#include "../../includes/Multiplex.hpp"

#include "../../includes/Request/Http_req.hpp"
#include "../../includes/Response/Response.hpp"
SOCKET Multiplex::epollFD;
Multiplex::listeners_t Multiplex::listeners;
Multiplex::requests_t Multiplex::requests;
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
    // each server should have a socket
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

    size_t totalBytesReceived = 0 ;
    std::ofstream output;

    /* The event loop */
    while (1)
    {
        int eventCount; // Number of events epoll_wait returned

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

            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP))
            {
                // fprintf (stderr, "epoll error\n");
                close(events[i].data.fd);
                perror("EPOLLERR | EPOLLHUP");
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
                // mballa: create and add request object after accepting new client
                // Http_req my_obg;
                requests.insert(std::make_pair(infd, Http_req(listeners[events[i].data.fd])));
                output.open("testfile.txt") ;
            }
            else if (events[i].events & EPOLLIN) // check if we have EPOLLIN (connection socket ready to read)
            {
                ssize_t bytesReceived;  // number of bytes read returned
                char buf[R_SIZE] = {0}; // read buffer

                bytesReceived = read(events[i].data.fd, buf, sizeof(char) * R_SIZE - 1);
                if (bytesReceived == -1 || bytesReceived == 0)
                {
                    if (bytesReceived == -1)
                        perror("read");
                    close(events[i].data.fd);
                    requests.erase(events[i].data.fd);
                    continue;
                }
                std::string toSTing(buf); // Convert received data to string using the total bytes received
                 //Http_req &currRequest = requests.find(events[i].data.fd)->second;
               // std::cout << "fddddd " << requests[events[i].data.fd].is_finsh << std::endl;
               if (output.is_open())
               {
                    output << toSTing ;
               }
               totalBytesReceived += bytesReceived ;
               if (totalBytesReceived == 759050)
               {
                write(events[i].data.fd, "HTTP/1.1 201 CREATED\r\n\r\n", 24) ;
                std::cout << totalBytesReceived << std::endl ;
                close(events[i].data.fd) ;
                requests.erase(events[i].data.fd);
                totalBytesReceived = 0 ;
                    output.close() ;

               }
                // requests[events[i].data.fd].parse_re(toSTing, bytesReceived);
                 //currRequest.parse_re(toSTing, bytesReceived); // Pass totalBytesReceived instead of bytesReceived
                 //reqqq = currRequest;
            }
            else if (events[i].events && EPOLLOUT && requests[events[i].data.fd].getFlag() == true) // check if we have EPOLLOUT (connection socket ready to write)
            {
                // Response resp(requests[events[i].data.fd]);
                // if(resp.getResponse().empty())
                // {
                //     std :: cout << "IS empty\n";
                // }
                // else{
                //      std :: cout << "IS not empty\n";
                // }
                // s = write (events[i].data.fd, resp.getResponse().c_str(), resp.getResponse().size());       
                // std::cout << "============== Response ==============" << std::endl ;
                write(events[i].data.fd, "HTTP/1.1 201 CREATED", 20) ;
            }
        }
    }
    // close (sfd);
}
