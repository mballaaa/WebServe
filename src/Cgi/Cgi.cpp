#include "../../includes/cgi/Cgi.hpp"
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>


Cgi::Cgi(Http_req &request){
    _setupEnv(request);
    executeCgi(request);
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

void Cgi::fill_executablefile(){
    std::ifstream file("src/Cgi/pathExecutableFile.txt");
    std::string line;
    
    if(!file.is_open()){
        std::cout << "pathExecutableFile Error" << std::endl;
        return ;
    }
        
    while(getline(file,line)){
        std::istringstream str(line);
        std::string key,value;
        if(str >> key >> value)
            _executablefile[key] = value;
        else
            std::cout << "Error parsing line" << std::endl;
    }
    file.close();
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
    std::cout << headers["content-type"] << std::endl;
    if(headers["content-type"] != "")
        _env["CONTENT_TYPE"] = headers["content-type"].substr(1);
    else
        _env["CONTENT_TYPE"] = "";
	// _env["REDIRECT_STATUS"] = "200"; //know more about REDIRECTE_STATUS
    _env["PATH_INFO"] = request.getPath();
    _env["PATH_TRANSLATED"] = request.getPath();
    _env["QUERY_STRING"] = ""; // get the query with getMethod
    _env["REMOTE_ADDR"] =   server.getHost();
    _env["REQUEST_METHOD"] = request.getMethod();
	// _env["REQUEST_URI"] = request.getPath() + request.getQuery();
	_env["REQUEST_URI"] = request.getPath() + _env["QUERY_STRING"];
    _env["SERVER_PORT"] = server.getPort();
    _env["SERVER_PROTOCOL"] = "HTTP/1.1";
    _env["SERVER_SOFTWARE"] = "Weebserv/1.0";
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    
    std::string extension = fileExtension(request.getPath());
    if(extension != ""){
        _argv[0] = _executablefile[extension];
        _argv[1] = request.getFlag();
    }


}

std::string Cgi::cgiResponse(Http_req &request,std::string _cgibody){

    std::string httpResponse;
    if(_cgibody.find("\r\n\r\n") == std::string::npos){
        _cgibody = "Content-type: text/html; charset=UTF-8\r\n\r\n" + _cgibody;
    }
    request.header["content-type"] = "text/html";
    request._status["200"] = "OK";
    size_t pos = _cgibody.find("\r\n\r\n");
    std::string headers = _cgibody.substr(0,pos);
    std::string body = _cgibody.substr(pos+4);

    return httpResponse;
}

std::string Cgi::executeCgi(Http_req &request){
    std::string _cgibody;
   

    std::string outputfilename = request.randNameGen();

    int input = open(request.make_name.c_str(),O_RDONLY); //The make_name file wasn't always created.
    int output = open("jj.txt", O_RDWR);

    if (input == -1 || output == -1) {
        std::cerr << "Error opening files\n";
        return "\0";
    }


    char **env = envMap_to_char(_env);
    char **argv = envMap_to_char(_argv);
    pid_t pid = fork();
    if(pid < 0){
        for (int i = 0;env[i];i++)
            delete[] env[i];
        for (int i = 0;argv[i];i++)
            delete[] argv[i];
        return "FORK FAILED";
    }
    else if(!pid){
        dup2(output,1);
        dup2(input,0);
        execve(argv[0],argv,env);
        exit(1);
    }
    else{
        int status;
        waitpid(-1,&status,0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0){
            std::cout << "WAITPID ERROR" << std::endl;
            for (int i = 0;env[i];i++)
                delete[] env[i];
            for (int i = 0;argv[i];i++)
                 delete[] argv[i];
            exit(1);
        }
    }

    std::ifstream _filename(outputfilename.c_str());
    if(!_filename.is_open())
        std::cout << "_filename opening ERROR" << std::endl;
    std::string line;
    while(getline(_filename,line)){
        _cgibody += line + "\n";
    }
    for (int i = 0;env[i];i++)
        delete[] env[i];
    // delete[] env;
    for (int i = 0;argv[i];i++)
        delete[] argv[i];
    // delete[] argv;
    
    close(input);
    close(output);
    _filename.close();

    // cgiResponse(request,_cgibody);
    return _cgibody;
}

Cgi::~Cgi()
{
}   