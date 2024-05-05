#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include"../Request/Http_req.hpp"
#include"../cgi/Cgi.hpp"

#define R_BUFFER_SIZE 4096

class Response
{
private:
    std::string     _resbody;
    std::string     _response;
public:
    std::string chunkHeader ;
    std::vector<char>   buffer ;
    bool            fileOpened ;
    std::string     _resheaders;
    bool            headerSent ;
    std::ifstream   file ;
    size_t          readSize ;
    Response();
    Response(const Response& obj);
    const Response& operator=(const Response& obj);
    /*==============Member function===============*/
    std::string getResHeaders();
    std::string getResBody();
    void fillResponseHeadre(Http_req&);
    void fillResponseBody(Http_req&);
    
    Cgi cgi;
    std::string getResponse();
    /*-------------Body TYPE(begin)-------------*/
    void notFound();
    void forrbiden();
    void created();
    void noContent();
    /*start mballa*/
    void listDirectory(std::string);
    void    send_get(Http_req&);


    /*End mballa*/

    /*-------------Body TYPE(end)-------------*/

    /*===========================================*/
    
    ~Response();
};



#endif