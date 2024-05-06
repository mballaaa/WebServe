#include "../../includes/parser/Parser.hpp"

Parser::servers_t   Parser::servers ;
Lexer::iterator_t   Parser::curr ;
Lexer::iterator_t   Parser::end ;

void Parser::_listen( Server& s )
{
    expect("listen") ;
    s.setPort(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_serverName( Server& s )
{
    expect("server_name") ;
    //! consider testing if the server name doesnt end with semicolon
    while ( *curr != ";" )
    {
        s.appendServerName(*curr) ;
        next() ;
    }
    expect(";") ;
}

void Parser::_host( Server& s )
{
    expect("host") ;
    s.setHost(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_root( Server& s )
{
    expect("root") ;
    s.setRoot(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_clientMaxBodySize( Server& s )
{
    expect("client_max_body_size") ;
    s.setClientMaxBodySize(std::atol(curr->c_str())) ;
    next() ;
    expect(";") ;
}

void Parser::_index( Server& s )
{
    /**
     * could have multiple index files
    */
    expect("index") ;
    while ( *curr != ";" )
    {
        s.setIndex(*curr) ;
        next() ;
    }
    expect(";") ;
}

void Parser::_errorPage( Server& s )
{
    expect("error_page") ;
    int statusCode = atol(curr->c_str()) ;
    next() ;
    s.appendErrorPage(statusCode, *curr) ;
    next() ;
    expect(";") ;
}

void Parser::_location( Server& s )
{
    expect("location") ;
    std::string route(*curr) ;
    next() ;
    expect("{") ;
    Location l = createLocation(s) ;
    s.appendLocation( route, l ) ;
    expect("}") ;
}

void Parser::_root( Location& l )
{
    expect("root") ;
    l.setRoot(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_index( Location& l )
{
    /**
     * could have multiple index files
    */
    expect("index") ;
    while ( *curr != ";" )
    {
        l.setIndex(*curr) ;
        next() ;
    }
    expect(";") ;
}

void Parser::_autoIndex( Location& l )
{
    expect("autoindex") ;
    l.setAutoIndex(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_allowMethods( Location& l )
{
    expect("allow_methods") ;
    Location::Methods_t methods ;
    while ( *curr != ";" )
    {
        if (*curr == "GET")
            methods.push_back(Location::GET) ;
        else if (*curr == "POST")
            methods.push_back(Location::POST) ;
        else if (*curr == "DELETE")
            methods.push_back(Location::DELETE) ;
        else
            throw std::runtime_error("Method is not supported: " + *curr) ;
        next() ;
    }
    l.setAllowedMethods(methods) ;
    expect(";") ;
}

void Parser::_return( Location& l )
{
    /**
     * return could have 1 or 2 values
     * return <code> [<url>] [<text>];
    */
    expect("return") ;
    std::string statusCode = *curr ;
    next() ;
    l.setReturn(statusCode, *curr) ;
    next() ;
    expect(";") ;
}

void Parser::_cgi( Location& l )
{
    expect("cgi") ;
    l.setCgi(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_cgiPath( Location& l )
{
    expect("cgi_path") ;
    std::string extension = *curr ;
    next() ;
    l.setCgiPath(extension, *curr) ;
    next() ;
    expect(";") ;
}

void Parser::_upload_path( Location& l )
{
    expect("upload_path") ;
    l.setUploadPath(*curr) ;
    next() ;
    expect(";") ;
}

void Parser::_upload( Location& l )
{
    expect("upload") ;
    l.setUpload(*curr) ;
    next() ;
    expect(";") ;
}

Parser::servers_t Parser::parse( const Lexer::tokens_t& tokens )
{
    curr = tokens.begin();
    end = tokens.end() ;
    while ( expect("server") )
    {
        expect("{") ;
        servers.push_back(createServer()) ;
        expect("}") ;
    }
    return (servers) ;
}

bool Parser::accept( const std::string& sym )
{
    if ( sym == *curr )
    {
        do
		{
	        next();
		} while (sym == ";" && *curr == ";");
        return (true) ;
    }
    return (false) ;
}

bool Parser::expect( const std::string& sym )
{
    if ( accept(sym) )
        return (true) ;
    if (curr == end)
        return (false) ;
    throw std::runtime_error("expected " + sym + " got: " + *curr) ;
    return (false) ;
}

Server Parser::createServer( void )
{
    Server s ;
    while ( next() && *(--curr) != "}" )
    {
        if ( *curr == "listen" )
            _listen(s) ;
        else if ( *curr == "server_name" )
            _serverName(s) ;
        else if ( *curr == "host" )
            _host(s) ;
        else if ( *curr == "root" )
            _root(s) ;
        else if ( *curr == "client_max_body_size" )
            _clientMaxBodySize(s) ;
        else if ( *curr == "index" )
            _index(s) ;
        else if ( *curr == "error_page" )
            _errorPage(s) ;
        else if ( *curr == "location" )
            _location(s) ;
        else 
            throw std::runtime_error("Unexpected token: in server" + *curr) ;
    }
    return (s) ;
}

Location Parser::createLocation( const Server& server )
{
    Location l = Location(server);
    while ( next() && *(--curr) != "}" )
    {
        if ( *curr == "allow_methods")
            _allowMethods(l) ;
        else if ( *curr == "autoindex")
            _autoIndex(l) ;
        else if ( *curr == "root")
            _root(l) ;
        else if ( *curr == "index")
            _index(l) ;
        else if ( *curr == "cgi")
            _cgi(l) ;
        else if ( *curr == "cgi_path")
            _cgiPath(l) ;
        else if ( *curr == "return")
            _return(l) ;
        else if ( *curr == "upload")
            _upload(l) ;
        else if ( *curr == "upload_path")
            _upload_path(l) ;
        else 
            throw std::runtime_error("Unexpected token: in location " + *curr) ;
    }
    return (l) ;
}

bool Parser::next( void )
{
    if (curr != end)
    {
        curr++ ;
        return (true) ;
    }
    return (false) ;
}