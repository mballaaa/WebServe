#include "../includes/Location.hpp"
#include "../includes/Server.hpp"

Location::Location( void ) : _autoIndex(false), _index(), _allowedMethods(), _return(), _root("/var/www"), _cgi(false), _upload(true), _upload_path("/var/upload")
{
    _return.first = 0 ;
    _return.second = "" ;
}

Location::Location( const Server& server ) : _autoIndex(false), _index(server.getIndex()), _allowedMethods(), _return(), _root(server.getRoot()), _cgi(false), _upload(false), _upload_path("/var/upload")
{
    _return.first = 0 ;
    _return.second = "" ;
}

Location::Location( const Location& rhs )
{
    this->_autoIndex = rhs._autoIndex ;
    this->_index = rhs._index ;
    this->_allowedMethods = rhs._allowedMethods ;
    this->_return = rhs._return ;
    this->_root = rhs._root ;
    this->_cgi = rhs._cgi ;
    this->_upload = rhs._upload ;
    this->_upload_path = rhs._upload_path ;

    CgiPath_t::const_iterator itCgi = rhs._cgiMap.begin() ;
    _cgiMap.clear() ;
    while (rhs._cgiMap.size() &&  itCgi != rhs._cgiMap.end())
        this->_cgiMap.insert(*itCgi++) ;
}

Location& Location::operator=( const Location& rhs )
{
    this->_autoIndex = rhs._autoIndex ;
    this->_index = rhs._index ;
    this->_allowedMethods = rhs._allowedMethods ;
    this->_return = rhs._return ;
    this->_root = rhs._root ;
    this->_cgi = rhs._cgi ;
    this->_upload = rhs._upload ;
    this->_upload_path = rhs._upload_path ;
    
    CgiPath_t::const_iterator itCgi = rhs._cgiMap.begin() ;
    _cgiMap.clear() ;
    while (rhs._cgiMap.size() &&  itCgi != rhs._cgiMap.end())
        this->_cgiMap.insert(*itCgi++) ;

    return (*this) ;
}

Location::~Location( void )
{

}


const bool&						Location::getAutoIndex( void ) const
{
    return (_autoIndex) ;
}

const std::vector<std::string>&				Location::getIndex( void ) const
{
    return (_index) ;
}

const Location::Methods_t&	Location::getAllowedMethods( void ) const
{
    return (_allowedMethods) ;
}

const Location::redirection_t&	Location::getReturn( void ) const
{
    return (_return) ;
}

const std::string&				Location::getRoot( void ) const
{
    return (_root) ;
}

const bool&                   Location::getCgi( void ) const
{
    return (_cgi ) ;
}

const Location::CgiPath_t&			    Location::getCgiPaths( void ) const
{
    return (_cgiMap) ;
}

const bool&                    Location::getUpload( void ) const
{
    return (_upload) ;
}

const std::string&               Location::getUploadPath( void ) const
{
    return (_upload_path) ;
}

void 						Location::setAutoIndex( const std::string& _autoIndex )
{
    if (_autoIndex == "on")
        this->_autoIndex = true ;
    else if (_autoIndex == "off")
        this->_autoIndex = false ;
    else
        throw std::runtime_error("Unexpected value for autoindex: " + _autoIndex) ;
}

void 						Location::setIndex( const std::string& _index )
{
    this->_index.push_back(_index) ;
}

void 						Location::clearIndex( void )
{
    this->_index.clear() ;
}

void 						Location::setAllowedMethods( const Methods_t& _allowedMethods )
{
    this->_allowedMethods = _allowedMethods ;
}

void 						Location::setReturn( const std::string& statusCodeStr, const std::string& _return )
{
    int statusCode = atol(statusCodeStr.c_str()) ;
    if (statusCode < 300 || statusCode > 399)
         throw std::runtime_error("HTTP redirection status codes must be between 300 and 399") ;
    this->_return = std::make_pair(statusCode, _return) ;
}

void 						Location::setRoot( const std::string& _root )
{
    this->_root = _root ;
}

void 						Location::setCgi( const std::string& state )
{
    if (state == "on")
        this->_cgi = true ;
    else if (state == "off")
        this->_cgi = false ;
    else
        throw std::runtime_error("Unexpected value for cgi: " + state) ;
}

void 						Location::setCgiPath( const std::string& extension, const std::string& path )
{
    this->_cgiMap[extension] = path ;
}

void 						Location::setUpload( const std::string& state )
{
    if (state == "on")
        this->_upload = true ;
    else if (state == "off")
        this->_upload = false ;
    else
        throw std::runtime_error("Unexpected value for upload: " + state) ;
}

void 						Location::setUploadPath( const std::string& path )
{
    this->_upload_path = path ;
}

static const std::string getMethod( Location::Method_t method )
{
    if (method == Location::GET)
        return ("GET") ;
    if (method == Location::POST)
        return ("POST") ;
    if (method == Location::DELETE)
        return ("DELETE") ;
    return ("Error") ;
}

std::ostream& operator<<( std::ostream& os, const Location& location )
{
    os << "\t\tAutoIndex: " << (location.getAutoIndex() ? "on" : "off") << std::endl ;

    std::vector<std::string>::const_iterator inx = location.getIndex().begin() ;
    os << "\t\tIndex: " ;
    while (inx != location.getIndex().end())
    {
        os << *inx++ ;
        if (inx != location.getIndex().end())
            os << ", " ;
        
    }
    os << std::endl ;
    
    Location::Methods_t methods = location.getAllowedMethods() ;
    Location::Methods_t::iterator itMethod = methods.begin() ;
    os << "\t\tAllowedMethods: " ;
    while (itMethod != methods.end())
    {
        os << getMethod(*itMethod++) ;
        if (itMethod != methods.end())
            os << ", " ;
    }
    os << std::endl ;

    Location::redirection_t redir = location.getReturn() ;
    os << "\t\tReturn: " << redir.first << " " << redir.second << std::endl ;
    os << "\t\tRoot: " << location.getRoot() << std::endl ;
    os << "\t\tcgi: " << (location.getCgi() ? "on" : "off") << std::endl ;

    os << "\t\tUpload: " << (location.getUpload() ? "on" : "off") << std::endl ;
    os << "\t\tUpload Path: " << location.getUploadPath() << std::endl ;

    os << "\t\tcgi: " << std::endl ;
    Location::CgiPath_t _cgiMap = location.getCgiPaths() ;
    Location::CgiPath_t::iterator itCgi = _cgiMap.begin() ;
    while (itCgi != _cgiMap.end())
    {
        os << "\t\t\t\t" << itCgi->first << " " << itCgi->second << std::endl ;
        itCgi++ ;
    }

    return (os) ;
}