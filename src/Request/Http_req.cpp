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
Http_req::Http_req(Server server)
{
    is_finsh=false;
    this->server=server;
    
   



}

// Http_req::Http_req(std ::string req, int byterec, std::map<int, Server> listners)
// {

//     // std :: cerr << s.getClientMaxBodySize();

//     //  std::map<SOCKET,Server> ::iterator it;

//     // for (it =listners.begin() ;it !=listners.end();++it)

//     // {

//     //     std ::cerr << "********* here***********\n";
//     //     std :: cerr << it->second.getClientMaxBodySize() << std ::endl;
//     //     std ::cerr << "********* here***********\n";
//     std::map<int, Server>::iterator it;

//     it = listners.begin();

//     this->req = req;
//     this->byterec = byterec;
//     this->server = it->second;
//    // std :: cerr << "====>root"  << server.getRoot() << std ::endl;
//    /// See location

// //    std :: cerr << "Yessss\n";
// //    std::map<std::string ,Location> getLocation=server.getLocations();
// //         std ::cerr << "==>\n" ;
// //    std::map<std::string, Location>::iterator it_loc;
// //     for (it_loc = getLocation.begin(); it_loc != getLocation.end(); ++it_loc) {
// //     std :: cerr << it_loc->first << std ::endl;
// // }
//     // for(it_loc = getLocation.begin();it_loc !=getLocation.end();++it_loc)
//     // {
//     //     std :: cerr << " =>" << it_loc->first << std ::endl;
//     // }
//     // parse_re(req, byterec); // amine: I commented this line

// }

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
        /*=============== 14 PART (begin)==================*/
        _status = obj._status;
        /*=============== 14 PART (end)==================*/
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

const bool &Http_req::getFlag() const{
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
bool is_same(std::string key, std::string target)
{
    // key is valuee from config location
    //  //target ==is path request

    if (target.length() < key.length())
    {

        return false;
    }

    return target.compare(0, key.length(), key) == 0 && (target.length() == key.length() || target[key.length()] == '/');
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
            // std :: cout << "ddddd3\n";
            return (0);
        }
    }
    if (header.find("transfer-encoding") != header.end() && header["transfer-encoding"] != "chunked")
    {
        // std :: cout << "ddddd4\n";
        return (0);
    }

    if (method == "POST" && header.find("content-length") == header.end() && header.find("transfer-encoding") == header.end())
        return (0);

    this->_target = this->path;

    // now let check if match or not
    std::map<std ::string, Location> location = this->server.getLocations();
    std::map<std::string, Location>::iterator it;
    int flag = 0;
    std ::string key;
    for (it = location.begin(); it != location.end(); it++)
    {

        key = it->first;

        if (is_same(key, _target))
        {

            // std :: cerr << "is same\n" << std ::endl;
            flag++;
            this->_loca = it->second;
            break;
        }
    }

    if (flag == 0)
    {
        std ::cerr << "Not Match \n";

        // if not found any match
        return (0); /// No match akhouuya
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

    if (outputFile.is_open()) {
        // Output body to the file
        outputFile << this->body << std::endl;

        // Close the file
        outputFile.close();

    }
    ///// print headar
    std::map<std::string, std::string>::iterator it;
    for (it = header.begin(); it != header.end(); it++)
    {
      
        // std ::cerr << it->first << ":" << it->second << std ::endl;
    }
    // 
    // //std :: cout << "this ===?\n";
    //std :: cout << this->body << std::endl;
}
int Http_req::StautRe(std::string request)
{
    std ::string my_req;
    // Set flag that can tell us is request are finshied
    if (!is_finsh)
    {
        my_req += request;
    }

    size_t len_req = my_req.find("\r\n\r\n");
    int res;
    res = 0;
    // //std :: cout << "Heyyy\n";
    // //std :: cout << a << std ::endl;
    a++;

    if (!is_finsh && len_req != std ::string ::npos)
    {

        std::istringstream input(my_req);
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
               // debugFunction();
            }
           this->body=my_req.substr(len_req+4);
           is_finsh=true;
         
        }
        else
        {
            this->body=request;
        }
    
 
    // std :: cerr << "this body ==>"  <<body << std ::endl;

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

    if (!StautRe(bufer) || bytee < 0)
    {
    }
    else
    {
        if (method == "GET")
        {
            //std :: cout << "YEssss\n";
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

void Http_req ::CheckLoc()
{
    std :: cout << this->_loca.getIndex().size() << std ::endl;
    if (this->_loca.getIndex().size() != 0)
    {

        std ::vector<std ::string> index = this->_loca.getIndex();
        // check if index file are exit
        /// ==> get first index string
        std ::string main_index = index.at(0);
        std :: cout <<   "==>" << this->_loca.getRoot() << std ::endl;

        //std ::cerr << "index  name==>" << main_index << std ::endl;
        std :: cout << "==> index" << main_index << std ::endl;
        _target += main_index;
    }
    else
    {
        if (this->_loca.getAutoIndex())
        {
            ///Here We shloud Send DirectoryListe
            std :: cout <<  _target << std :: endl;
            std ::string dirpath=_target;
            DIR *dir = opendir(_target.c_str());
            if(dir !=NULL)
            {   
                struct dirent *list;
                list=readdir(dir);
                while (list !=NULL)
                {
                    
                }
                
                
            }


         
            


        }
    }
}
// =====> Let Start Get
void Http_req::LetGet()
{
    std ::string URI = this->_target;
    int check_type = is_file_dir(URI);
    // std :: cerr << "output" << check_type << std ::endl;
    if (check_type == IS_DIR)
    {

        // std ::cerr << "hEYY\n";
        CheckLoc();
    }
}
/*=============== 14 PART (begin)==================*/
void Http_req::mimeParse()
{
    std::ifstream file("mime.types");
    std::string line;
    std::string key;
    std::string value;

    if(!file.is_open())
        return ;
    
    while(getline(file,line)){
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


std::string randNameGen(){
    srand(time(NULL));
    std::string c = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string name;
    for (int i = 0; i < 5; i++)
        name += c[rand() % (sizeof(c) - 1)];
    return name;
}

void Http_req::LetPost(){
    std::ifstream filee("writeBody.txt");
    
    if (!filee.is_open())
        return ;
    
    /*location not found*/
    if (_loca.getUploadPath() == "Not Found")
    {
        /*Status 404*/
        _status["404"] = "Not Found";
    }
    else if (_loca.getUpload() == true)
    {

        mimeParse();

        if (header["content-length"] == " 0")
        {

            /*Status 204*/
            _status["204"] = "No Content";
            return;
        }

        int dirCheck = mkdir("Upload", 0777);

        if(!dirCheck || errno==  EEXIST){
            std::string str = "Upload/"+randNameGen()+"."+_mime[header["content-type"].substr(1)];
            std::ofstream file(str.c_str(),std::ios::out);

            while(std::getline(filee,str))
                file  << str << std::endl ;
        }
        /*Status 201*/
        _status["201"] = "Created";
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
