#ifndef CGI_HPP
#define CGI_HPP

#include "../../includes/Request/Http_req.hpp"
#include<unistd.h>
class Cgi
{
private:
    /* data */
    std::map<std::string,std::string> _env;
    std::map<std::string,std::string> _executablefile;
    std::map<int,std::string>           _argv;
public:
    Cgi(Http_req &);
    void _setupEnv(Http_req &);
    std::string executeCgi(Http_req &request);
    void fill_executablefile();
    std::string cgiResponse(Http_req &request,std::string _cgibody);
    
    /*---utils---*/
    std::string size_t_to_string(size_t);
    std::string fileExtension(std::string filename);
    template<typename first,typename second>
    char        **envMap_to_char(std::map<first,second> _env);
    ~Cgi();
};


#endif