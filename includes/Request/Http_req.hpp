#ifndef HTTP_REQ
#define HTTP_REQ
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include "../Server.hpp"
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <fcntl.h>
#include <fstream>
#include "dirent.h"
#define IS_DIR 0
#define IS_FILE 1
#define IS_LINK 3
#define IS_RED 2



class Http_req
{
public:
    static std::map<int, std::string> errorTexts;
    time_t lastActive ;
    std::ifstream configFile ;
    size_t uploadedFileSize ;
    bool        moreValidationDone ;
    std::ofstream uploadFile ;
    std::string req;
    std::string _target;
    bool is_close;
    std ::string my_req;
    size_t bodycount;
    std ::string query_string;
    std ::ifstream file;
    bool CGI_FLAG;
    std ::map<std::string,std::string> cgiMap;

    std ::string toHtml;
    std ::string method;
    std::string path;
    std ::string http_ver;
    std ::string body;
    bool is_finsh;
    int i ;
    bool in_out;
    bool error;
    size_t lencontent;
    std ::string GetFIle;
        
    std::map<std::string, std::string> header;
    Server server;
    std::vector<Server> servers ;
    Location _loca;
/*=============== 14 PART (begin)==================*/

    std::map<std::string,std::string> _mime;
    std::map<std::string,std::string> _rmime;
    int _status;
    bool accessError;
    std::string to_file;
    size_t chunksize;
    std::string classChunksizeString;
    std::string make_name;
    int fd;
    bool sendHeaders;
    
    static void initErrorTexts();
    /*=============== 14 PART (end)==================*/
    int byterec;
    /*=============== 14 PART (begin)==================*/
    const int &getStatus() const;
    /*=============== 14 PART (end)==================*/

    /*=============== 14 PART (begin)==================*/

    void LetPost();
    int mimeParse();
    void chunked();
    void contentLenght();
    std::string randNameGen();
    bool dirExistWithPermiss();

    const std::string getErrorPage( void ) ;
    
    void    matchServer( void ) ;


    /*=============== 14 PART (end)==================*/
public:
    Http_req();
    Http_req(const Http_req &obj);
    Http_req &operator=(const Http_req &obj);
    void debugFunction();
    Http_req(std::vector<Server>& servers);
    void parse_re(std ::string bufer, int bytee);
    int StautRe(std ::string request);
    int MoreValidation();
    void LetGet();
    void LetDelete();
    void CheckLoc(int *);
    bool loadCGIMap() ;
    bool delete_Dir(std::string);

    bool Is_dir(const char *ptr);
    int is_file_dir(std::string uri);
    
    ~Http_req();

    /*  Getter*/
    const std::string &getTarget() const;
    const bool &getFlag() const;
    const std::string &getBody() const;
    const std::string &getMethod() const;
    const std::string &getPath() const;
    const std::string &getHttpVersion() const;
    const std::map<std::string, std::string> &getHeader() const;
    const Server &getServer() const;
    const Location &getLocation() const;
};

#endif
