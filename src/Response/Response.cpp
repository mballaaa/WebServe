#include "../../includes/Response/Response.hpp"

Response::Response(){   
}


/*Fill Response Header*/
void Response::fillResponseHeadre(Http_req &request){

    std::map<std::string,std::string>::iterator it1 = request._status.begin();
    std::map<std::string,std::string> h;
    _resheaders = request.getHttpVersion()+" "+it1->first+" "+it1->second+"\r\n";

    h["Transfer-Encoding"] = "chunked";
    h["Connection"] = "Closed";
    h["host"] = "127.0.0.1:9090";

    std::map<std::string,std::string>::iterator it2 = h.begin();
    for(;it2 != h.end();it2++)
        _resheaders += it2->first+": "+it2->second+"\r\n";
}

/*Fill  Resposne Body*/
void Response::fillResponseBody(Http_req &request){
    fillBodyChunked(request);
    fillResponseHeadre(request);
    if(request.sendHeaders == false){
        std::cout << "HEADER FALSE" << std::endl;
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
    char buff [50];
    ssize_t bytesReceived;

    if(request.fd<0){
        std::cout << "request.fdFD ERROR" << std::endl;
        return;
    }

    bytesReceived = read(request.fd, buff, 49);
    if(bytesReceived == 0){
        _resbody = "\r\n0\r\n\r\n";

        std::cout << "TEEEEEEEEEST" << _resbody << std::endl;
        close(request.fd);
        return;
    }
    _resbody = "\r\n"+ssizeToHexToStr(bytesReceived)+"\r\n"+std::string(buff,bytesReceived);

}

void Response::listDirectory(std ::string html)
{
std::ifstream file("www/html/listDirectory.html");
std::string line;
    if(file.is_open()){
        while (getline(file,line))
            html += line+"\n";
    }
    file.close();
    
    _resbody = html;
    
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
#include <cstring>
void Response::send_get(Http_req request)
{
    // std :: cout << "sss\n";
    ///  std ::cout << "baaamam\n";
 if (!request.toHtml.empty()) {
        listDirectory(request.toHtml);
    } else {
        request.file.open(request._target.c_str(), std::ios::binary); // Open the file again
        if (request.file.is_open()) {
            std::string line;
            while (getline(request.file, line)) {
                _resbody += line + "\n";
            }
            request.file.close(); 
        } else {
            
        }
    }
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