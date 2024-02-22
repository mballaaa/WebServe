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
        
        *****2Header
        
*/

int Http_req:: StautRe(std::string request)
{
    int res ;
    res=0;
    size_t len_req = request.find("\r\n\r\n");
    if(len_req==std::string::npos)
    {
        perror("Error : RequstHeader ==>Finding end of request ");
        return (0);
    }
    std::istringstream input(request);
    input >> this->method  >> this->path  >> this->http_ver; 
  
    
    std :: string next_line;
    std ::getline(input,next_line);
  
      while (std::getline(input, next_line,'\n') && next_line!="\r") 
     {
       // try to supp all \r in each line we have
       std::string::iterator new_end=std::remove(next_line.begin(),next_line.end(),'\r');
       int distance=std::distance(next_line.begin(),new_end);
        next_line.resize(distance);
       size_t find=next_line.find(":");
        if(find!= std::string ::npos)
        {
            std ::string key=next_line.substr(0,find);
            std ::string value=next_line.substr(find+1,distance);
            for (size_t i = 0; i < key.length(); i++)
            {
               key[i]= std::tolower(key[i]);
            }
            if(header.find(key)!=header.end())
            {
                 perror("Error : RequstHeader ==>Duplcated");
        return (0);              
            }
            header[key]=value;
            

        }


          
     }



   
    
    res=1;
    return (res);

}
void Http_req::parse_re(std ::string bufer,int bytee)
{
    (void) bufer;
    (void) bytee;
    if(StautRe(bufer))
    {

    }

}

Http_req::~Http_req()
{

}
