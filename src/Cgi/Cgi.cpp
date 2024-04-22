#include "../../includes/cgi/Cgi.hpp"
#include <cstring>
#include <fcntl.h>
#include <sys/wait.h>


Cgi::Cgi(Http_req &request){
    _setupEnv(request);
}

std::string Cgi::size_t_to_string(size_t nbr){

    std::stringstream string;

    string << nbr;
    return string.str();
}

template<typename first,typename second>
char **Cgi:: **envMap_to_char(std::map<first,second> _env){
    char **env = new char *[_env.size()+1];
    int i = 0;
    for(std::map<std::string,std::string>::iterator it = _env.begin();it!=_env.end();it++){
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
    _env["CONTENT_TYPE"] = headers["content-type"].substr(1);
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



std::string Cgi::executeCgi(){
    std::string _cgibody;
   

    char **env = envMap_to_char(_env);
    char **argv = envMap_to_char(_argv);

    int input = open(request.make_name.c_str(),O_RDONLY);
    int output = open(request.randNameGen().c_str(), O_CREAT | O_RDWR);
    if (input == -1 || output == -1) {
        std::cerr << "Error opening files\n";
        return NULL;
    }


    pid_t pid = fork();
    if(pid < 0)
        return "FORK FAILED";
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
            exit(1);
        }
    }
    
    return _cgibody;
}

Cgi::~Cgi()
{
}   