#include "../../includes/Response/Response.hpp"
#include <unistd.h>

Response::Response() : buffer(R_BUFFER_SIZE)
{
    headerSent = false ;
    fileOpened = false ;
}

Response::Response(const Response& obj)
{
    //std::cout << "copy" << std::endl ;
    (void) obj ;
    exit(1) ;
}
const Response& Response::operator=(const Response& obj)
{
    //std::cout << "= copy" << std::endl ;
    (void) obj ;
    exit(1) ;
}

std::string sizeToHex(size_t size)
{
    std::stringstream ss ;

    ss << std::hex << size << "\r\n" ;
    return ss.str() ;
}

/*Fill Response Header*/
void Response::fillResponseHeadre(Http_req &request){
    
    std::map<std::string,std::string>::iterator it1 = request._status.begin();
    std::map<std::string,std::string> h;
    _resheaders = "HTTP/1.1 "+it1->first+" "+it1->second+"\r\n";
    _resheaders += request.to_file;
    if (request._loca.getReturn().first !=0 &&request._loca.getReturn().second != "")
    {
        h["Location"] = " " + request._loca.getReturn().second ;
    }
      
    std::string fileExtension = request._target.substr(request._target.find_last_of('.') + 1);
    if(!request._loca.getCgi()){
        h["content-type"] = request._rmime[fileExtension];
    }
    // if(request._loca.getCgi() && request.getMethod() == "POST")
    //     _resheaders += "\r\n";
    h["Transfer-Encoding"] = "chunked";
    h["host"] = "127.0.0.1:9090";
    h["Connection"] = "close";
    
    std::map<std::string,std::string>::iterator it2 = h.begin();
    for(;it2 != h.end();it2++)
    {
        if (it2->second != "")
            _resheaders += it2->first+": "+it2->second+"\r\n";
    }

}

/*Fill  Resposne Body*/
void Response::fillResponseBody(Http_req &request){
    _resbody = "\r\n0\r\n\r\n";
    if(request.fd != 0)
        fillBodyChunked(request);
    fillResponseHeadre(request);
    // std::cout << 
    if(request.sendHeaders == false){
        _resheaders = "";
    }
    _response = _resheaders + _resbody;
}

std::string ssizeToHexToStr(ssize_t chunksize){
    std::stringstream ss;
    ss << std::hex << chunksize;
    std::string hexString = ss.str();

    return hexString;
}
/*To send response with chunked*/
void Response::fillBodyChunked(Http_req &request){
    char buff [R_SIZE];
    ssize_t bytesReceived;
    if(request.fd<0){
        std::cout << "request.fd 4FD ERROR" << std::endl;
        return;
    }
    bytesReceived = read(request.fd, buff, R_SIZE-1);
    if (bytesReceived == -1) 
    {
        std::cout << "read error fill body" << std::endl ;
        close(request.fd);
        return;
    }
    if(bytesReceived == 0)
    {
        _resbody = "\r\n0\r\n\r\n";
        close(request.fd);
        return;
    }
    _resbody = "\r\n"+ssizeToHexToStr(bytesReceived)+"\r\n"+std::string(buff,bytesReceived);

}
std::string Response::getResHeaders()
{
    return _resheaders;
}

std::string Response::getResBody()
{
    return _resbody;
}
std::string Response::getResponse()
{
    return _response;
}

Response::~Response()
{
}