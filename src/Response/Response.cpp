#include "../../includes/Response/Response.hpp"

Response::Response(Http_req request){
    (void) request;

    fillResponseBody(request);
    fillResponseHeadre(request);
    _response = _resheaders + _resbody;
}

/*Fill Response Header*/
void Response::fillResponseHeadre(Http_req request){

    std::map<std::string,std::string>::iterator it1 = request._status.begin();
    std::map<std::string,std::string> h = request.header;
    std::map<std::string,std::string>::iterator it2 = h.begin();
    std::stringstream ss;
    ss << _resbody.size();
    std::cerr << "------------------RESP------------------" << std::endl; 
    _resheaders = request.getHttpVersion()+" "+it1->first+" "+it1->second+"\r\n";
    h["content-length"] = ss.str();
    h["content-type"] = "text/plain"; 
    for(;it2 != h.end();it2++)
        _resheaders += it2->first+":"+it2->second+"\r\n";
  
    _resheaders += "\r\n";
    std::cerr << "------------------RESP------------------" << std::endl; 


}
void Response::created(){

    std::ifstream file("www/html/201.html");
    std::string line;
    if(file.is_open()){
        while (getline(file,line))
            _resbody += line+"\n";
    }
    file.close();
}
void Response::forrbiden(){
    
    std::ifstream file("www/html/403.html");
    std::string line;
    if(file.is_open()){
        while (getline(file,line))
            _resbody += line+"\n";
    }
    file.close();
}

void Response::notFound(){
    std::ifstream file("www/html/Page not found · GitHub Pages.html");
    std::string line;
    if(file.is_open()){
        while (getline(file,line))
            _resbody += line+"\n";
    }
    file.close();
}

void Response::noContent(){

    std::ifstream file("www/html/204.html");
    std::string line;
    if(file.is_open()){
        while (getline(file,line))
            _resbody += line+"\n";
    }
    file.close();
}

/*Fill  Resposne Body*/
void Response::fillResponseBody(Http_req request){
    if(request._status.find("201") != request._status.end())
        created();
    else if(request._status.find("403") != request._status.end())
        forrbiden();
    else if(request._status.find("404") != request._status.end())
        notFound();
    else if(request._status.find("204") != request._status.end())
        noContent();

}

std::string Response::getResHeaders(){
    return _resheaders;
}

std::string  Response::getResBody(){
    return _resbody;
}
std::string  Response::getResponse(){
    return _response;
}

Response::~Response() 
{
}