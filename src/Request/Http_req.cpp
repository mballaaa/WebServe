#include "../../includes/Request/Http_req.hpp"
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <cstring>

#include <cstring>

std::map<int, std::string> Http_req::errorTexts ;

void Http_req::initErrorTexts()
{
    errorTexts[0] = "Internal" ;
    errorTexts[100] = "Continue" ;
    errorTexts[101] = "Switching protocols" ;
    errorTexts[102] = "Processing" ;
    errorTexts[103] = "Early Hints" ;
    errorTexts[200] = "OK" ;
    errorTexts[201] = "Created" ;
    errorTexts[202] = "Accepted" ;
    errorTexts[203] = "Non-Authoritative Information" ;
    errorTexts[204] = "No Content" ;
    errorTexts[205] = "Reset Content" ;
    errorTexts[206] = "Partial Content" ;
    errorTexts[207] = "Multi-Status" ;
    errorTexts[208] = "Already Reported" ;
    errorTexts[226] = "IM Used" ;
    errorTexts[300] = "Multiple Choices" ;
    errorTexts[301] = "Moved Permanently" ;
    errorTexts[302] = "Found (Previously \"Moved Temporarily\")" ;
    errorTexts[303] = "See Other" ;
    errorTexts[304] = "Not Modified" ;
    errorTexts[305] = "Use Proxy" ;
    errorTexts[306] = "Switch Proxy" ;
    errorTexts[307] = "Temporary Redirect" ;
    errorTexts[308] = "Permanent Redirect" ;
    errorTexts[400] = "Bad Request" ;
    errorTexts[401] = "Unauthorized" ;
    errorTexts[402] = "Payment Required" ;
    errorTexts[403] = "Forbidden" ;
    errorTexts[404] = "Not Found" ;
    errorTexts[405] = "Method Not Allowed" ;
    errorTexts[406] = "Not Acceptable" ;
    errorTexts[407] = "Proxy Authentication Required" ;
    errorTexts[408] = "Request Timeout" ;
    errorTexts[409] = "Conflict" ;
    errorTexts[410] = "Gone" ;
    errorTexts[411] = "Length Required" ;
    errorTexts[412] = "Precondition Failed" ;
    errorTexts[413] = "Payload Too Large" ;
    errorTexts[414] = "URI Too Long" ;
    errorTexts[415] = "Unsupported Media Type" ;
    errorTexts[416] = "Range Not Satisfiable" ;
    errorTexts[417] = "Expectation Failed" ;
    errorTexts[418] = "I'm a Teapot" ;
    errorTexts[421] = "Misdirected Request" ;
    errorTexts[422] = "Unprocessable Entity" ;
    errorTexts[423] = "Locked" ;
    errorTexts[424] = "Failed Dependency" ;
    errorTexts[425] = "Too Early" ;
    errorTexts[426] = "Upgrade Required" ;
    errorTexts[428] = "Precondition Required" ;
    errorTexts[429] = "Too Many Requests" ;
    errorTexts[431] = "Request Header Fields Too Large" ;
    errorTexts[451] = "Unavailable For Legal Reasons" ;
    errorTexts[500] = "Internal Server Error" ;
    errorTexts[501] = "Not Implemented" ;
    errorTexts[502] = "Bad Gateway" ;
    errorTexts[503] = "Service Unavailable" ;
    errorTexts[504] = "Gateway Timeout" ;
    errorTexts[505] = "HTTP Version Not Supported" ;
    errorTexts[506] = "Variant Also Negotiates" ;
    errorTexts[507] = "Insufficient Storage" ;
    errorTexts[508] = "Loop Detected" ;
    errorTexts[510] = "Not Extended" ;
    errorTexts[511] = "Network Authentication Required" ;
}

/*=============== 14 PART (begin)==================*/
Http_req::Http_req()
{
}
/*=============== 14 PART (end)==================*/
Http_req::Http_req(std::vector<Server> &servers)
{
    toHtml = "";
    is_finsh = false;
    this->server = servers[0];
    this->servers = servers ;
    in_out = false;
    CGI_FLAG = false;
    query_string = "";
    fd = -2;
    moreValidationDone = false;
    uploadedFileSize = 0;
    mimeParse();
    sendHeaders = true;
    i = 0;
    lastActive = time(NULL);
    error = false;
    _status = 0 ;
}

Http_req::Http_req(const Http_req &obj)
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

const int &Http_req::getStatus() const
{
    return _status;
}

const bool &Http_req::getFlag() const
{
    return in_out;
}

const std::string Http_req::getErrorPage( void )
{
    return server.getErrorPage(_status) ;
} 

/*=============== 14 PART (end)==================*/
/*
    structure of request
        ===> start line
        Type(Methode) +Request target
        + HTTP version

        *****2Header

*/


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
    size_t it = target.find(key);

    if (it != std ::string::npos)
    {
        target.replace(0, key.length(), root + key);
        return target;
    }
    return root+target;
}

// replace douplicate '/' in path with one
std::string replaceDuplicateSlash(const std::string &path)
{
    std::string result = path;
    size_t pos = 0;
    while ((pos = result.find("/", pos)) != std::string::npos)
    {
        if (result[pos+1] == '/') // "//"
        {
            result.erase(pos, 1);
        }
        else if (result[pos+1] == '.')
        {
            if (result[pos+2] == '.' && (result[pos+3] == '/' || result[pos+3] == 0)) // ".."
            {
                size_t erase_start = 0 ;
                if (pos)
                    erase_start = result.rfind("/", pos - 1) ;
                result.erase(erase_start, result.find("/..") - erase_start + 3) ;
            }
            else if (result[pos+2] == '/' || result[pos+2] == 0)  // "."
            {
                result.erase(pos, 2) ;
            }
            else
                pos++ ;
        }
        else
            pos++ ;
    }
    if (result == "")
        return "/" ;
    return result;
}

void    Http_req::matchServer( void )
{
    std::vector<Server>::iterator servIt = servers.begin() ;
    while (servIt != servers.end())
    {
        std::vector<std::string>::const_iterator serverName = servIt->getServerNames().begin() ;
        while (serverName != servIt->getServerNames().end())
        {
            if (header["host"].substr(0, header["host"].find(":")) == *serverName)
            {
                server = *servIt ;
                return ;
            }
            serverName++ ;
        }
        servIt++ ;
    }
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
    // check method
    
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
        _status = 403;
        in_out=true;
        return 0;
    }
    Location::redirection_t red = this->_loca.getReturn();
    if (red.first != 0 && red.second != "")
    {
        _status = red.first;
        in_out=true;
        return 1;
    }
    // let check allow methode
    Location::Methods_t allowmethod = this->_loca.getAllowedMethods();
    bool is_exit = false;
    for (size_t i = 0; i < allowmethod.size(); i++)
    {
        // change to stirng
        std ::string get_methode = to_stringmetohd(allowmethod[i]);
        
        if (get_methode == this->method)
        {
            is_exit = true;
            break;
        }
    }

    if (!is_exit)
    {
       
        in_out = true;
        _status = 405;
        return 0;
    }
    _target = SetRootLoc(_target, key, this->_loca.getRoot());
    moreValidationDone = 1;
    return (1);
}


std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(0, s.find_first_not_of(t));
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

int Http_req::StautRe(std::string request)
{
    // Set flag that can tell us is request are finshied
    if (!is_finsh)
    {
        my_req += request;
    }

    size_t len_req = my_req.find("\r\n\r\n");

    if (!is_finsh && len_req != std ::string ::npos)
    {
        std::istringstream input(my_req);
        input >> this->method >> this->path >> this->http_ver;
        path = replaceDuplicateSlash(path) ;
       
        
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
                if (value.empty())
                {
                    _status = 400;
                    in_out = true;
                    return (0);
                }
                for (size_t i = 0; i < key.length(); i++)
                {
                    key[i] = std::tolower(key[i]);
                }
                if (header.find(key) != header.end())
                {
                    perror("Error : RequstHeader ==>Duplcated");
                    return (0);
                }
                header[key] = trim(value);
            }
            else
            {
                _status = 400;
                in_out = true;
                return (0);
            }
        }
        size_t body_start = len_req + 4;
        this->body = my_req.substr(body_start);

        if (method != "GET" && method != "POST" && method != "DELETE")
        {
            _status =  501;
            in_out = true;
            return (0);
        }
        if (http_ver != "HTTP/1.1")
        {
            _status = 400;
            in_out = true;
            return (0);
        }
 
        if(header.find("host") == header.end())
        {
            
            _status = 400;
        
            return (0);
        }
        matchServer() ;

   
        size_t maxx_size = this->server.getClientMaxBodySize();
        char *endptr;
        size_t content_len;
        if (header.find("content-length") != header.end())
        {
            content_len = strtol(header["content-length"].c_str(), &endptr, 10);
            if (endptr == header["content-length"].c_str())
            {
                _status = 400;
                return 1;
            }
            if (maxx_size < content_len)
            {
                _status = 413;
                in_out = true;
            return (0);
            }
        }
        if (header.find("transfer-encoding") != header.end() && header["transfer-encoding"] != "chunked")
        {
            _status=400;
            return (0);
        }

        if (method == "POST" && header.find("content-length") == header.end() && header.find("transfer-encoding") == header.end())
        {
        _status = 411;
            return (0);
        }
        if(method=="POST"  && header.find("content-length") != header.end() && header.find("transfer-encoding") != header.end())
        {

        _status=  400;
        return (0);
        }
        this->_target = this->path;
        size_t stat = _target.find('?');
        if (stat != std::string ::npos)
        {
            _target = _target.substr(0, stat); 
            query_string = path.substr(stat + 1, path.length()); 
        }
        if(path.length() > 2048)
        {
            _status=413;
            return (0);
        }
        is_finsh = true;
    }
    else if (is_finsh)
    {
        if(this->method != "GET"  && this->method !="DELETE")
            this->body = request;
    }
    if (is_finsh == true)
    {
        if (!moreValidationDone && MoreValidation() == 0)
        {
            return (0);
        }
    }
   
    return (1);
}
void Http_req::LetDelete()
{
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
                    _status = 204 ;
                    in_out = true;
                    return;
                }
                else
                {
                    _status = 403 ;
                    if(fd > 0)
                        close(fd);
                    fd=open(getErrorPage().c_str(),O_RDONLY);
                    in_out = true;
                    return;
                }
            }
            else
            {
                _status = 403 ;
                if(fd > 0)
                    close(fd);
                fd=open(getErrorPage().c_str(),O_RDONLY);
                in_out = true;
                return;
            }
        }
        else if (S_ISDIR(infoo.st_mode))
        {
            if ((infoo.st_mode & S_IWUSR )&& (infoo.st_mode & S_IXUSR) )
            {
                bool check = delete_Dir(URI);
                if (!check)
                {
                    in_out = true;
                    return;
                }
                in_out = true;
                _status = 204;
                return;
            }
            else
            {
                _status = 403;
                if(fd > 0)
                    close(fd);
                fd=open(getErrorPage().c_str(),O_RDONLY);
                in_out = true;
                return;
            }
        }
    }
    else
    {
        _status = 404;
        if(fd > 0)
            close(fd);
        fd=open(getErrorPage().c_str(),O_RDONLY);
        in_out = true;
        return;
    }
}

bool Http_req::delete_Dir(std::string pathh)
{
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
                        _status = 500;
                        closedir(ptr);
                        return false;
                    }
                    _status = 204;
                }
                else if (S_ISDIR(fileStat.st_mode))
                {
                    delete_Dir(full_path);
                }
                else
                {
                    perror("Error: Cannot get file or directory information");
                    _status = 500;
                    closedir(ptr);
                    return false;
                }
            }
            else
            {
                closedir(ptr);
                _status = 500;
                return false;
            }
        }
        closedir(ptr);
        if (rmdir(pathh.c_str()) != 0)
        {
            perror("Error : DIRECTOR DELETE");
            _status = 403;
            return false;
        }
        return true;
    }
    else
    {
        perror("Error : can not open directory");
        _status = 403;
        closedir(ptr);
        return false;
    }
    closedir(ptr);
}

void Http_req::parse_re(std ::string bufer, int bytee)
{
    if (!StautRe(bufer) || bytee < 0)
    {
        in_out = true;
        if (fd > 0)
            close(fd);
        fd =open(getErrorPage().c_str(), O_RDONLY);
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
            if (fd > 0)
                close(fd) ;
            in_out = true ;
            fd = open(getErrorPage().c_str(), O_RDONLY) ;
        }
        /*=============== 14 PART (end)==================*/
    }
}

bool Http_req :: Is_dir(const char *ptr)
{
    if (!access(ptr, X_OK | R_OK))
    {
        DIR *dir = opendir(ptr);
        if (dir != NULL)
        {
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
int Http_req:: is_file_dir(std::string uri)
{
    if (Is_dir(uri.c_str()))
        return 0;
    return 1;
}

void Http_req ::CheckLoc(int *is_file)
{
   
    std ::string tmp =_target;
   
    if (path[path.length() - 1] != '/')
    {
        in_out = true;
        _status = 301;
        _loca.setReturn("301", path + "/") ;
        return;
    }

    if (this->_loca.getIndex().size() != 0)
    {
        std ::string main_index;
        std ::vector<std ::string> index = this->_loca.getIndex();
        std::string separator = (_target[_target.length() - 1] == '/') ? "" : "/";
        for (std::vector<std::string>::iterator it = index.begin(); it != index.end(); it++) 
        {
            std::string filename = *it;
            std::string tosearch = _target + separator + filename;
            struct stat sb;
            if (stat(tosearch.c_str(), &sb) == 0)
            {
                main_index = tosearch;
                break;
            }
        }
        _target = main_index;
       
        // check if that index is floder shloud trhow error forbiden
        if (is_file_dir(_target) == 0)
        {
            _status = 403;
            if (fd > 0)
                close(fd) ;
            fd = open(getErrorPage().c_str(), std::ios::binary, O_RDONLY);
            in_out = true;
            return;
        }
        *is_file = 1;
    }

    if (this->_loca.getAutoIndex() )
    {
        /// Here We shloud Send DirectoryListe
        std ::string dirpath = tmp;
        toHtml = "<!DOCTYPE html><html><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" /><head><title>Index of " + path + "</title></head><body><h1>Index of " + path + "</h1><hr/><pre>";
        DIR *dir = opendir(dirpath.c_str());
        if (!dir)
        {
            closedir(dir);
            //perror("auto index issue");
            _status = 403 ;
            if (fd > 0)
                close(fd) ;
            fd = open(getErrorPage().c_str(), O_RDONLY) ;
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
                    if (std::string(list->d_name) != ".")
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
            toHtml += "</pre><hr/>\n</body>\n</html>";
            closedir(dir);
            in_out = true;
            _status = 200;
            std::ofstream outputFile("output.txt", std::ios::binary);
            if (!outputFile.is_open())
            {
                outputFile.close();
                perror("Error file");
                _status = 500 ;
                fd = open(getErrorPage().c_str(), O_RDONLY) ;
                return ;
            }
            outputFile << toHtml;
            outputFile.close();
            if (fd > 0)
                close(fd) ;
            fd = open("output.txt", std::ios::binary, O_RDONLY);
            return;
        }
        closedir(dir);
    }
    else
    {
        in_out = true;
        _status = 403;
        if (fd > 0)
            close(fd);
        fd = open(getErrorPage().c_str(), std::ios::binary, O_RDONLY);
        return;
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
    // this condtion here for that stauts come from redirection
   std ::string tmp=_target;
   
    if(_status)
        return ;
    int is_file = 0;    
    struct stat sb;

    std ::string URI = _target;
    stat(URI.c_str(), &sb);
    int check_type = is_file_dir(URI);
   
    if (S_ISDIR(sb.st_mode) && (!(sb.st_mode & S_IRUSR ) || !(sb.st_mode & S_IXUSR)))
    {
        _status = 403;
        in_out = true;
        if (fd > 0) close(fd);
        fd = open(getErrorPage().c_str(), O_RDONLY);
        return;  
    }

    if (check_type == IS_DIR)
    {
        CheckLoc(&is_file);
        URI = _target;
        
    }
    if(_loca.getReturn().first)
    {
        
       return ; 
    }
    
    if (stat(URI.c_str(), &sb) == 0)
    {
        
        
        if (this->_loca.getCgi())
        {
            // cehck extions
            std ::string extension = fileExtension(URI);
            std ::map<std::string, std ::string> cgiMap = this->_loca.getCgiPaths();
            std ::map<std::string, std::string>::iterator it = cgiMap.find(extension);
            if (it != cgiMap.end())
            {
                if (!it->second.empty() )
                {
                    _status = 200;
                    CGI_FLAG = true;
                    in_out = true;
                    return;
                }
                else
                {
                    _status = 500;
                    in_out = true;
                    if (fd > 0)
                        close(fd) ;
                    fd = open(getErrorPage().c_str(), O_RDONLY);
                    return;
                }
            }
        }
        if ((sb.st_mode & S_IFREG) || is_file)
        {
           
            
              if (!(sb.st_mode & S_IRUSR )) {
              
       
            _status = 403;
            in_out = true;
           fd =open(getErrorPage().c_str(), O_RDONLY);
            return;
        }
            /// wa7d case dyal found index in list directory shloud redirect the index as inginx do
            if (fd > 0)
                close(fd);
            fd = open(_target.c_str(), std::ios::binary, O_RDONLY);
            _status = 200;
            in_out = true;
            return;
        }
        // permisiion condition trhow
    }
    else if(!(stat(URI.c_str(), &sb) == 0) && toHtml.empty())
    {
        _status = 404;
        if (fd > 0)
            close(fd) ;
        fd = open(getErrorPage().c_str(), std::ios::binary, O_RDONLY);
        in_out = true;
        return;
    }
}

/*=============== 14 PART (begin)==================*/
bool Http_req::dirExistWithPermiss()
{
    struct stat info;
    if (stat((_loca.getRoot()+"/"+_loca.getUploadPath()).c_str(), &info) != 0)
        return false;
    else if (info.st_mode & S_IFDIR)
        return true; 
    return false;
}
int Http_req::mimeParse()
{
    std::ifstream file("mime.types");
    std::string line;
    std::string key;
    std::string value;
    if (!file.is_open())
    {
        _status = 415;
        if (fd > 0)
            close(fd) ;
        fd = open(getErrorPage().c_str(), O_RDWR);
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
    file.close() ;
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
    std ::string URI = _target;
    struct stat sb;
    if (stat(URI.c_str(), &sb) == 0)
    {
        if (this->_loca.getCgi())
        {
            std ::string extension = fileExtension(URI);
            std ::map<std::string, std ::string> cgiMap = this->_loca.getCgiPaths();
            std ::map<std::string, std::string>::iterator it = cgiMap.find(extension);
            if (it != cgiMap.end())
            {
                if (!it->second.empty() )
                {
                    CGI_FLAG = true;
                }
            }
        }
    }
    if (fd > 0)
        close(fd);
    if (_loca.getUpload() == true)
    {
        if ((dirExistWithPermiss() == false || (header.find("content-type") ==  header.end())))
        {
            in_out = true;
            error = true;
            _status = 403;
            if(header.find("content-type") ==  header.end())
                _status = 400;
            if (fd > 0)
                close(fd) ;
            fd = open(getErrorPage().c_str(), O_RDWR);
            return;
        }
        if (header["content-type"] == "")
        {
            header["content-type"] = "application/octet-stream" ;
        }
        /*First check if the extension exist */
        std::string str;
        if (_mime.find(header["content-type"]) != _mime.end() && make_name == "")
        {
            make_name = _loca.getRoot()+"/"+_loca.getUploadPath() +"/"+ randNameGen() + "."+ _mime[header["content-type"]];
            uploadFile.open(make_name.c_str(), std::ios::app);
        }
        else if(header["content-type"].substr(0,29) == "multipart/form-data; boundary" && make_name == "")
        {
            make_name = _loca.getRoot()+_loca.getUploadPath().substr(1) +"/"+ randNameGen() + ".txt";
            uploadFile.open(make_name.c_str(), std::ios::app);
        }
        else if (make_name == "")
        {
            _status = 415;
            in_out = true;
            error = true;
            if (fd > 0)
                close(fd) ;
            fd = open(getErrorPage().c_str(), O_RDWR);
            return;
        }
        if (!uploadFile.is_open()) 
        {
            in_out = true;
            _status = 403;
            if (fd > 0)
                close(fd) ;
            fd = open(getErrorPage().c_str(), O_RDWR);
            error = true;
            return;
        }
        if (header["transfer-encoding"] == "chunked")
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
                    _status = 201;
                    if (fd > 0)
                        close(fd) ;
                    fd = open(getErrorPage().c_str(), O_RDWR);
                    return;
                }
            }
            i = 1;
        }
        else if(header.find("content-length") != header.end())
        {
            size_t lastsize = uploadedFileSize;
            uploadedFileSize += body.size();
            size_t fullSize = strtoul(header["content-length"].c_str(), NULL, 10);
            if (uploadedFileSize >= fullSize)
            {
                if(uploadedFileSize == fullSize)
                    uploadFile << body;
                else
                    uploadFile << body.substr(0,fullSize-lastsize);
                uploadFile.close();
                in_out = true;
                _status = 201;
                if (!CGI_FLAG){
                    header["content-type"] = "text/html";
                    if (fd > 0)
                        close(fd) ;
                    fd = open(getErrorPage().c_str(), O_RDWR);
                }
                return;
            }
            uploadFile << body;
            i = 1;
        }
        else
        {
            _status = 411 ;
            in_out = true;
            error = true;
            uploadFile.close();
            if (fd > 0)
                close(fd) ;
            fd = open(getErrorPage().c_str(), O_RDWR);
            return ;
        }
        /*Status 201*/
    }
    else if (_loca.getUpload() == false)
    {
        /*Status 403*/
        _status = 403;
        in_out = true;
        if (fd > 0)
            close(fd) ;
        fd = open(getErrorPage().c_str(), O_RDWR);
        error = true;
    }
}

/*=============== 14 PART (end)==================*/

Http_req::~Http_req()
{
    configFile.close();
    uploadFile.close();
    close(fd) ;
    file.close() ;
}