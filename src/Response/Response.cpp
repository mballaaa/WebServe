#include "../../includes/Response/Response.hpp"
#include <unistd.h>

Response::Response() : buffer(R_BUFFER_SIZE)
{
    headerSent = false ;
    fileOpened = false ;
}

Response::Response(const Response& obj)
{
    std::cout << "copy" << std::endl ;
    (void) obj ;
    exit(1) ;
}
const Response& Response::operator=(const Response& obj)
{
    std::cout << "= copy" << std::endl ;
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
    _resheaders = request.getHttpVersion()+" "+it1->first+" "+it1->second+"\r\n";

    h["Transfer-Encoding"] = "chunked";
    h["Connection"] = "Closed";
    h["host"] = "127.0.0.1:9090";
    if (request._status.find("302") != request._status.end())
        h["Location"] = " " + request.path + "/" ;
    std::string fileExtension = request._target.substr(request._target.find_last_of('.') + 1);
    std::string contentType;
    if (fileExtension == "html") {
        contentType = "text/html; charset=utf-8";
    } else if (fileExtension == "mp4") {
        contentType = "video/mp4";
    }
    else if (fileExtension=="png" )
    {
        contentType = "image/png";
    }
     
    else {
        contentType = "application/octet-stream";
        contentType = "text/html";
    }
    h["content-type"] = contentType;

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
    // std::ifstream file("www/html/listDirectory.html");
    // std::string line;
    // if (file.is_open())
    // {
        // std::cout << "3ann\n";
        
        // while (getline(file, line))
            // html += line + "\n";
    // }
    // file.close();
    buffer = std::vector<char>(html.begin(), html.end()) ;
    readSize = html.size() ;
    chunkHeader = sizeToHex(readSize) ;
}

void Response::noContent()
{

    readSize = 0 ;
    if (!fileOpened)
    {
        file.open("www/html/204.html", std::ios::binary); // Open the file again
        fileOpened = true ;
    }
    if (file.is_open())
    {
        buffer = std::vector<char>(R_BUFFER_SIZE, 0) ;
        readSize = file.readsome(&buffer[0], buffer.size()) ;
        if (!readSize)
        {
            buffer.clear() ;
            file.close() ;
        }
        chunkHeader = sizeToHex(readSize) ;
        // std::cout << "size hex: " << chunkHeader << std::endl ;
        // std::cout << "chunk: " << std::string(buffer.begin(), buffer.end()) << std::endl ;
    }
    else
    {
        std::cout << "not open" << std::endl ;
        exit(1) ;
    }
}
#include <cstring>
void Response::send_get(Http_req &request)
{
    // std :: cout << "sss\n";
    // std ::cout << "baaamam\n";
    if (!request.toHtml.empty())
    {
        listDirectory(request.toHtml);
        request.toHtml.clear() ;
    }
    else
    {
      
        readSize = 0 ;
        if (!fileOpened)
        {
           
        std ::cout << "jakldjkljmsdfl\n";
            file.open(request._target.c_str(), std::ios::binary); 
          
            fileOpened = true ;
        }
        if (file.is_open())
        {
            std ::cout << "is opeeeeenenenn\n";
            buffer = std::vector<char>(R_BUFFER_SIZE, 0) ;
            readSize = file.readsome(&buffer[0], buffer.size()) ;
            if (!readSize)
            {
                buffer.clear() ;
                file.close() ;
            }
            chunkHeader = sizeToHex(readSize) ;
            // std::cout << "size hex: " << chunkHeader << std::endl ;
            // std::cout << "chunk: " << std::string(buffer.begin(), buffer.end()) << std::endl ;
        }
        else
        {
            std::cout << "not open" << std::endl ;
            exit(1) ;
        }
    }
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