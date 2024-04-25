#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include"../Request/Http_req.hpp"
#include"../cgi/Cgi.hpp"
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
    std::string getResponse();
    /*-------------Body TYPE(begin)-------------*/
    void notFound();
    void forrbiden();
    void created();
    void noContent();

    /*-------------Body TYPE(end)-------------*/

    /*===========================================*/
    
    ~Response();
};



#endif