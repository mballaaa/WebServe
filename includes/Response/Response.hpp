#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include"../Request/Http_req.hpp"
#include"../cgi/Cgi.hpp"

#define R_SIZE 1024

class Response
{
private:
    std::string     _resheaders;
    std::string     _resbody;
    std::string     _response;
public:
    Response();
    
    /*==============Member function===============*/
    std::string getResHeaders();
    std::string getResBody();
    void fillResponseHeadre(Http_req&);
    void fillResponseBody(Http_req&);
    
    Cgi cgi;
    int i;
    
    std::string getResponse();
    /*-------------Body TYPE(begin)-------------*/
    void notFound();
    void forrbiden();
    void fillBodyChunked(Http_req &request);
    void created(Http_req &request);
    void noContent();
    /*start mballa*/
    void listDirectory(std::string);
    void    send_get(Http_req);


    /*End mballa*/

    /*-------------Body TYPE(end)-------------*/

    /*===========================================*/
    
    ~Response();
};



#endif