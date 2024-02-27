#include "../../includes/Request/Http_req.hpp"

Http_req::Http_req(std ::string req, int byterec, Multiplex::listeners_t listners)
{

    // std :: cout << s.getClientMaxBodySize();

    //  std::map<SOCKET,Server> ::iterator it;

    // for (it =listners.begin() ;it !=listners.end();++it)

    // {

    //     std ::cout << "********* here***********\n";
    //     std :: cout << it->second.getClientMaxBodySize() << std ::endl;
    //     std ::cout << "********* here***********\n";
    std::map<SOCKET, Server>::iterator it;
    
    it = listners.begin();
    
    this->req = req;
    this->byterec = byterec;
    this->server = it->second;
   /// See location 
   std::map<std::string ,Location> getLocation=server.getLocations();
    std::map<std::string ,Location>::iterator it_loc;
    std :: cout << getLocation.size()<< std ::endl;
    for(it_loc = getLocation.begin();it_loc !=getLocation.end();it_loc++)
    {
        std :: cout << it_loc->second << std ::endl;     
    }
    parse_re(req, byterec);
}
/*
    structure of request
        ===> start line
        Type(Methode) +Request target
        + HTTP version

        *****2Header

*/

int check_path(std ::string path)
{

    if (path.empty())
    {
        return (0);
    }
    if (path.at(0) != '/')
    {
        return (0);
    }

    return (1);
}
int Http_req::MoreValidation()
{

    std ::cout << "Yessss\n";

    if (!check_path(this->path))
    {

        return 0;
    }
    /// check method
   

    if (method != "GET" && method != "POST" && method != "DELETE")
    {

        return (0);
    }
    if (http_ver != "HTTP/1.1")
    {

        return (0);
    }

    // get    max body size  in conf
    size_t maxx_size = this->server.getClientMaxBodySize();
    char *endptr;
    if(header.find("content-length")!=header.end())
    {
             size_t content_len = strtol(header["content-length"].c_str(), &endptr, 10);
    if (endptr == header["content-length"].c_str())
    {
        std::cerr << "Error: Invalid content-length in request." << std::endl;
        return 0;
    }
    std ::cout << content_len << std ::endl;


     if(method== "POST"  && header.find("content-length") != header.end()
             && maxx_size < content_len)
        {
                    return (0);
        }
    }
    /// Location Part

   

    return (1);
}
void Http_req::debugFunction()
{
    std ::cout << "our infoo\n";
    std ::cout << "type mthode=>" << this->method << std ::endl;
    std ::cout << "path=>" << this->path << std ::endl;
    std ::cout << "vers=>" << this->http_ver << std ::endl;

    ///// print headar
    std::map<std::string, std::string>::iterator it;
    for (it = header.begin(); it != header.end(); it++)
    {
        if (it->first == "Content-Length")
        {
            std ::cout << "ssssss\n";
        }
        std ::cout << it->first << ":" << it->second << std ::endl;
    }
}
int Http_req::StautRe(std::string request)
{
    int res;
    res = 0;
    size_t len_req = request.find("\r\n\r\n");
    if (len_req == std::string::npos)
    {
        perror("Error : RequstHeader ==>Finding end of request ");
        return (0);
    }

    std::istringstream input(request);
    input >> this->method >> this->path >> this->http_ver;

    std ::string next_line;
    std ::getline(input, next_line);

    while (std::getline(input, next_line, '\n') && next_line != "\r")
    {
        // try to supp all \r in each line we have
        std::string::iterator new_end = std::remove(next_line.begin(), next_line.end(), '\r');
        int distance = std::distance(next_line.begin(), new_end);
        next_line.resize(distance);
        size_t find = next_line.find(":");
        if (find != std::string ::npos)
        {
            std ::string key = next_line.substr(0, find);
            std ::string value = next_line.substr(find + 1, distance);
            for (size_t i = 0; i < key.length(); i++)
            {
                key[i] = std::tolower(key[i]);
            }
            if (header.find(key) != header.end())
            {
                perror("Error : RequstHeader ==>Duplcated");
                return (0);
            }
            header[key] = value;

            /// debug function
        }
    }
    debugFunction();
    //======> check path
    if (MoreValidation())
    {
    }

    res = 1;
    return (res);
}
void Http_req::parse_re(std ::string bufer, int bytee)
{
    (void)bufer;
    (void)bytee;
    if (StautRe(bufer) || bytee < 0)
    {
    }
}

Http_req::~Http_req()
{
}
