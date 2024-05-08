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
    i = 0 ;
    moreValidationDone = false ;
    uploadedFileSize = 0 ;
    configFile.open("./src/Cgi/pathExecutableFile.txt");
        mimeParse();
    sendHeaders = true;
    i  = 0;
    
}

Http_req::Http_req(const Http_req &obj)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl ;
    query_string = obj.query_string;
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
    i = obj.i;
    body = obj.body;
    sendHeaders = obj.sendHeaders;
    /*=============== 14 PART (begin)==================*/
    _status = obj._status;
    _mime=obj._mime;
    fd = obj.fd;
    /*=============== 14 PART (end)==================*/
    in_out = obj.in_out;
    is_close = obj.is_close;
    bodycount = obj.bodycount;
    CGI_FLAG = obj.CGI_FLAG;
    cgiMap = obj.cgiMap;
    GetFIle = obj.GetFIle;
    uploadedFileSize = obj.uploadedFileSize ;
    moreValidationDone = obj.moreValidationDone ;
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
        i = obj.i;
        fd = obj.fd;
        // byterec = obj.byterec;
        toHtml = obj.toHtml;
        /*=============== 14 PART (begin)==================*/
        _status = obj._status;
        _mime = obj._mime;
        sendHeaders = obj.sendHeaders;
        /*=============== 14 PART (end)==================*/
        in_out = obj.in_out;
        is_close = obj.is_close;
        bodycount = obj.bodycount;
        CGI_FLAG = obj.CGI_FLAG;
        cgiMap = obj.cgiMap;
        GetFIle = obj.GetFIle;
        uploadedFileSize = obj.uploadedFileSize ;
        moreValidationDone = obj.moreValidationDone ;
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
std ::string SetRootLoc(std ::string path, std ::string loac_value, std ::string root)
{
    std ::string result;

    // std::cout << "SetRootLoc" << std::endl ;
    // std::cout << "path: " << path << std::endl ;
    // std::cout << "loac_value: " << loac_value << std::endl ;
    // std::cout << "root: " << root << std::endl ;
   
    size_t it = path.find(loac_value);

    if (it != std ::string::npos)
    {
        path.replace(0, loac_value.length(), root+loac_value);
        std ::cout << path << std::endl;
        return path;
    }
    return path;

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

int Http_req::MoreValidation()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;

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
        // std ::cout << "sss" << header.find("content-length")->second << std ::endl;
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
            std ::cout << "3azziii\n";
            exit(0);
            // std :: cout << "ddddd3\n";
            return (0);
        }
    }
    // if (header.find("transfer-encoding") != header.end() && header["transfer-encoding"] != " chunked")
    // {
    //     ;
    //     return (0);
    // }

    if (method == "POST" && header.find("content-length") == header.end() && header.find("transfer-encoding") == header.end())
        return (0);

    this->_target = this->path;
    // no we have to check for quesry string;

    // size_t stat=path.find('?');
    // if (stat != std::string ::npos)
    // {
    // 	_target=path.substr(0,stat);
    //     query_string=_target.substr(stat+1,_target.length());
    // }

    // now let check if match or not
  std::map<std::string, Location> location = this->server.getLocations();
std::map<std::string, Location>::iterator it;
int flag = 0;
std::string key = "";
size_t foundSize = 0;

std::vector<std::string> splittedTarget = split(_target, '/');
for (it = location.begin(); it != location.end(); it++)
{
    _target = replaceDuplicateSlash(_target);

   

    std::vector<std::string> splittedLocationPath = split(it->first, '/');

    size_t count = 0;
    size_t shorterLength = std::min(splittedLocationPath.size(), splittedTarget.size());
    for (size_t i = 0; i < shorterLength; ++i)
    {
        if (splittedLocationPath[i] == splittedTarget[i])
        {
            count++;
        }
        else
        {
           
            break;
        }
        if (count > foundSize)
        {
            foundSize = count;
            this->_loca = it->second;
            key = it->first;
            flag = 1;
        }
    }
}


if (flag == 0)
{
    _status["404"] = "Page Not Found";
    std::cout << "Not match \n";
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
        // debugFileAmine << "std::string to_stringmetohd(int value)" << std::endl ;
        std ::string get_methode = to_stringmetohd(allowmethod[i]);
        //  std :: cerr << "get methode==>\n" << get_methode << std ::endl;
        if (get_methode == this->method)
        {

            is_exit = true;
            break;
        }
    }
    // if(!is_exit)
    // {
    //     std ::cout << "sssssss\n";
    //     exit(0);
    //     in_out=true;
    //     _status["403"]="NOt allowed";
    //     return 0 ;
    // }
    /// TO DO SHLOUD DO SOMETHING IF ALLOW MEHODE FALSE

    // debugFileAmine << "std ::string SetRootLoc(std ::string path, std ::string loac_value, std ::string root)" << std::endl ;
    _target = SetRootLoc(_target, key, this->_loca.getRoot());
    //std :: cout << _target << std ::endl;

    std ::cout << "lastttttttttttttttttt =>" << _target << std ::endl;
    moreValidationDone = 1 ;
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
            /*amine do this*/
        while (path.find("%") != std::string::npos)
        {
            unsigned int x ;
            std::string hexCode = path.substr(path.find("%")+1, 2) ;
            std::stringstream ss ;
            ss << std::hex << hexCode ;
            ss >> x ;
            path.replace(path.find("%"), 3, std::string(1, x)) ;
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
            std ::cout << "dddddd\n";
            in_out = true;
            return (0);
        }
    }
    //======> check path

    res = 1;
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
                _status["403"] = "Forbbiden";
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
                _status["403"] = "Forbbiden";
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
            std ::cout << filename << std ::endl;

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
        _status["403"] = "Not Found";
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
        _status.clear();
        _status["400"] = "Bad request";
        // _status.clear();
        header["content-lenght"] = "0";
        // body = "BADD";
        return;
    }
    else
    {

        if (method == "GET")
        {
            
            LetGet();
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
            closedir(dir);

            //  std ::cerr << "Is directory\n";
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
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    std ::cout << _loca << std ::endl;
    if (this->_loca.getIndex().size() != 0 )
    {
    
     
        std ::vector<std ::string> index = this->_loca.getIndex();
        

        std ::string main_index = index.at(0);
        // std ::cout << "==>" << this->_loca.getRoot() << std ::endl;

        // std ::cerr << "index  name==>" << main_index << std ::endl;
        if(_target[_target.length()-1] != '/' )
        {
            
           _target+="/";
        }
        //  std ::cout << "==> index" << main_index << std ::endl;
        _target += main_index;
        // check if that index is floder shloud trhow error forbiden
        if(is_file_dir(_target)==0)
        {
            _status["403"]="Forbbiden";
         in_out=true;
         return ;
        }

        *is_file = 1;
    }
    else
    {
        // std ::cout << "adhjdfjdf\n";
        // std::cout << this->_loca.getIndex().size();
        // std ::cout <<  this->_loca.getAutoIndex() << std ::endl;
        // exit(0);
       
      
        if (this->_loca.getAutoIndex() && this->_loca.getIndex().size()==0)
        {
          
          std :: cout << "jkladjlasdklsf\n";
            
            /// Here We shloud Send DirectoryListe
            // std ::cout << _target << std ::endl;
            std ::string dirpath = _target;
            std ::cout << dirpath << std ::endl;
            toHtml = "<!DOCTYPE html>\n<html>\n<head>\n<title>Index of " + path + "</title>\n</head>\n<body>\n<h1>Index of " + path + "</h1>\n<pre>";

            DIR *dir = opendir(dirpath.c_str());
            if (!dir)
            {
                perror("auto index issue");
              closedir(dir);
                return;
            }
            else
            {
                struct dirent *list;
                list = readdir(dir);
                // std :: cout << path << std :: endl;
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
             closedir(dir);
        }
        else
        {
           

            // SendErrorClient(403);
           
            in_out = true;
            _status["403"] = "Forbidden";
            return;
        }
    }
}

bool Http_req::loadCGIMap()
{
    if (!cgiMap.empty())
        return true;
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;

    if (configFile.is_open())
    {
        std::string line;
        while (std::getline(configFile, line))
        {
            std::istringstream iss(line);
            std::string ext, path;
            if (iss >> ext >> path)
            {
                cgiMap[ext] = path;
            }
        }
    }
    else
    {
        perror("Error: Unable to open configuration file");
        _status.clear();
        _status["403"] = "Forbidden";
        in_out = true;
        return false;
    }
    return true ;
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
    _status.clear();
    loadCGIMap();
        // exit(0);
   

    int is_file = 0;
   // int permisson=0;
  
    std ::string URI = _target;
    std ::cout << URI << std ::endl;
   
    // debugFileAmine << "int is_file_dir(std::string uri)" << std::endl ;
    int check_type = is_file_dir(URI);

  
    // std :: cerr << "output" << check_type << std ::endl;
 

    if (check_type == IS_DIR)
    {
       
        
        CheckLoc(&is_file);
        URI=_target;
    }
   
   
    

    struct stat sb;
 
 std ::cout << URI << std ::endl;
    if (stat(URI.c_str(), &sb) == 0)
    {
        if (this->_loca.getCgi())
        {
         
            // cehck extions
            // debugFileAmine << "std::string fileExtension(std::string filename)" << std::endl ;
            std ::string extension = fileExtension(URI);
           // std ::cout << "extension: " << extension << std ::endl;
            if (extension == "php" || extension == "python")
            {
                std ::map<std::string, std::string>::iterator it = cgiMap.find(extension);
                if (it != cgiMap.end())
                {
                    std::string executable = it->second;

                    if (executable == "/usr/bin/php" || executable == "/usr/bin/python3")
                    {
                        std ::cout << "yesss\n";
                        _status["200"] = "OK";
                        CGI_FLAG = true;

                        in_out = true;
                        return;
                    }

                    else
                    {
                        _status.clear();
                        _status["403"] = "permission denied";
                        fd = open(_target.c_str(),std::ios::binary,O_RDONLY );
                        return;
                    }
                }
            }
        }

        if ((sb.st_mode & S_IFREG) || is_file)
        {
          

        
          _status.clear();
            fd = open(_target.c_str(),std::ios::binary,O_RDONLY );
            std::cout << "->> " << fd << std::endl;
            // exit(0);
            _status["200"] = "ok";
            in_out = true;

            return;
        }
    }

    else
    {
        
        _status.clear();
        _status["404"] = "Not found";
        std::cout << "here \n";
        fd = open("www/html/Page not found · GitHub Pages.html",std::ios::binary,O_RDONLY);
        std::cout << "fd test =>> " << fd << std::endl;
        in_out = true;
        // exit(0);
        return;
    }
}
// in_out=true;

// std ::cout << "sssdffd\n";
/*=============== 14 PART (begin)==================*/
int Http_req::mimeParse()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
        std::ifstream file("mime.types");
    std::string line;
    std::string key;
    std::string value;

    if (!file.is_open())
    {
        std::cout << "Error : mimes.types could not be open" << std::endl;
        _status.clear();
        _status["415"] = "Unsupported Media Type";
        fd = open("www/html/415.html",O_RDWR);
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
    std::string name =ss.str(); 

    return name;
}

int hexStringToInt(const std::string& hexString) {
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
    if (_loca.getUpload() == true)
    {
        
        if (header["content-length"] == " 0" || header["content-type"] == "")
        {
            /*Status 204*/
            _status["204"] = "No Content";
            in_out = true;
            fd = open("www/html/204.html",O_RDWR);
            return;
        }
        int dirCheck = mkdir("Upload", 0777);

        if (!dirCheck || errno == EEXIST)
        {
            /*First check if the extension exist */
            std::string str;
            if (_mime.find(header["content-type"].substr(1)) != _mime.end() && make_name == "")
                make_name = "Upload/" + randNameGen() + "." + _mime[header["content-type"].substr(1)];
            else if(make_name == "")
            {
                _status.clear();
                _status["415"] = "Unsupported Media Type";
                in_out = true;
                fd = open("www/html/415.html",O_RDWR);
                return;
            }

            std::ofstream file(make_name.c_str(), std::ios::app);
            
            if(!file.is_open()){
                std::cout << "File Upload Error" << std::endl;
                return ;
            }
            if(header["transfer-encoding"] == " chunked"){
                if(!i){
                    classChunksizeString = body.substr(0,body.find("\r\n")+2);
                    body = body.substr(body.find("\r\n")+2);
                    chunksize = hexStringToInt(classChunksizeString);
                }
                to_file += body;
                while(chunksize<=to_file.size()){
                    if(to_file.find("\r\n",chunksize+2) != std::string::npos){
                        std::string correct = to_file.substr(0,chunksize);
                        file << correct;
                        to_file.erase(0,chunksize+2);
                        if(to_file.size()){
                            classChunksizeString = to_file.substr(0,to_file.find("\r\n")+2);
                            chunksize = hexStringToInt(classChunksizeString);
                            to_file.erase(0,classChunksizeString.size());
                        }
                    }
                    else
                        break;
                    if(!chunksize){
                        in_out = true;
                        _status["201"] = "Created";
                        header["content-type"] = "text/html";
                        file.close();
                        if(_loca.getCgi() == false)
                            fd = open("www/html/201.html",O_RDWR);
                        break;
                    }
                }
                i=1;
            }
            else
            {
                uploadedFileSize += body.size() ;
                file << body;
                file.close();
                size_t fullSize = strtoul(header["content-length"].substr(1).c_str(), NULL, 10) ;
                if (uploadedFileSize == fullSize)
                {
                    in_out = true;
                    _status["201"] = "Created";
                    header["content-type"] = "text/html";
                    if(_loca.getCgi() == false)
                            fd = open("www/html/201.html",O_RDWR);
                }
                i = 1;
            }
        }
        /*Status 201*/
    }
    else if (_loca.getUpload() == false)
    {
        /*Status 403*/
        _status["403"] = "Forbidden";
    }
}

/*=============== 14 PART (end)==================*/

Http_req::~Http_req()
{
    // debugFileAmine << __PRETTY_FUNCTION__ << std::endl ;
    // debugFileAmine.close() ;
    configFile.close() ;
    uploadFile.close() ;
    file.close() ;
}