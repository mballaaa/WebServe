#include "../../includes/cgi/Cgi.hpp"
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>


Cgi::Cgi(){
    _waitreturn = 1;
    _waitstatus = 0;
    outputfilename = "";
    input = 0;
    output = 0;
    
}

std::string Cgi::size_t_to_string(size_t nbr){

    std::stringstream string;

    string << nbr;
    return string.str();
}

template<typename first,typename second>
char **Cgi:: envMap_to_char(std::map<first,second> _env){
    char **env = new char *[_env.size()+1];
    int i = 0;
    typename std::map<first,second>::iterator it = _env.begin();
    for(;it!=_env.end();it++){
        std::string key_value = it->first + "=" + it->second;
        env[i] = new char[key_value.size()+1];
        env[i] = strcpy(env[i], key_value.c_str());
        i++;
    }
    env[i] = NULL;
    return env;
}

char **avMap_to_char(std::map<int,std::string> _env){
    char **env = new char *[_env.size()+1];
    int i = 0;
    std::map<int,std::string>::iterator it = _env.begin();
    for(;it!=_env.end();it++){
        std::string key_value =it->second;
        env[i] = new char[key_value.size()+1];
        env[i] = strcpy(env[i], key_value.c_str());
        i++;
    }
    env[i] = NULL;
    return env;
}

std::string Cgi::fileExtension(std::string filename){
    std::string extension = "";
    size_t p = filename.find_last_of('.');
    if(p != std::string::npos )
        extension = filename.substr(p+1);
    return extension;
}

void Cgi::_setupEnv(Http_req &request){
    std::map<std::string,std::string> headers = request.getHeader();
    Server server = request.getServer();
    _env["CONTENT_LENGTH"] = size_t_to_string(request.getBody().size());
    _env["CONTENT_TYPE"] = headers["content-type"];
	_env["REDIRECT_STATUS"] = "CGI"; //know more about REDIRECTE_STATUS
    _env["PATH_INFO"] = request.getPath().substr(1);
    _env["PATH_TRANSLATED"] = request.getPath().substr(1);
    _env["QUERY_STRING"] = request.query_string; // get the query with getMethod
    _env["REMOTE_ADDR"] =   server.getHost();
    _env["REQUEST_METHOD"] = request.getMethod();
	_env["REQUEST_URI"] = request.getPath() + _env["QUERY_STRING"];
    _env["SERVER_PORT"] = server.getPort();
    _env["HTTP_COOKIE"] = request.header["cookie"];
    _env["SERVER_PROTOCOL"] = "HTTP/1.1";
    _env["SERVER_SOFTWARE"] = "Weebserv/1.0";
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    
    
    std::string extension = fileExtension(request.getPath());
    std::cerr << "Heloo "+extension << std::endl;

    _executablefile = request._loca.getCgiPaths();
    // exit(0);
    if(extension != "" && _executablefile.find(extension) != _executablefile.end()){
        _argv[0] = _executablefile[extension];
        _argv[1] = request.getTarget().substr(2);
        std::cout << "=>> " << _argv[0] << std::endl;
        std::cout << "=>> " << _argv[1] << std::endl;

    }
    else    
    {
        /*=====Must be in a separate func=====*/
        request._status.clear();
        request._status["404"] = "Not found";
        request.fd = open("www/html/Page not found · GitHub Pages.html",O_RDWR);
        _waitreturn = 1;
        return ;
        /*===================================*/
    }
    // std::cerr << "SAAAALm" << std::endl;
    executeCgi(request);
}

void Cgi::cgiResponse(Http_req &request){

    std::string line;
    bool headerflag = false;
    std::string _cgibody;
    std::ifstream _filename(outputfilename.c_str());
    while(getline(_filename,line)){
        _cgibody += line + "\n";
        if(_cgibody.find("\r\n\r\n") != std::string::npos){
            headerflag = true;
            break;
        }
    }
    cgifile = "www/html/cgi"+request.randNameGen()+".html";
    std::ofstream file(cgifile.c_str(),std::ios_base::app);
    if(!file.is_open())
    {
        std::cout << "cgi file erro" << std::endl;
        return ;
    }
    if(headerflag == false){
        _filename.close();
        _filename.open(outputfilename.c_str());
    }
    while(getline(_filename,line))
        file << line+"\n";
    _filename.close();
    request.header["content-type"] = "text/html";
    request._status["200"] = "OK";
    file.close();
    request.fd = open(cgifile.c_str(),O_RDWR);    
}

void Cgi::cgiErrorResponse(Http_req &request,std::string _cgibody){

    if(_cgibody.find("\r\n\r\n") == std::string::npos)
        _cgibody = "Status: 500 Internal Server Error\r\nContent-type: text/html; charset=UTF-8\r\n\r\n";
    request.header["content-type"] = "text/html";
   
    std::string::size_type index2= _cgibody.find("\r",12);
    request._status[_cgibody.substr(8,3)] = _cgibody.substr(12,index2 - 12);
    if(request.fd == 0)
        request.fd = open("www/html/500.html",O_RDWR);
}

void freeptr(char **env,char **argv){
    for (int i = 0;env[i];i++)
        delete[] env[i];
    for (int i = 0;argv[i];i++)
        delete[] argv[i];
}


void Cgi::executeCgi(Http_req &request){
   
    if(request._status.find("404") != request._status.end()){
        
        unlink(outputfilename.c_str());//remove output file
        return ;
    }

    request._status.clear(); //clear status;

    if(!_waitstatus){

        outputfilename = "HHH"+request.randNameGen();
        if(request.make_name == ""){
            input = 0;//The make_name file wasn't always created.
        }
        else
            input = open(request.make_name.c_str(),O_RDONLY); 
        output = open(outputfilename.c_str(),  O_CREAT | O_RDWR,0666);
    }


    if ( output == -1 || input == -1)
        return ;

    if(!_waitstatus){
        startTime = clock();
        pid = fork();
    }
    _waitstatus = 1;

    if(pid < 0)
        return ;
    else if(!pid){
    
        env = envMap_to_char(_env);
        argv = avMap_to_char(_argv);
        if(input != 0)
            dup2(input,STDIN_FILENO);
        dup2(output, STDOUT_FILENO);
        
        execve(argv[0], argv,NULL);
        exit(1);
    }
    else{
        _waitreturn = waitpid(pid,&status,WNOHANG);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0){
            std::string _cgibody;
            std::ifstream _filename(outputfilename.c_str());
            std::string line;
            while(getline(_filename,line)){
                _cgibody += line + "\n";
            }
            cgiErrorResponse(request,_cgibody);
            unlink(outputfilename.c_str());//remove output file
            kill(pid,SIGKILL);
            waitpid(pid,&status,WNOHANG);
            return ;
        }
    }
   
    if(_waitreturn){
        cgiResponse(request);
        unlink(outputfilename.c_str());//remove output file
        return ;
    }
    endTime = clock();
    double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
    if(elapsedTime>=2){

        kill(pid,SIGKILL);
        waitpid(pid,&status,WNOHANG);
        request._status.clear();
        request._status["504"] = "Gateway timeout";
        request.header["content-type"] = "text/html";
        request.fd = open("www/html/504.html",O_RDONLY);
        std::cout << "fd cgi: " << request.fd << std::endl ;
        unlink(outputfilename.c_str());//remove output file
        _waitreturn = 1;
        std::cerr << "ERROR" << std::endl;
        return ;
    }
    return ;
}

Cgi::~Cgi()
{
    close(output);
    if (input)
        close(input);
}   
