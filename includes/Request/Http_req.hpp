#ifndef HTTP_REQ
#define HTTP_REQ
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include "../Server.hpp"
#include <cerrno>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include "dirent.h"
#define IS_DIR 0
#define IS_FILE 1
#define IS_LINK 3
#define IS_RED 2

class Http_req
{
public:
    struct golbal_info
    {
    };

public: // amine: i made this public for now
        /// this the start line
    std::string req;
    std::string _target;
    bool is_close;
    std ::string my_req;
    size_t bodycount;
    typedef enum
    {
        START,
        HEADER,
        BODY,
        DONE,
        WAITCLOSE
    } State_t;
    std ::string toHtml;
    State_t state;
    std ::string method;
    std::string path;
    std ::string http_ver;
    std ::string body;
    bool is_finsh;
    bool is_body_finsh;
    bool in_out;
    bool _headerParsed;
    size_t lencontent;
    std::string to_file;

    std::map<std::string, std::string> header;
    Server server;
    Location _loca;
    /*=============== 14 PART (begin)==================*/
    std::map<std::string, std::string> _mime;
    std::map<std::string, std::string> _status;

    /*=============== 14 PART (end)==================*/
    int byterec;
    /*=============== 14 PART (begin)==================*/
    const std::map<std::string, std::string> &getStatus() const;
    /*=============== 14 PART (end)==================*/

    /*=============== 14 PART (begin)==================*/

    void LetPost();
    void mimeParse();
    void chunked();
    void contentLenght();

    /*=============== 14 PART (end)==================*/
public:
    Http_req();
    Http_req(const Http_req &obj);
    Http_req &operator=(const Http_req &obj);
    void debugFunction();
    Http_req(Server server);
    // Http_req(std::string req,int byterec, std::map<int, Server> listenrs);
    void parse_re(std ::string bufer, int bytee);
    int StautRe(std ::string request);
    int MoreValidation();
    void LetGet();
   void CheckLoc(int *);
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
