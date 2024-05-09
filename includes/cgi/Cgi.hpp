#ifndef CGI_HPP
#define CGI_HPP

#include "../../includes/Request/Http_req.hpp"
#include<unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctime>
#include <sys/time.h>

class Cgi
{
private:
    /* data */
    std::map<std::string,std::string> _env;
    std::map<std::string,std::string> _executablefile;
    std::map<int,std::string>           _argv;
public:
    Cgi();
    void _setupEnv(Http_req &);
    void executeCgi(Http_req &request);
    int fill_executablefile();
    void cgiResponse(Http_req &request);
    void cgiErrorResponse(Http_req &request,std::string _cgibody);
    /*---utils---*/
    std::string size_t_to_string(size_t);
    std::string fileExtension(std::string filename);
    template<typename first,typename second>
    char        **envMap_to_char(std::map<first,second> _env);

    int status;
    std::string outputfilename;
    pid_t _waitreturn ;
    pid_t _waitstatus ;
    int input;
    int output;
    pid_t pid         ;
    char **env;
    char **argv;
    std::string cgifile;
    clock_t     startTime;
    clock_t     endTime;
    
    ~Cgi();
};


#endif