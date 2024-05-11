#include "../../includes/Request/Http_req.hpp"
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

#include <cstring>

static int a = 0;
/*=============== 14 PART (begin)==================*/
Http_req::Http_req()
{
    // debugFileAmine.open("debug.log") ;
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
}
/*=============== 14 PART (end)==================*/
Http_req::Http_req(Server &server)
{
    // debugFileAmine.open("debug.log") ;
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    toHtml = "";
    is_finsh = false;
    this->server = server;
    in_out = false;
    CGI_FLAG = false;
    query_string = "";
    fd = 0;
    moreValidationDone = false;
    uploadedFileSize = 0;
    mimeParse();
    sendHeaders = true;
    i = 0;
    lastActive = time(NULL);
    error = false;
}

Http_req::Http_req(const Http_req &obj)
{
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    query_string = obj.query_string;
    req = obj.req;
    _target = obj._target;
    method = obj.method;
    path = obj.path;
    http_ver = obj.http_ver;
    header = obj.header;
    server = obj.server;
    _loca = obj._loca;
    make_name = obj.make_name;
    byterec = obj.byterec;
    toHtml = obj.toHtml;
    i = obj.i;
    body = obj.body;
    sendHeaders = obj.sendHeaders;
    /*=============== 14 PART (begin)==================*/
    _status = obj._status;
    _mime = obj._mime;
    _rmime = obj._rmime;
    fd = obj.fd;
    error = obj.error;
    /*=============== 14 PART (end)==================*/
    in_out = obj.in_out;
    is_close = obj.is_close;
    bodycount = obj.bodycount;
    CGI_FLAG = obj.CGI_FLAG;
    cgiMap = obj.cgiMap;
    GetFIle = obj.GetFIle;
    uploadedFileSize = obj.uploadedFileSize;
    moreValidationDone = obj.moreValidationDone;
}

// copyy
Http_req &Http_req::operator=(const Http_req &obj)
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    if (this != &obj)
    {
        query_string = obj.query_string;

        req = obj.req;
        _target = obj._target;
        method = obj.method;
        path = obj.path;
        http_ver = obj.http_ver;
        header = obj.header;
        server = obj.server;
        _loca = obj._loca;
        make_name = obj.make_name;
        body = obj.body;
        error = obj.error;
        i = obj.i;
        fd = obj.fd;
        // byterec = obj.byterec;
        toHtml = obj.toHtml;
        /*=============== 14 PART (begin)==================*/
        _status = obj._status;
        _mime = obj._mime;
        _rmime = obj._rmime;
        sendHeaders = obj.sendHeaders;
        /*=============== 14 PART (end)==================*/
        in_out = obj.in_out;
        is_close = obj.is_close;
        bodycount = obj.bodycount;
        CGI_FLAG = obj.CGI_FLAG;
        cgiMap = obj.cgiMap;
        GetFIle = obj.GetFIle;
        uploadedFileSize = obj.uploadedFileSize;
        moreValidationDone = obj.moreValidationDone;
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
bool comparePaths(const std::string &target, const std::string &key)
{
    // Check if the target starts with the key
    if (target.compare(0, key.length(), key) != 0)
        return false;

    // If the target is exactly the same as the key or the next character is a '/'
    return (target.length() == key.length() || target[key.length()] == '/');
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
std ::string SetRootLoc(std ::string target, std ::string key, std ::string root)
{
    std ::string result;

    // std::cout << "SetRootLoc" << std::endl ;

    size_t it = target.find(key);

    if (it != std ::string::npos)
    {
        
        target.replace(0, key.length(), root + "/");

        return target;
    }
    return root+target;
}

// replace douplicate '/' in path with one
std::string replaceDuplicateSlash(const std::string &path)
{
    std::string result = path;
    size_t pos = 0;
    while ((pos = result.find("//", pos)) != std::string::npos)
    {
        result.erase(pos, 1);
    }
    return result;
}

// split string by delimiter
std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}
bool IsPathValid(std::string path)
{

    std::string allowed_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~";

    size_t found = path.find_first_not_of(allowed_chars);

    if (found == std::string::npos)
    {

        return false;
    }

    return true;
}

size_t matchLocation(const char *_target, const char *location)
{
    size_t matchCount = 0 ;
    while (*location && *_target && *location == *_target)
    {
        location++ ;
        _target++ ;
        matchCount++ ;
    }
    if (*location != 0)
        return (0) ;
    if (*_target != 0 && *_target != '/' && *--_target != '/')
        return (0) ;
    return matchCount ;
}

int Http_req::MoreValidation()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;

    // /// check method

    if (method != "GET" && method != "POST" && method != "DELETE")
    {std ::cout << "ydes\n";

        _status["400"] = "Bad Request";
        in_out = true;
        return (0);
    }
    if (http_ver != "HTTP/1.1")
    {
        std ::cout << "yes\n";
        _status["400"] = "Bad Request";
        in_out = true;
        return (0);
    }
    if (!IsPathValid(path))
    {
        _status["400"] = "Bad Request";
        in_out = true;
        return 0;
    }
    // get    max body size  in conf
    size_t maxx_size = this->server.getClientMaxBodySize();
    char *endptr;
    size_t content_len;
    if (header.find("content-length") != header.end())
    {
        // std ::cout << "SSSSSSSSSSSSSSSSSSSSSJDKJDKLFJLKDFJKLDFJKLDFJKLDFKLDFLKFDJLK\n";
        // std ::cout << "sss" << header.find("content-length")->second << std ::endl;
        content_len = strtol(header["content-length"].c_str(), &endptr, 10);
        if (endptr == header["content-length"].c_str())
        {
            // std :: cout << "ddddd\n";
            std::cerr << "Error: Invalid content-length in request." << std::endl;
            _status["400"] = "Bad Request";
            return 0;
        }
        (void)content_len;

        if (maxx_size < content_len)
        {
            _status["400"] = "Bad Request";
            in_out = true;
           
            return (0);
        }
    }
   
    if(header.find("host") == header.end())
    {
          _status["400"]="Bad Request";
     
        return (0);
    }
    if (method == "POST" && header.find("content-length") == header.end() && header.find("transfer-encoding") == header.end())
    {
       _status["400"]="Bad Request";
     
        return (0);
    }


    this->_target = this->path;
   
   

 size_t stat = _target.find('?');

    if (stat != std::string ::npos)
     {
       
        _target = _target.substr(0, stat); 
    
         query_string = path.substr(stat + 1, path.length()); 

       
     }



    // now let check if match or not

    std::map<std::string, Location> location = this->server.getLocations();
    std::map<std::string, Location>::iterator it;
    int flag = 0;
    std::string key = "";
    size_t foundSize = 0;
    for (it = location.begin(); it != location.end(); it++)
    {
        size_t count = matchLocation(_target.c_str(), it->first.c_str()) ;  
        if (count && count >= foundSize )
        {
            key = it->first ;
            _loca = it->second ;
            flag = 1 ;
        }
    }

    if (flag == 0)
    {
        std ::cout << "yes1\n";
        _status["404"] = "Forbbiden";
        in_out=true;
        return 0;
    }

    /// std :: cerr << "weech\n";
    Location::redirection_t red = this->_loca.getReturn();
    
    if (red.first != 0 && red.second != "")
    {
        this->_target = red.second;
        std::stringstream ss ;
        ss << red.first ;
        _status[ss.str()]="Redirect1";
        in_out=true;
        return 1;

       
    
    }
    // let check allow methode
    Location::Methods_t allowmethod = this->_loca.getAllowedMethods();
    bool is_exit = false;

    for (size_t i = 0; i < allowmethod.size(); i++)
    {

        // change to stirng
        // debugFileAmine << "std::string to_stringmetohd(int value)" << std::endl ;
        std ::string get_methode = to_stringmetohd(allowmethod[i]);

        //  std :: cerr << "get methode==>\n" << get_methode << std ::endl;
        if (get_methode == this->method)
        {

            is_exit = true;
            break;
        }
    }

    if (!is_exit)
    {

        in_out = true;
        _status["405"] = "Method Not Allowed";
        return 0;
    }
    /// TO DO SHLOUD DO SOMETHING IF ALLOW MEHODE FALSE

    // debugFileAmine << "std ::string SetRootLoc(std ::string path, std ::string loac_value, std ::string root)" << std::endl ;
   // std ::cout << this->_loca.getRoot() << std ::endl;

    _target = SetRootLoc(_target, key, this->_loca.getRoot());
 
     

    // std :: cout << _target << std ::endl;

    // std ::cout << "lastttttttttttttttttt =>" << _target << std ::endl;
    moreValidationDone = 1;
    return (1);
}

void Http_req::debugFunction()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    // std ::cout << "Yesss\n";
    // std ::cout << "our infoo\n";
    // std ::cout << "type mthode=>" << this->method << std ::endl;
    // std ::cout << "path=>" << this->path << std ::endl;
    // std ::cout << "vers=>" << this->http_ver << std ::endl;
    // std::ofstream outputFile("output.txt", std::ios_base::app);

    // if (outputFile.is_open())
    // {
    //     // Output body to the file
    //     outputFile << this->body;

    //     // Close the file
    //     outputFile.close();
    // }
    // ///// print headar
    //  std::map<std::string, std::string>::iterator it;
    // for (it = header.begin(); it != header.end(); it++)
    // {

    //      std ::cerr << it->first << ":" << it->second << std ::endl;
    // }
    //
    // //std :: cout << "this ===?\n";
    //  std :: cout << this->body << std::endl;
}
long hex_to_decimal(const std::string &hexString)
{
    char *endPtr;
    return strtol(hexString.c_str(), &endPtr, 16);
}
int Http_req::StautRe(std::string request)
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;

 

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
        /*amine do this*/
        while (path.find("%") != std::string::npos)
        {
            unsigned int x;
            std::string hexCode = path.substr(path.find("%") + 1, 2);
            std::stringstream ss;
            ss << std::hex << hexCode;
            ss >> x;
            path.replace(path.find("%"), 3, std::string(1, x));
        }
        /*amine finsh*/
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
            debugFunction();
        }

        size_t body_start = len_req + 4;
        this->body = my_req.substr(body_start);
        //    std ::cout << body ;

        is_finsh = true;
    }
    else if (is_finsh)
    {
        this->body = request;
    }

    // std :: cerr << "this body ==>"  <<body << std ::endl;

    if (is_finsh == true)
    {
        if (!moreValidationDone && MoreValidation() == 0)
        {
            
            in_out = true;
            return (0);
        }
    }
    //======> check path

    res = 1;
    // std::map<std::string, std::string>::iterator it = header.begin() ;
    // while (it != header.end())
    // {
    //     std::cout << it->first << "=" << it->second << std::endl ;
    //     it++ ;
    // }
    // exit(0);
    // exit(0);
    return (res);
}
void Http_req::LetDelete()
{

    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    struct stat infoo;
    std::string URI = _target;
    if (stat(_target.c_str(), &infoo) == 0)
    {

        if (S_ISREG(infoo.st_mode))
        {
            // CHECK PERMISSION
            if (infoo.st_mode & S_IWUSR)
            {
                // here have dele file
                if (unlink(URI.c_str()) == 0)
                {

                    _status["204"] = "No Content";
                    in_out = true;
                    return;
                }
            }
            else
            {
                _status["403"] = "Forbidden";
                in_out = true;
                return;
            }
        }
        else if (S_ISDIR(infoo.st_mode))
        {

            if (infoo.st_mode & S_IWUSR)
            {

                bool check = delete_Dir(URI);

                if (!check)
                {
                    in_out = true;
                    return;
                }
                in_out = true;
                _status["204"] = "No Content";
                return;
            }
            else
            {
                _status["403"] = "Forbidden";
                in_out = true;
                return;
            }
        }
    }
    else
    {
        _status["404"] = "Not found";
        in_out = true;
        return;
    }
}

bool Http_req::delete_Dir(std::string pathh)
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    DIR *ptr = opendir(pathh.c_str());

    if (ptr != NULL)
    {

        struct dirent *list;

        while (((list = readdir(ptr)) != NULL))
        {
            std::string filename = list->d_name;
           

            if (filename == "." || filename == "..")
            {
                continue;
            }

            std::string full_path = pathh + "/" + filename;
            struct stat fileStat;

            if (stat(full_path.c_str(), &fileStat) == 0)
            {

                if (S_ISREG(fileStat.st_mode) && (fileStat.st_mode & S_IWUSR))
                {

                    if (unlink(full_path.c_str()) != 0)
                    {

                        perror("Error: Cannot delete file");
                        _status["500"] = "Internal Server Error";
                        closedir(ptr);
                        return false;
                    }
                    _status["204"] = "No Content";
                }
                else if (S_ISDIR(fileStat.st_mode))
                {
                    delete_Dir(full_path);
                }
                else
                {

                    perror("Error: Cannot get file or directory information");
                    _status["500"] = "Internal Server Error";
                    closedir(ptr);
                    return false;
                }
            }
            else
            {
                closedir(ptr);
                _status["500"] = "Internal Server Error";
                return false;
            }
        }

        closedir(ptr);

        if (rmdir(pathh.c_str()) != 0)
        {
            perror("Error : DIRECTOR DELETE");

            return false;
        }
        return true;
    }
    else
    {
        perror("Error : can not open directory");
        _status["403"] = "FOrbideen";
        closedir(ptr);
        return false;
    }

    closedir(ptr);
}

void Http_req::parse_re(std ::string bufer, int bytee)
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    // std::ofstream outputFile("request.txt", std::ios_base::app);

    // std :: cout << bufer << std ::endl;
    (void)bufer;
    (void)bytee;
    
    if (!StautRe(bufer) || bytee < 0)
    {

        in_out = true;
        std ::cout << "Baaaad Request\n";
         std::map<std::string, std::string>::iterator it=_status.begin();
           
        if (fd > 0)
            close(fd);
        if( it->first=="404")
        {
           
             fd = open("www/html/Page not found · GitHub Pages.html", O_RDONLY);
             return ;
        }
       
        fd = open("www/html/400.html", O_RDONLY);
        return;
    }
    else
    {

        if (method == "GET")
        {
           
            LetGet();

            // exit(0);
        }
        /*=============== 14 PART (begin)==================*/
        else if (method == "POST")
        {
            LetPost();
        }
        else if (method == "DELETE")
        {
            LetDelete();
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
            closedir(dir);
            return true;
        }
        closedir(dir);
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

void Http_req ::CheckLoc(int *is_file)
{
    // std ::cout << "debug\n";
    // std ::cout << _target << std ::endl;
   
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    if (path[path.length() - 1] != '/')
    {
        std ::cout << "debug1\n";
        in_out = true;
        _status["302"] = "Redirect2";
        _loca.setReturn("302", path + "/") ;
        return;
    }
    if (this->_loca.getIndex().size() != 0)
    {

        std ::vector<std ::string> index = this->_loca.getIndex();

        std ::string main_index = index.at(0);
        // std ::cout << "==>" << this->_loca.getRoot() << std ::endl;

        // std ::cerr << "index  name==>" << main_index << std ::endl;
        if (_target[_target.length() - 1] != '/')
        {

            _target += "/";
        }
        //  std ::cout << "==> index" << main_index << std ::endl;
        _target += main_index;
        // check if that index is floder shloud trhow error forbiden
        if (is_file_dir(_target) == 0)
        {
            _status["403"] = "Forbbiden";
            fd = open("403.html", std::ios::binary, O_RDONLY);
            in_out = true;
            return;
        }

        *is_file = 1;
    }
    else
    {

        // std ::cout << "adhjdfjdf\n";
        // //std::cout << this->_loca.getIndex().size();
        // std ::cout <<  this->_loca.getAutoIndex() << std ::endl;
        // exit(0);
        
        if (this->_loca.getAutoIndex() && this->_loca.getIndex().size() == 0)
        {

            /// Here We shloud Send DirectoryListe
           

            std ::string dirpath = _target;
            toHtml = "<!DOCTYPE html>\n<html>\n<head>\n<title>Index of " + path + "</title>\n</head>\n<body>\n<h1>Index of " + path + "</h1>\n<pre>";

            DIR *dir = opendir(dirpath.c_str());
            if (!dir)
            {
                closedir(dir);
                perror("auto index issue");
                return;
            }
            else
            {

                struct dirent *list;
                list = readdir(dir);
                // std :: cout << path << std :: endl;
                while (list != NULL)
                {

                    if (std ::string(list->d_name) == "index.html")
                    {

                        _target += std ::string(list->d_name);

                        closedir(dir);
                        return;
                    }
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
                std::ofstream outputFile("output.txt");

                if (!outputFile.is_open())
                {
                    outputFile.close();
                    perror("Error file");
                    exit(1);
                }
                outputFile << toHtml;
                outputFile.close();
                if (fd > 0)
                {
                    //std::cout << "case in get fd >0\n";
                    close(fd);
                }
                fd = open("output.txt", std::ios::binary, O_RDONLY);
                //std::cout << "fd list->> " << fd << std::endl;

                return;
            }
            closedir(dir);
        }
        else
        {
            in_out = true;
            _status["403"] = "Forbidden";
            if (fd > 0)
                close(fd);
            fd = open("www/html/403.html", std::ios::binary, O_RDONLY);
            return;
        }
    }
}

std::string fileExtension(std::string filename)
{
    std::string extension = "";
    size_t p = filename.find_last_of('.');
    if (p != std::string::npos)
        extension = filename.substr(p + 1);
    return extension;
}
void Http_req::LetGet()
{
    // std ::cout << _loca << std ::endl;
   
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    // this condtion here for that stauts come from redirection
    if(!_status.empty())
    {
        return ;
    }
    int is_file = 0;
    // int permisson=0;

    std ::string URI = _target;

    // debugFileAmine << "int is_file_dir(std::string uri)" << std::endl ;
    int check_type = is_file_dir(URI);

    // std :   : cerr << "output" << check_type << std ::endl;

    if (check_type == IS_DIR)
    {

        CheckLoc(&is_file);
        URI = _target;
    }

    struct stat sb;

   

    if (stat(URI.c_str(), &sb) == 0)
    {

        if (this->_loca.getCgi())
        {
        

            //     // cehck extions
            //     // debugFileAmine << "std::string fileExtension(std::string filename)" << std::endl ;
            std ::string extension = fileExtension(URI);
            std ::map<std::string, std ::string> cgiMap = this->_loca.getCgiPaths();
            std ::map<std::string, std::string>::iterator it = cgiMap.find(extension);

            if (it != cgiMap.end())
            {
          
                if (!it->second.empty() )
                {
                    _status["200"] = "OK";
                    CGI_FLAG = true;
                    in_out = true;
                    return;
                }
                else
                {
                    _status["500"] = "Internal Server Error";
                    in_out = true;
                    fd = open("www/html/500.html", O_RDONLY);
                    return;
                }
            }
        
           
            


            // else
            // {

                

            //     _status["404"] = "Forbiden";
            //     in_out = true;
            //      fd = open("www/html/Page not found · GitHub Pages.html", std::ios::binary, O_RDONLY);
            //     return;
            // }

        }

        if ((sb.st_mode & S_IFREG) || is_file)
        {
            
              if (!(sb.st_mode & S_IWUSR)) {
           
            _status["403"] = "Forbidden";
            in_out = true;
           fd =open("www/html/403.html", O_RDONLY);
            return;
        }
            /// wa7d case dyal found index in list directory shloud redirect the index as inginx do
            if (!toHtml.empty())
            {

                _status["200"] = "OK";
                toHtml.clear();
                in_out = true;
                return;
            }

            if (fd > 0)
                close(fd);
          
            fd = open(_target.c_str(), std::ios::binary, O_RDONLY);
            std::cout << "fd get->> " << fd << std::endl;

            _status.clear();
            _status["200"] = "ok";
            std :: cout << "i am here\n";
        
            in_out = true;
            // exit(0);

            return;
        }
    
        // permisiion condition trhow
    }

    else
    {
      
        _status.clear();
        _status["404"] = "Not found";
        // std::cout << "here \n";
        
        fd = open("www/html/Page not found · GitHub Pages.html", std::ios::binary, O_RDONLY);
      
        //std::cout << "fd test =>> " << fd << std::endl;
        in_out = true;
        // exit(0);
        return;
    }
}
// in_out=true;

// std ::cout << "sssdffd\n";
/*=============== 14 PART (begin)==================*/
bool Http_req::dirExistWithPermiss()
{
    struct stat info;
    if (stat(_loca.getUploadPath().c_str(), &info) != 0)
        return false;
    else if (info.st_mode & S_IFDIR)
        return true; 
    return false;
}
int Http_req::mimeParse()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    std::ifstream file("mime.types");
    std::string line;
    std::string key;
    std::string value;

    if (!file.is_open())
    {
        //std::cout << "Error : mimes.types could not be open" << std::endl;
        _status.clear();
        _status["415"] = "Unsupported Media Type";
        fd = open("www/html/415.html", O_RDWR);
        return 1;
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
            if (_rmime[value] == "")
                _rmime[value] = key;
        }
    }
    return 0;
}

std::string Http_req::randNameGen()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    size_t milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(13) << milliseconds;
    std::string name = ss.str();

    return name;
}

int hexStringToInt(const std::string &hexString)
{
    std::stringstream ss;
    ss << std::hex << hexString; // Set the stringstream to interpret input as hexadecimal
    int intValue;
    ss >> intValue; // Extract the integer value
    return intValue;
}

void Http_req::LetPost()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    /*location not found*/
    if (fd > 0)
        close(fd);
    _status.clear();
    if (_loca.getUpload() == true)
    {
        if (dirExistWithPermiss() == false)
        {
            in_out = true;
            error = true;
            _status["404"] = "Not found";
            fd = open("www/html/Page not found · GitHub Pages.html", O_RDWR);
            return;
        }

        if (header["content-length"] == " 0" || header["content-type"] == "")
        {
            /*Status 204*/
            _status["204"] = "No Content";
            in_out = true;
            fd = open("www/html/204.html", O_RDWR);
            return;
        }
            /*First check if the extension exist */
            std::string str;
            if (_mime.find(header["content-type"].substr(1)) != _mime.end() && make_name == ""){
                make_name = _loca.getUploadPath() +"/"+ randNameGen() + "."+ _mime[header["content-type"].substr(1)];
                uploadFile.open(make_name.c_str(), std::ios::app);
            }
            else if(header["content-type"].substr(0,30) == " multipart/form-data; boundary" && make_name == ""){
                make_name = _loca.getUploadPath() +"/"+ randNameGen() + ".txt";
                uploadFile.open(make_name.c_str(), std::ios::app);
                // exit(0);
            }
            else if (make_name == "")
            {
                _status["415"] = "Unsupported Media Type";
                in_out = true;
                error = true;
                fd = open("www/html/415.html", O_RDWR);
                return;
            }

            if (!uploadFile.is_open()) 
            {
                in_out = true;
                _status["403"] = "Permission Denied";
                fd = open("www/html/403.html", O_RDWR);
                error = true;
                std::cout << "File Upload Error" << std::endl;
                return;
            }
            if (header["transfer-encoding"] == " chunked")
            {
                if (!i)
                {
                    classChunksizeString = body.substr(0, body.find("\r\n") + 2);
                    body = body.substr(body.find("\r\n") + 2);
                    chunksize = hexStringToInt(classChunksizeString);
                }
                to_file += body;
                while (chunksize <= to_file.size())
                {
                    if (to_file.find("\r\n", chunksize + 2) != std::string::npos)
                    {
                        std::string correct = to_file.substr(0, chunksize);
                        uploadFile << correct;
                        to_file.erase(0, chunksize + 2);
                        if (to_file.size())
                        {
                            classChunksizeString = to_file.substr(0, to_file.find("\r\n") + 2);
                            chunksize = hexStringToInt(classChunksizeString);
                            to_file.erase(0, classChunksizeString.size());
                        }
                    }
                    else
                        break;
                    if (!chunksize)
                    {
                        in_out = true;
                        uploadFile.close();
                        _status["201"] = "Created";
                        fd = open("www/html/201.html", O_RDWR);
                        return;
                    }
                }
                i = 1;
            }
            else
            {
                uploadedFileSize += body.size();
                size_t fullSize = strtoul(header["content-length"].substr(1).c_str(), NULL, 10);
                
                if (uploadedFileSize >= fullSize)
                {
                    if(uploadedFileSize == fullSize)
                        uploadFile << body;
                    uploadFile.close();
                    in_out = true;
                    _status["201"] = "Created";
                    if (_loca.getCgi() == false){
                        header["content-type"] = "text/html";
                        fd = open("www/html/201.html", O_RDWR);
                    }
                    return;
                }
                uploadFile << body;
                i = 1;
            }
        /*Status 201*/
    }
    else if (_loca.getUpload() == false)
    {
        /*Status 403*/
        _status["403"] = "Forbidden";
        in_out = true;
        fd = open("www/html/403.html", O_RDWR);
        error = true;

    }
    // exit(0);
}

/*=============== 14 PART (end)==================*/

Http_req::~Http_req()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    // debugFileAmine.close() ;
    configFile.close();
    uploadFile.close();
}