#include "../../includes/Request/Http_req.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

#include <cstring>

static int a = 0;
/*=============== 14 PART (begin)==================*/
Http_req::Http_req() {}
/*=============== 14 PART (end)==================*/
Http_req::Http_req(Server& server)
{
    toHtml = "";
    is_finsh = false;
    this->server = server;
    in_out = false;
    
}



Http_req::Http_req(const Http_req &obj)
{
   
     req = obj.req;
    _target = obj._target;
    method = obj.method;
    path = obj.path;
    http_ver = obj.http_ver;
    header = obj.header;
    server = obj.server;
    _loca = obj._loca;
    byterec = obj.byterec;
    toHtml = obj.toHtml;
    /*=============== 14 PART (begin)==================*/
    _status = obj._status;
    _mime=obj._mime;
    /*=============== 14 PART (end)==================*/
    in_out = obj.in_out ;
    is_close = obj.is_close ;
    bodycount = obj.bodycount ;
}

// copyy
Http_req &Http_req::operator=(const Http_req &obj)
{
    if (this != &obj)
    {

        req = obj.req;
    _target = obj._target;
    method = obj.method;
    path = obj.path;
    http_ver = obj.http_ver;
    header = obj.header;
    server = obj.server;
    _loca = obj._loca;
    byterec = obj.byterec;
    toHtml = obj.toHtml;
    /*=============== 14 PART (begin)==================*/
    _status = obj._status;
    _mime=obj._mime;
    /*=============== 14 PART (end)==================*/
    in_out = obj.in_out ;
    is_close = obj.is_close ;
    bodycount = obj.bodycount ;
    }
    return *this;
}
/*  Getter   */
const std::string &Http_req::getTarget() const
{
    return _target;
}
const std::string &Http_req::getBody() const
{
    return body;
}

const std::string &Http_req::getMethod() const
{
    return method;
}

const std::string &Http_req::getPath() const
{
    return path;
}

const std::string &Http_req::getHttpVersion() const
{
    return http_ver;
}

const std::map<std::string, std::string> &Http_req::getHeader() const
{
    return header;
}

const Server &Http_req::getServer() const
{
    return server;
}

const Location &Http_req::getLocation() const
{
    return _loca;
}
/*=============== 14 PART (begin)==================*/

const std::map<std::string, std::string> &Http_req::getStatus() const
{
    return _status;
}

const bool &Http_req::getFlag() const
{
    return in_out;
}
/*=============== 14 PART (end)==================*/
/*
    structure of request
        ===> start line
        Type(Methode) +Request target
        + HTTP version

        *****2Header

*/
bool comparePaths(const std::string& target, const std::string& key) {
 
   
    size_t j = 0;
    while (j < target.size() && j < key.size() && target[j] == key[j])
        j++;

    return (j == target.size() && j == key.size()) ||
           (j == key.size() && ((j < target.size() && target[j] == '/') || (j > 0 && target[j - 1] == '/')));
}
int check_path(std ::string path)
{

    if (path.empty())
    {
        // return (0);
    }
    if (path.at(0) != '/')
    {
        // return (0);
    }

    return (1);
}
std::string to_stringmetohd(int value)
{
    switch (value)
    {
    case 0:
        return "GET";
    case 2:
        return "POST";
    case 4:
        return "DELETE";
    default:
        return "Unknown Method";
    }
}
std ::string SetRootLoc(std ::string path, std ::string loac_value, std ::string root)
{
    std ::string result;
    // std ::cerr << "==> path:" << path << std ::endl;
    // std ::cerr << "==>locationpath:" << loac_value << std ::endl;
    // std ::cerr << "==>root:" << root << std ::endl;
    size_t it = path.find(loac_value);

    if (it != std ::string::npos)
    {

        // if (path[path.size() - 1] != '/')
        // {
        //     path += "/";
        // }

        path.replace(it, loac_value.length(), root + loac_value);
        return path;
    }
    return path;
}
int Http_req::MoreValidation()
{

    if (!check_path(this->path))
    {

        return 0;
    }
    // /// check method

    if (method != "GET" && method != "POST" && method != "DELETE")
    {

        return (0);
    }
    if (http_ver != "HTTP/1.1")
    {
    // std ::cout << "ddddd2\n";
        return (0);
    }

    // get    max body size  in conf
    size_t maxx_size = this->server.getClientMaxBodySize();
    char *endptr;
    size_t content_len;
    if (header.find("content-length") != header.end())
    {
       // std ::cout << "SSSSSSSSSSSSSSSSSSSSSJDKJDKLFJLKDFJKLDFJKLDFJKLDFKLDFLKFDJLK\n";
        //std ::cout << "sss" << header.find("content-length")->second << std ::endl;
        content_len = strtol(header["content-length"].c_str(), &endptr, 10);
        if (endptr == header["content-length"].c_str())
        {
            // std :: cout << "ddddd\n";
            std::cerr << "Error: Invalid content-length in request." << std::endl;
            return 0;
        }
        (void)content_len;

        if (maxx_size < content_len)
        {
            std :: cout << "dd22dd\n";
            // std :: cout << "ddddd3\n";
            return (0);
        }
    }
    if (header.find("transfer-encoding") != header.end() && header["transfer-encoding"] != " chunked")
    {
       // std :: cout << "dd1dd\n";
       // return (0);
    }

    if (method == "POST" && header.find("content-length") == header.end() && header.find("transfer-encoding") == header.end())
    {
        std :: cout << "dddd\n";
        return (0);
    }
        

    this->_target = this->path;
  
    // now let check if match or not
  std::map<std::string, Location> location = this->server.getLocations();
std::map<std::string, Location>::iterator it;
int flag = 0;
std::string key;
size_t foundSize = 0 ;
for (it = location.begin(); it != location.end(); it++)
{
    key = it->first;

    // if (comparePaths(_target, key))
    if (_target.find(key) != std::string::npos)
    {
        if (foundSize < key.length())
        {
            foundSize = key.length() ;
            this->_loca = it->second;
        }
        flag = 1;
    }
}
 
if (flag == 0)
{
    _status["404"]="Page Not Found";
    std :: cout << "Not match \n";
    return 0;
}


    /// std :: cerr << "weech\n";
    Location::redirection_t red = this->_loca.getReturn();
    //  std :: cerr << red.first << std ::endl;
    //  std :: cerr << red.second << std ::endl;
    if (red.first != 0 && red.second != "")
    {
        this->_target = red.second;
        // return 0;
        // std :: cerr << "tis the path\n" << path << std ::endl;
    }
    // let check allow methode
    Location::Methods_t allowmethod = this->_loca.getAllowedMethods();
    bool is_exit = false;
    (void)is_exit;

    for (size_t i = 0; i < allowmethod.size(); i++)
    {
        // change to stirng
        std ::string get_methode = to_stringmetohd(allowmethod[i]);
        //  std :: cerr << "get methode==>\n" << get_methode << std ::endl;
        if (get_methode == this->method)
        {

            is_exit = true;
            break;
        }
    }
    /// TO DO SHLOUD DO SOMETHING IF ALLOW MEHODE FALSE

    _target = SetRootLoc(_target, key, this->server.getRoot());

    //  std ::cout << "lastttttttttttttttttt =>" << _target << std ::endl;

    return (1);
}
void Http_req::debugFunction()
{
    // std ::cout << "Yesss\n";
    // std ::cout << "our infoo\n";
    // std ::cout << "type mthode=>" << this->method << std ::endl;
    // std ::cout << "path=>" << this->path << std ::endl;
    // std ::cout << "vers=>" << this->http_ver << std ::endl;
    std::ofstream outputFile("output.txt", std::ios_base::app);

    if (outputFile.is_open())
    {
        // Output body to the file
        outputFile << this->body;

        // Close the file
        outputFile.close();
    }
    ///// print headar
    //  std::map<std::string, std::string>::iterator it;
    // for (it = header.begin(); it != header.end(); it++)
    // {

    //      std ::cerr << it->first << ":" << it->second << std ::endl;
    // }
    
        //
    // //std :: cout << "this ===?\n";
    //  std :: cout << this->body << std::endl;
}
 long hex_to_decimal(const std::string& hexString) {
    char* endPtr;
    return strtol(hexString.c_str(), &endPtr, 16);
}
int Http_req::StautRe(std::string request)
{

    //////////////////
   // std ::cout << request << std ::endl;


    std ::string my_req = "";
    // Set flag that can tell us is request are finshied
    if (!is_finsh)
    {
        my_req += request;
    }

    size_t len_req = my_req.find("\r\n\r\n");
    int res;
    res = 0;

    a++;
   

    if (!is_finsh && len_req != std ::string ::npos)
    {

        std::istringstream input(my_req);
        input >> this->method >> this->path >> this->http_ver;

        while (path.find("%") != std::string::npos)
        {
            unsigned int x ;
            std::string hexCode = path.substr(path.find("%")+1, 2) ;
            std::stringstream ss ;
            ss << std::hex << hexCode ;
            ss >> x ;
            path.replace(path.find("%"), 3, std::string(1, x)) ;
        }

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
            // debugFunction();
        }
       
        size_t body_start = len_req + 4;
         this->body = my_req.substr(body_start);
     //    std ::cout << body ;
         
        if (header.find("transfer-encoding") != header.end())
        {
            std :: cout << "sssssssssss\n";
            //
            //std :: cout << "sss\n";
            std ::string sizeChunk;
            size_t startchu = body.find("\r\n");
           
            if (startchu != std ::string::npos)
            {
              //  std :: cout << startchu << std ::endl;

                 sizeChunk = body.substr(0, startchu);
                size_t sizeHex=hex_to_decimal(sizeChunk);
                (void) sizeHex;
                if(header.find("transfer-encoding")->second ==" chunked")
                {
                    body=my_req.substr(body_start+sizeChunk.length()+2);

                }
                
                

            }
        }
       

        is_finsh = true;
    }
    else if (is_finsh)
    {
        this->body = request;
    }

    // std :: cerr << "this body ==>"  <<body << std ::endl;

    if (is_finsh == true)
    {
        // debugFunction();
        if (MoreValidation()==0)
        {
            in_out =true;
            return (0);


        }
    }
    //======> check path

    res = 1;
    return (res);
}

void Http_req::parse_re(std ::string bufer, int bytee)
{
    // std::ofstream outputFile("request.txt", std::ios_base::app);

    // if (outputFile.is_open())
    // {
    //     // Output body to the file
    //     outputFile << bufer;

    //     // Close the file
        
    // }
    // outputFile.close();
    // std :: cout << bufer << std ::endl;
    (void)bufer;
    (void)bytee;

    if (!StautRe(bufer)|| bytee < 0)
    {
       
        in_out = true;
        std ::cout << "Baaaad Request\n";
        return;
    }
    else
    {
         
      
        if (method == "GET")
        {
            // std :: cout << "YEssss\n";
            // std ::cout << "sssss\n"
            LetGet();
        }
        /*=============== 14 PART (begin)==================*/
        else if (method == "POST")
        {
            LetPost();
        }

        /*=============== 14 PART (end)==================*/
    }
}

bool Is_dir(const char *ptr)
{
    // std ::cerr << "ptr==>" << ptr << std ::endl;
    if (!access(ptr, X_OK | R_OK))
    {
        DIR *dir = opendir(ptr);
        if (dir != NULL)
        {
            //  std ::cerr << "Is directory\n";
            return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}
int is_file_dir(std::string uri)
{
    if (Is_dir(uri.c_str()))
        return 0;
    return 1;
}
std ::string getMessage(int code)
{
    switch (code)
    {
    case 400:
        return "Bad Request";
    case 401:
        return "Unauthorized";
    case 403:
        return "Forbidden";
    case 404:
        return "Not Found";
    case 500:
        return "Internal Server Error";
    case 501:
        return "Not Implemented";
    case 503:
        return "Service Unavailable";
    default:
        return "Unknown Error";
    }
}

void Http_req ::CheckLoc(int *is_file)
{
    if (this->_loca.getAutoIndex() && this->_loca.getIndex().size() != 0)
    {
        
        std ::vector<std ::string> index = this->_loca.getIndex();

        // check if index file are exit
        /// ==> get first index string
       // std :: cout << 
      //  std ::cout << this->_loca.getRoot() << std ::endl;

        std ::string main_index = index.at(0);
        // std ::cout << "==>" << this->_loca.getRoot() << std ::endl;

        // std ::cerr << "index  name==>" << main_index << std ::endl;
        //  std ::cout << "==> index" << main_index << std ::endl;
        _target += main_index;
        
      
        in_out = true;
        _status["200"] = "OK";
    
        *is_file=1;
    
    }
    else
    {
        if (!this->_loca.getAutoIndex())
        {
            
            /// Here We shloud Send DirectoryListe
            std ::string dirpath = _target;

            toHtml = "<!DOCTYPE html>\n<html>\n<head>\n<title>Index of " + path + "</title>\n</head>\n<body>\n<h1>Index of " + path + "</h1>\n<pre>";

            DIR *dir = opendir(dirpath.c_str());
            if (!dir)
            {
                perror("auto index issue");
                return;
            }
            else
            {

                struct dirent *list;
                list = readdir(dir);
                while (list != NULL)
                {
                    if (list->d_type == DT_DIR)
                    {
                        toHtml += "<a href=\"" + (std::string(list->d_name)) + "/\">" + std::string(list->d_name) + "/</a> \n";
                    }
                    else if (list->d_type == DT_LNK)
                    {
                        toHtml += "<a href=\"" + (std::string(list->d_name)) + "\">" + std::string(list->d_name) + "</a>\n";
                    }
                    else if (list->d_type == DT_REG)
                    {
                        toHtml += "<a href=\"" + (std::string(list->d_name)) + "\">" + std::string(list->d_name) + "</a> \n";
                    }
                    list = readdir(dir);
                }
                toHtml += "</pre>\n</body>\n</html>";

                closedir(dir);
                in_out = true;
                _status["200"] = "OK";
                return;
            }
        }
        else
        {
            //SendErrorClient(403);
            std :: cout << "Yesss iam here\n";
            in_out = true;
            _status["403"]="Forbidden";
            return;
        }
    }
    
}


void Http_req::LetGet()
{
    
    int is_file=0;
    std ::string URI = this->_target;
    int check_type = is_file_dir(URI);
    // std :: cerr << "output" << check_type << std ::endl;
    if (check_type == IS_DIR)
    {
        

       
        CheckLoc(&is_file);
       
    }
    
       
        struct stat sb;
        
      
        if(stat(URI.c_str(),&sb)==0)
        {
           
            if((sb.st_mode & S_IFREG ) || is_file)
            {
                   
                    _status["200"]="ok";
                    in_out=true;
                    
                    return ;
                 }
                
            }
            else
            {
                
                _status["404"]="Forbidden";
                in_out =true;
                return ;
            }
       
}
   // in_out=true;
   
    //std ::cout << "sssdffd\n";    
/*=============== 14 PART (begin)==================*/
void Http_req::mimeParse()
{
    std::ifstream file("mime.types");
    std::string line;
    std::string key;
    std::string value;

    if (!file.is_open())
    {
        std::cout << "Error : mimes.types could not be open" << std::endl;
        return;
    }

    while (getline(file, line))
    {
        std::istringstream thenewline(line);

        thenewline >> key;
        thenewline >> value;
        if (!value.empty())
        {
            size_t pos = value.find(";");
            if (pos != std::string::npos)
                value.erase(pos);
            _mime[key] = value;
        }
    }
}

void Http_req::contentLenght()
{
}

std::string randNameGen()
{
    srand(time(NULL));
    std::string c = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string name;
    for (int i = 0; i < 5; i++)
        name += c[rand() % (sizeof(c) - 1)];
    return name;
}

void Http_req::LetPost()
{
    /*location not found*/
    // std::cout << body << std::endl;
    if (_loca.getUploadPath() == "Not Found")
    {
        /*Status 404*/
        _status["404"] = "Not Found";
    }
    else if (_loca.getUpload() == true)
    {

        in_out = true;
        mimeParse();

        if (header["content-length"] == " 0")
        {

            /*Status 204*/
            _status["204"] = "No Content";
            return;
        }

        int dirCheck = mkdir("Upload", 0777);

        if (!dirCheck || errno == EEXIST)
        {
            /*First check if the extension exist */
            std::string str;
            if (_mime.find(header["content-type"].substr(1)) != _mime.end())
                str = "Upload/" + randNameGen() + "." + _mime[header["content-type"].substr(1)];
            else
                str = "Upload/" + randNameGen() + ".txt";

            if (header["transfer-encoding"] == " chunked")
            {
                while (body.find("/r/n") != std::string::npos)
                    body.erase(body.find("/r/n"));
            }
            std::ofstream file(str.c_str(), std::ios::app);
            file << body;
            file.close();
        }
        /*Status 201*/
        _status["201"] = "Created";
    }
    else if (_loca.getUpload() == false)
    {
        /*Status 403*/
        _status["403"] = "Forbidden";
    }
    in_out = true;
}

/*=============== 14 PART (end)==================*/

Http_req::~Http_req()
{
}