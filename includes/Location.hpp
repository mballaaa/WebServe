#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif
#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

class Location
{
public:
	typedef enum { GET, HEAD, POST, PUT, DELETE } Method_t;
	typedef std::vector<Method_t> Methods_t ;
	typedef std::pair<int, std::string> redirection_t ;
	
private:
	bool						_autoIndex ;
	std::vector<std::string>	_index ;
	Methods_t					_allowedMethods ;
	redirection_t				_return ;
	std::string					_root ;
	bool						_cgi ;
	bool						_upload ;
	std::string					_upload_path ;
public:
	Location( void ) ;
	Location( const Location& rhs ) ;
	Location& operator=( const Location& rhs ) ;
	~Location( void ) ;

	// Getters
	const bool&					getAutoIndex( void ) const ;
	const std::vector<std::string>&			getIndex( void ) const ;
	const Methods_t&			getAllowedMethods( void ) const ;
	const redirection_t&		getReturn( void ) const ;
	const std::string&			getRoot( void ) const ;
	const bool&					getCgi( void ) const ;
	const bool&					getUpload( void ) const ;
	const std::string&			getUploadPath( void ) const ;

	// Setters
	void 						setAutoIndex( const std::string& _autoIndex ) ;
	void 						setIndex( const std::string& _index ) ;
	void 						setAllowedMethods( const Methods_t	& _allowedMethods ) ;
	void 						setReturn( const std::string& statusCode, const std::string& _return ) ;
	void 						setRoot( const std::string& _root ) ;
	void 						setCgi( const std::string& state ) ;
	void 						setUpload( const std::string& state ) ;
	void 						setUploadPath( const std::string& path ) ;

} ;

std::ostream& operator<<( std::ostream& os, const Location& location ) ;

#endif


