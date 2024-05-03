#include "../../includes/Request/Http_req.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

#include <cstring>

static int a = 0;
/*=============== 14 PART (begin)==================*/
Http_req::Http_req()
{
}
/*=============== 14 PART (end)==================*/
Http_req::Http_req(Server &server)
{
    toHtml = "";
    is_finsh = false;
    this->server = server;
    in_out = false;
    CGI_FLAG = false;
    query_string = "";
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
    byterec = obj.byterec;
    toHtml = obj.toHtml;
    i = obj.i;
    body = obj.body;

    /*=============== 14 PART (begin)==================*/
    _status = obj._status;
    _mime = obj._mime;
    /*=============== 14 PART (end)==================*/
    in_out = obj.in_out;
    is_close = obj.is_close;
    bodycount = obj.bodycount;
    CGI_FLAG = obj.CGI_FLAG;
    cgiMap = obj.cgiMap;
    GetFIle = obj.GetFIle;
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
        i = obj.i;
        // byterec = obj.byterec;
        toHtml = obj.toHtml;
        /*=============== 14 PART (begin)==================*/
        _status = obj._status;
        _mime = obj._mime;
        /*=============== 14 PART (end)==================*/
        in_out = obj.in_out;
        is_close = obj.is_close;
        bodycount = obj.bodycount;
        CGI_FLAG = obj.CGI_FLAG;
        cgiMap = obj.cgiMap;
        GetFIle = obj.GetFIle;
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
        path.replace(0, loac_value.length(), root + "/");
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
    size_t foundSize = 0 ;
    for (it = location.begin(); it != location.end(); ++it)
    {

        size_t count = 0;
        size_t shorterLength = std::min(it->first.length(), _target.length());
        for (size_t i = 0; i < shorterLength; ++i) {
            if (it->first[i] == _target[i]) {
                count++;
            } else {
                break;
            }
        }
        if (foundSize < count)
        {
            foundSize = count ;
            this->_loca = it->second;
            key = it->first ;
            flag = 1;
        }
    }

    std::cout << "key: " << key << std::endl ;
    std::cout << _loca << std::endl ;

    if (flag == 0)
    {
        _status["404"] = "Page Not Found";
        std ::cout << "Not match \n";

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
    // if(!is_exit)
    // {
    //     std ::cout << "sssssss\n";
    //     exit(0);
    //     in_out=true;
    //     _status["403"]="NOt allowed";
    //     return 0 ;
    // }
    /// TO DO SHLOUD DO SOMETHING IF ALLOW MEHODE FALSE

    _target = SetRootLoc(_target, key, this->_loca.getRoot());

     std ::cout << "lastttttttttttttttttt =>" << _target << std ::endl;

    return (1);
}
void Http_req::debugFunction()
{
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

        // if (header.find("transfer-encoding") != header.end())
        // {
        //     //
        //     //std :: cout << "sss\n";
        //     std ::string sizeChunk;
        //     size_t startchu = body.find("\r\n");

        //     if (startchu != std ::string::npos)
        //     {
        //       //  std :: cout << startchu << std ::endl;

        //          sizeChunk = body.substr(0, startchu);
        //         size_t sizeHex=hex_to_decimal(sizeChunk);
        //         (void) sizeHex;
        //         if(header.find("transfer-encoding")->second ==" chunked")
        //         {
        //             body=my_req.substr(body_start+sizeChunk.length()+2);

        //         }

        //     }
        // }

        is_finsh = true;
    }
    else if (is_finsh)
    {
        this->body = request;
    }

    // std :: cerr << "this body ==>"  <<body << std ::endl;

    if (is_finsh == true)
    {
        debugFunction();
        if (MoreValidation() == 0)
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
}

void Http_req::parse_re(std ::string bufer, int bytee)
{
    std::ofstream outputFile("request.txt", std::ios_base::app);

    // std :: cout << bufer << std ::endl;
    (void)bufer;
    (void)bytee;

    if (!StautRe(bufer) || bytee < 0)
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

        *is_file = 1;
    }
    else
    {
        if (!this->_loca.getAutoIndex())
        {

            /// Here We shloud Send DirectoryListe
            // std ::cout << _target << std ::endl;
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
        }
        else
        {
            // SendErrorClient(403);
            std ::cout << "Yesss iam here\n";
            in_out = true;
            _status["403"] = "Forbidden";
            return;
        }
    }
}

void Http_req::loadCGIMap()
{
    if (!cgiMap.empty())
        return;

    std::ifstream configFile("./src/Cgi/pathExecutableFile.txt");
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
        configFile.close();
    }
    else
    {
        perror("Error: Unable to open configuration file");
        _status["403"] = "Forbidden";
        in_out = true;
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
    loadCGIMap();

    int is_file = 0;

    std ::string URI = _target;

    int check_type = is_file_dir(URI);
    // std :: cerr << "output" << check_type << std ::endl;

    if (check_type == IS_DIR && path[path.length() - 1] != '/')
    {
        _status["302"] = "Found" ;
        in_out = true ;
        return ;
    }

    if (check_type == IS_DIR)
    {
        CheckLoc(&is_file);
    }

    struct stat sb;

    if (stat(URI.c_str(), &sb) == 0)
    {

        if (this->_loca.getCgi())
        {

            // cehck extions
            std ::string extension = fileExtension(URI);
            std ::cout << extension << std ::endl;
            if (extension == "php" || extension == "python")
            {
                std ::map<std::string, std::string>::iterator it = cgiMap.find(extension);
                if (it != cgiMap.end())
                {
                    std::string executable = it->second;

                    if (executable == "/usr/bin/php" || executable == "/usr/bin/python")
                    {
                        std ::cout << "yesss\n";
                        _status["200"] = "OK";
                        CGI_FLAG = true;

                        in_out = true;
                        return;
                    }

                    else
                    {
                        _status["403"] = "Not found";
                        return;
                    }
                }
            }
        }

        if ((sb.st_mode & S_IFREG) || is_file)
        {

            header["content-type"] = "text/html";
            GetFIle = URI;
            _status["200"] = "ok";
            in_out = true;

            return;
        }
    }

    else
    {

        _status["404"] = "Not FOund";
        in_out = true;
        return;
    }
}
// in_out=true;

// std ::cout << "sssdffd\n";
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

std::string Http_req::randNameGen()
{
    srand(time(NULL));
    std::string c = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string name;
    for (int i = 0; i < 5; i++)
        name += c[rand() % (sizeof(c) - 1)];
    return name;
}

void getSize(std::string body)
{

    std::string size = body.substr(0, body.find("\r\n"));
}

int hexStringToInt(const std::string &hexString)
{
    std::stringstream ss;
    ss << std::hex << hexString; // Set the stringstream to interpret input as hexadecimal
    int intValue;
    ss >> intValue; // Extract the integer value
    return intValue;
}

bool checkSize(std::string name, std::string size)
{

    std::ifstream file(name.c_str(), std::ios::binary);

    // Check if the file is open
    if (!file.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);                    // Move the file pointer to the end
    std::ifstream::pos_type fileSize = file.tellg(); // Get the position, which is the file size
    file.seekg(0, std::ios::beg);                    // Move the fil
    file.close();
    if (atoi(size.c_str()) == fileSize)
        return true;
    return false;
}

void Http_req::LetPost()
{
    /*location not found*/
    if (_loca.getUploadPath() == "Not Found")
    {
        /*Status 404*/
        in_out = true;
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
            in_out = true;
            return;
        }
        int dirCheck = mkdir("Upload", 0777);

        if (!dirCheck || errno == EEXIST)
        {
            /*First check if the extension exist */
            std::string str;
            if (_mime.find(header["content-type"].substr(1)) != _mime.end() && make_name == "")
                make_name = "Upload/" + randNameGen() + "." + _mime[header["content-type"].substr(1)];
            else if (make_name == "")
                make_name = "Upload/" + randNameGen() + ".txt";

            std::ofstream file(make_name.c_str(), std::ios::app);

            if (!file.is_open())
            {
                std::cout << "File Upload Error" << std::endl;
                return;
            }
            std::istringstream body_forstream(body);
            std::string chunk_sizeString;

            if (header["transfer-encoding"] == " chunked")
            {

                if (!i)
                {
                    classChunksizeString = body.substr(0, body.find("\r\n") + 2);
                    body = body.substr(body.find("\r\n") + 2);
                    chunksize = hexStringToInt(classChunksizeString);
                }
                to_file += body;
                while (1)
                {
                    if (chunksize <= to_file.size())
                    {
                        if (to_file.find("\r\n", chunksize + 2) != std::string::npos)
                        {
                            std::string correct = to_file.substr(0, chunksize);
                            file << correct;
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
                            _status["201"] = "Created";
                            header["content-type"] = "text/html";
                            file.close();
                            break;
                        }
                    }
                    else
                        break;
                }
                i++;
            }
            else
            {
                file << body;
                // if(checkSize(make_name.c_str(),header["content-length"].substr(1)) == true)
                in_out = true;
                file.close();
                _status["201"] = "Created";
                header["content-type"] = "text/html";

                i++;
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
}