#include "../../includes/Response/Response.hpp"
#include <unistd.h>

Response::Response()
{
    headerSent = false ;
    fileOpened = false ;
    _socketfd = -1 ;
}

Response::Response(int _socketfd)
{
    headerSent = false ;
    fileOpened = false ;
    this->_socketfd = _socketfd ;
    std::cout << "Created fd: " << _socketfd << std::endl ;
}

Response::Response(const Response& obj)
{
    //std::cout << "copy" << std::endl ;
    (void) obj ;
}
const Response& Response::operator=(const Response& obj)
{
    //std::cout << "= copy" << std::endl ;
    (void) obj ;
    return (*this) ;
}

std::string sizeToHex(size_t size)
{
    std::stringstream ss ;

    ss << std::hex << size << "\r\n" ;
    return ss.str() ;
}

/*Fill Response Header*/
void Response::fillResponseHeadre(Http_req &request){
    
    std::map<std::string,std::string> h;
    std::stringstream ss;
    ss << request._status;
    _resheaders = "HTTP/1.1 "+ ss.str() +" "+ Http_req::errorTexts[request._status] +"\r\n";
    _resheaders += request.to_file;
    if (request._loca.getReturn().first !=0 &&request._loca.getReturn().second != "")
    {
        h["Location"] = request._loca.getReturn().second ;
    }
      
    std::string fileExtension = request._target.substr(request._target.find_last_of('.') + 1);
    if(!request.CGI_FLAG && request.fd != -1){
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
std::string ssizeToHexToStr(ssize_t chunksize){
    std::stringstream ss;
    ss << std::hex << chunksize;
    std::string hexString = ss.str();

    return hexString;
}

/*Fill  Resposne Body*/
void Response::fillResponseBody(Http_req &request){
    _resbody = "\r\n0\r\n\r\n";
    fillResponseHeadre(request);
    if(request.fd > 0)
        fillBodyChunked(request);
    else if(request.fd == -1)
    {
        if (request._status)
        {
            std::stringstream ss;
            ss << request._status;
            std::string msg = "<body><center><h1>" + ss.str() + " " + Http_req::errorTexts[request._status] + "</h1></center><hr><center>webserv</center></body>" ;
            _resbody = "\r\n"+ssizeToHexToStr(msg.size())+"\r\n"+msg;
        }
        else 
            _resbody = "\r\n0\r\n\r\n";
        request._status = 0 ;
    }
    if(request.sendHeaders == false){
        _resheaders = "";
    }
    _response = _resheaders + _resbody;
}

/*To send response with chunked*/
void Response::fillBodyChunked(Http_req &request){
    char buff [R_BUFFER_SIZE];
    ssize_t bytesReceived;
    if(request.fd<0){
        std::cout << "request.fd 4FD ERROR" << std::endl;
        return;
    }
    bytesReceived = read(request.fd, buff, R_BUFFER_SIZE-1);
    if (bytesReceived == -1|| bytesReceived == 0) 
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
    close(_socketfd) ;
}