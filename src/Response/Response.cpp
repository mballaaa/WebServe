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
void Response::fillResponseHeadre(Http_req &request)
{
 std::map<std::string, std::string>::iterator it1 = request._status.begin();
    std::map<std::string, std::string> h;
    // std::stringstream ss;
    //         ss << _resbody.size();
    
    _resheaders = request.getHttpVersion() + " " + it1->first + " " + it1->second + "\r\n";
    if (request._status.find("302") != request._status.end())
        h["Location"] = " " + request.path + "/" ;
    
    // h["content-length"] = ss.str();
    h["Transfer-Encoding"] = "chunked";
    h["Connection"] = "Keep-Alive";
    // h["connection"] = "closed";
    // h["host"] = "127.0.0.1:9090";

    // Determine Content-Type based on file extension
    std::string fileExtension = request._target.substr(request._target.find_last_of('.') + 1);
    std::string contentType;
    if (fileExtension == "html") {
        contentType = "text/html; charset=utf-8";
    } else if (fileExtension == "mp4") {
        contentType = "video/mp4";
    } else {
        contentType = "application/octet-stream";
        contentType = "text/html";
    }
    h["content-type"] = contentType;

    std::map<std::string, std::string>::iterator it2 = h.begin();
    for (; it2 != h.end(); it2++)
        _resheaders += it2->first + ": " + it2->second + "\r\n";

    _resheaders += "\r\n";
}

/*Fill  Resposne Body*/
void Response::fillResponseBody(Http_req &request)
{

   
    if (request._status.find("200") != request._status.end())
    {
        send_get(request);
        ///std ::cout << "ddfdfsdfsfd\n";
    }
    else if (request.CGI_FLAG == false)
    {
   

        if (request._status.find("201") != request._status.end())
        {

            // std::cout << "ALOOO" << std::endl;

            created();
        }
        else if (request._status.find("403") != request._status.end())
        {
           
            // exit(0);

            forrbiden();
        }
        else if (request._status.find("404") != request._status.end())
            notFound();
        else if (request._status.find("204") != request._status.end())
            noContent();
        else if (request._status.find("302") != request._status.end())
            noContent();
    }
    // else
    //     _resbody = request.getBody();
    // std :: cout <<"=>> " << request._status["201"] << std::endl;
    // _response = _resheaders + _resbody;
}

void Response::created()
{
    readSize = 0 ;
    if (!fileOpened)
    {
        file.open("www/html/201.html", std::ios::binary); // Open the file again
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
void Response::forrbiden()
{
    readSize = 0 ;
    if (!fileOpened)
    {
        file.open("www/html/403.html", std::ios::binary); // Open the file again
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

void Response::notFound()
{
    readSize = 0 ;
    if (!fileOpened)
    {
        file.open("www/html/Page not found · GitHub Pages.html", std::ios::binary); // Open the file again
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
            std::cout << request._target << std::endl;
            file.open(request._target.c_str(), std::ios::binary); 
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