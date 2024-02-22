#ifndef HTTP_REQ
#define HTTP_REQ
#include <iostream>
#include "../Server.hpp"
#include <cerrno>
#include <cstdio>
#include <sstream>
#include <algorithm>
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
    /// hedear
  //  std ::string header;
   std::map<std::string, std::string> header; 

    
    int byterec;

public:
    Http_req(std::string req,int byterec);
   void parse_re(std ::string bufer,int bytee);
   int StautRe(std ::string request);
    ~Http_req();
};

#endif