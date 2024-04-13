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
    for(;it2 != h.end();it2++)
        _resheaders += it2->first+":"+it2->second+"\r\n";
  
    _resheaders += "\r\n";
    std::cerr << "------------------RESP------------------" << std::endl; 


}

/*Fill  Resposne Body*/
void Response::fillResponseBody(Http_req request){
    (void) request;
    std::ifstream file("www/html/201.html");
    std::string line;
    if(file.is_open()){
        while (getline(file,line))
            _resbody += line+"\n";
        
    }
    file.close();
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