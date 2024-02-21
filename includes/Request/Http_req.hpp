#ifndef HTTP_REQ
#define HTTP_REQ
#include <iostream>
#include "../Server.hpp"

class Http_req
{
public:
    struct golbal_info
    {
        stat
    };
    

private:
    std::string req;
    std ::string method;
    std::string path;
    std ::string http_ver;
    
    int byterec;

public:
    Http_req(std::string req,int byterec);
   void parse_re(std ::string bufer,int bytee);
    ~Http_req();
};

#endif