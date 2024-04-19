#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include"../Request/Http_req.hpp"
class Response
{
private:
    std::string     _resheaders;
    std::string     _resbody;
    std::string     _response;
public:
    Response(Http_req request);
    
    /*==============Member function===============*/
    std::string getResHeaders();
    std::string getResBody();
    void fillResponseHeadre(Http_req);
    void fillResponseBody(Http_req);
    

    std::string getResponse();
    /*-------------Body TYPE(begin)-------------*/
    void notFound();
    void forrbiden();
    void created();
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