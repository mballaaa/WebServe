#include "../../includes/cgi/Cgi.hpp"
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>


Cgi::Cgi(){
    _waitreturn = 1;
    _waitstatus = 0;
    outputfilename = "";
    input = -1;
    output = -1;
    pid = -1;
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
#include <sys/stat.h>

// Function to get file size
off_t getFileSize(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    } else {
        return -1; // Error occurred
    }
}
std::string off_tToString(off_t value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
void Cgi::_setupEnv(Http_req &request){
  
    std::map<std::string,std::string> headers = request.getHeader();
    Server server = request.getServer();

    _env.clear();
    if (headers["content-type"].length() && request.getMethod() == "POST"){
        if(request.make_name != "")
            _env["CONTENT_LENGTH"] = off_tToString(getFileSize(request.make_name.c_str()));
        _env["CONTENT_TYPE"] = headers["content-type"];
    }
    _env["GATEWAY_INTERFACE"] = "CGI/1.1";
    _env["SCRIPT_NAME"] = request.getPath(); 
    _env["SCRIPT_FILENAME"] = request.getTarget();
    _env["PATH_INFO"] = _env["SCRIPT_NAME"]; 
    _env["PATH_TRANSLATED"] = _env["SCRIPT_FILENAME"];
    _env["QUERY_STRING"] = request.query_string;
    _env["REQUEST_URI"] = request.getTarget();
    _env["SERVER_PORT"] = server.getPort(); 
    _env["REQUEST_METHOD"] = request.getMethod();
    _env["SERVER_PROTOCOL"] = "HTTP/1.1";
    _env["REDIRECT_STATUS"] = "200";
    _env["SERVER_SOFTWARE"] = "Weebserv/1.0";

    _env["HTTP_COOKIE"] = request.header["cookie"];

    std::string extension = fileExtension(request.getTarget());
    
    _executablefile = request._loca.getCgiPaths();
   
    if(extension != "" && _executablefile.find(extension) != _executablefile.end()){
        _argv[0] = _executablefile[extension];
        _argv[1] = request.getTarget();

    }
    else    
    {
        /*=====Must be in a separate func=====*/
        std::cout << "no extension" << std::endl ;
        request._status = 404;
        if(request.fd>0)
            close(request.fd);
        request.fd = open(request.getErrorPage().c_str(),O_RDWR);
        _waitreturn = 1;
        return ;
        /*===================================*/
    }
    executeCgi(request);
}

void Cgi::cgiResponse(Http_req &request){

    std::string line;
    bool headerflag = false;
    std::string _cgibody;
    std::ifstream _filename(outputfilename.c_str(),std::ios::binary);
    while(getline(_filename,line)){
        _cgibody += line + "\n";
        if(_cgibody.find("\r\n\r\n") != std::string::npos){
            headerflag = true;
            break;
        }
    }
  
    if(headerflag == true){
        if(_cgibody.find("Status") != std::string::npos){
            request._status = std::atoi(_cgibody.substr(8,3).c_str());
            std::string::size_type index1= _cgibody.find("\r\n") + 2;
            std::string::size_type index3= _cgibody.find("\r\n\r\n");
            request.to_file = _cgibody.substr(index1,index3-index1+1);  

        }
        else{
            request._status = 200;
            if (_cgibody.find("\r\n\r\n") != std::string::npos)
                request.to_file = _cgibody.substr(0,_cgibody.find("\r\n\r\n") + 2);
        }
    }
    else
        request._status = 200;

    cgifile = "www/html/cgi"+request.randNameGen()+".html";
    std::ofstream file(cgifile.c_str(),std::ios_base::app);
    if(!file.is_open())
    {
        return ;
    }
    if(headerflag == false){
        _filename.close();
        _filename.open(outputfilename.c_str());
    }
    int i = 0;
    while(getline(_filename,line)){
        i++;
        file << line+"\n";
    }
    _filename.close();
    request.header["content-type"] = "text/html";
    
    file.close();
    if(i)
    {
        if (request.fd > 0)
            close(request.fd) ;
        request.fd = open(cgifile.c_str(),O_RDWR);    
    }
}

void Cgi::cgiErrorResponse(Http_req &request,std::string _cgibody){
    if(_cgibody.find("\r\n\r\n") == std::string::npos)
        _cgibody = "Status: 500 Internal Server Error\r\nContent-type: text/html; charset=UTF-8\r\n\r\n";
    request.header["content-type"] = "text/html";
    request._status = std::atoi(_cgibody.substr(8,3).c_str()) ;
    if(request.fd > 0)
        close(request.fd);
    request.fd = open(request.getErrorPage().c_str(),O_RDWR);
}

void freeptr(char **env,char **argv){
    for (int i = 0;env[i];i++)
        delete[] env[i];
    for (int i = 0;argv[i];i++)
        delete[] argv[i];
}


void Cgi::executeCgi(Http_req &request){
   
    if(request._status == 404){
        
        unlink(outputfilename.c_str());//remove output file
        return ;
    }


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
        if(request.getMethod() == "POST")
            dup2(input,STDIN_FILENO);
        dup2(output, STDOUT_FILENO);
        
        execve(argv[0], argv,env);
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
            waitpid(pid,&status,0);
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
        waitpid(pid,&status,0);
        request._status = 504;
        request.header["content-type"] = "text/html";
        if (request.fd > 0)
            close(request.fd) ;
        request.fd = open(request.getErrorPage().c_str(),O_RDONLY);
        unlink(outputfilename.c_str());//remove output file
        _waitreturn = 1;
        return ;
    }
    return ;
}

Cgi::~Cgi()
{
    if(output)
            close(output);
        if (input)
            close(input);
    if (pid != -1)
    {
        kill(pid, SIGKILL) ;
        waitpid(pid,&status,0);
    }
    unlink(cgifile.c_str()) ;
}   
