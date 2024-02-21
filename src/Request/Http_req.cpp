#include "../../includes/Request/Http_req.hpp"


Http_req::Http_req(std ::string req,int byterec)
{
    this->req=req;
    this->byterec=byterec;
    parse_re(req,byterec);
     

    
  
}
/*   
    structure of request
        ===> start line 
        Type(Methode) +Request target
        + HTTP version 
        
        *****2Hedars
        
*/

int StautRe(std::string request)
{
    int res ;
    res=0;
    size_t len_req = request.find("\r\n\r\n");
    if(len_req==std::string::npos)
    {
        perror("Error : ParseRequstHeader <Finding end of request> ");
        return (0);
    }
    std::istringstream input(request);
    input >> this.method;    //keep methode
    input >> this.path;
    
    

}
void Http_req::parse_re(std ::string bufer,int bytee)
{
    (void) bufer;
    (void) bytee;
    

}

Http_req::~Http_req()
{

}
