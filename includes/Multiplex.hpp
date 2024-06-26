#ifndef MULTIPLEX_HPP
#define MULTIPLEX_HPP

#include <iostream>
#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <string>
#include <netdb.h>
#include <fcntl.h>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
#include "SocketManager.hpp"
#include "Server.hpp"
#include "Request/Http_req.hpp"
#include <fstream>
#include "Response/Response.hpp"// For "JaQen" Response
#include "cgi/Cgi.hpp"// For "JaQen" Response
#include <ctime>

#define RESETTEXT  "\x1B[0m" // Set all colors back to normal.
#define FOREBLK  "\x1B[30m" // Black
#define FORERED  "\x1B[31m" // Red
#define FOREGRN  "\x1B[32m" // Green
#define FOREYEL  "\x1B[33m" // Yellow
#define FOREBLU  "\x1B[34m" // Blue
#define FOREMAG  "\x1B[35m" // Magenta
#define FORECYN  "\x1B[36m" // Cyan
#define FOREWHT  "\x1B[37m" // White

#define R_SIZE 1024 // Read Buffer Size
#define TIMEOUT 30

class Multiplex
{
public:
	typedef std::vector<Server> servers_t ;
	typedef std::map<SOCKET, std::vector<Server> > listeners_t ;
	typedef std::map<std::string, SOCKET> host_port_map_t ;
	typedef struct epoll_event epoll_event_t ;
    typedef std::map<SOCKET, Http_req*> requests_t ;
    typedef std::map<SOCKET, Response*> response_t ; // For "JaQen" Response
	
private:
	static SOCKET 			epollFD ;
	static listeners_t		listeners ;
	static requests_t		requests ;
	static response_t		response ; // For "JaQen" Response
    static epoll_event_t 	events[SOMAXCONN] ;
	static host_port_map_t	hostPortMap ;

	Multiplex( void ) ;
	Multiplex( const Multiplex& rhs ) ;
	Multiplex& operator=( const Multiplex& rhs ) ;
	~Multiplex( void ) ;
public:
    static void start( void ) ;
    static void setup( const servers_t& _servers ) ;
	static void cleanAll( int eFD );
} ;

std::ostream& operator<<( std::ostream& os, const Multiplex& server ) ;

#endif
