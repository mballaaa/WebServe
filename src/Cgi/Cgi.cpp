#include "../../includes/cgi/Cgi.hpp"

Cgi::Cgi(Http_req &request){
    _setupEnv(request);
}

std::string Cgi::size_t_to_string(size_t nbr){

    std::stringstream string;

    string << nbr;
    return string.str();
}

void Cgi::_setupEnv(Http_req &request){
    std::map<std::string,std::string> headers = request.getHeader();
    
    _env["CONTENT_LENGTH"] = size_t_to_string(request.getBody().size());
    _env["CONTENT_TYPE"] = headers["content-type"].substr(1);
}

Cgi::~Cgi()
{
}