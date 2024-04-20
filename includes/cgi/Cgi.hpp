#ifndef CGI_HPP
#define CGI_HPP

#include "../../includes/Request/Http_req.hpp"

class Cgi
{
private:
    /* data */
    std::map<std::string,std::string> _env;
public:
    Cgi(Http_req &);
    void _setupEnv(Http_req &);
    
    /**/
    ~Cgi();
};


#endif