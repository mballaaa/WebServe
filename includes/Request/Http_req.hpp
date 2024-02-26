#ifndef HTTP_REQ
#define HTTP_REQ
#include <iostream>
#include "../Server.hpp"
#include <cerrno>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include "../../includes/Multiplex.hpp"
class Http_req
{
public:
    struct golbal_info
    {
        
    };
    

private:
   /// this the start line 
    std::string req;
    
    
    std ::string method;
    std::string path;
    std ::string http_ver;

   std::map<std::string, std::string> header; 
    Server server;
    int byterec;

public:
    void debugFunction();
    Http_req(std::string req,int byterec, Multiplex::listeners_t listenrs);
   void parse_re(std ::string bufer,int bytee);
   int StautRe(std ::string request);
    int MoreValidation();
    ~Http_req();
};

#endif