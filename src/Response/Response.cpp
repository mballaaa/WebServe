#include "../../includes/Response/Response.hpp"
#include <unistd.h>

Response::Response()
{
    }

/*Fill Response Header*/
void Response::fillResponseHeadre(Http_req &request)
{
 std::map<std::string, std::string>::iterator it1 = request._status.begin();
    std::map<std::string, std::string> h;
    std::stringstream ss;
            ss << _resbody.size();
    
    _resheaders = request.getHttpVersion() + " " + it1->first + " " + it1->second + "\r\n";
    if (request._status.find("302") != request._status.end())
        h["Location"] = " " + request.path + "/" ;
    
    h["content-length"] = ss.str();
    h["connection"] = "closed";
    h["host"] = "127.0.0.1:9090";

    // Determine Content-Type based on file extension
    std::string fileExtension = request._target.substr(request._target.find_last_of('.') + 1);
    std::string contentType;
    if (fileExtension == "html") {
        contentType = "text/html";
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

    //std::map<std ::string, std ::string>::iterator it = request._status.begin();

    // for ((void)it; it != request._status.end(); it++)
    // {
    //     std ::cout << "==>" << it->first << std ::endl;
    // }

        if (request._status.find("200") != request._status.end())
    {

        send_get(request);
    }
    else if (request.CGI_FLAG == false)
    {

        // std::map<std::string,std::string>::iterator it = request._status.begin();
        // std::cout << it->first << std::endl;
        // std::cout << it->second << std::endl;
        std::cout << "ALOOO" << std::endl;

        if (request._status.find("201") != request._status.end())
        {

            std::cout << "ALOOO" << std::endl;

            created();
        }
        else if (request._status.find("403") != request._status.end())
        {
            std ::cout << "3ansd5456465465465nnn\n";
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
    else
        _resbody = request.getBody();
    // std :: cout <<"=>> " << request._status["201"] << std::endl;
            fillResponseHeadre(request);
        _response = _resheaders + _resbody;
}

void Response::created()
{

    std::ifstream file("www/html/201.html");
    std::string line;
    if (file.is_open())
    {
        while (getline(file, line))
            _resbody += line + "\n";
    }
    file.close();
    std::cout << "ALOOO" << std::endl;
    }
void Response::forrbiden()
{

    std::ifstream file("www/html/403.html");
    std::string line;
    if (file.is_open())
    {
        while (getline(file, line))
            _resbody += line + "\n";
    }
    file.close();
    }

void Response::notFound()
{
    std::ifstream file("www/html/Page not found · GitHub Pages.html");
    std::string line;
    if (file.is_open())
    {
        while (getline(file, line))
            _resbody += line + "\n";
    }

    file.close();
    }
void Response::listDirectory(std ::string html)
{
    std::ifstream file("www/html/listDirectory.html");
    std::string line;
    if (file.is_open())
    {
        while (getline(file, line))
            html += line + "\n";
    }
    file.close();

    _resbody = html;
}

void Response::noContent()
{

    std::ifstream file("www/html/204.html");
    std::string line;
    if (file.is_open())
    {
        while (getline(file, line))
            _resbody += line + "\n";
    }
    file.close();
    }
#include <cstring>
void Response::send_get(Http_req request)
{
    // std :: cout << "sss\n";
    ///  std ::cout << "baaamam\n";
    if (!request.toHtml.empty())
    {
        listDirectory(request.toHtml);
    }
    else
    {
                request.file.open(request._target.c_str(), std::ios::binary); // Open the file again
        if (request.file.is_open())
        {
            std::string line;
            while (getline(request.file, line))
            {
                _resbody += line + "\n";
            }
            request.file.close();
        }
        else
        {
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