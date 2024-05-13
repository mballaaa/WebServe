#include "includes/Location.hpp"
#include "includes/Server.hpp"
#include "includes/Error.hpp"
#include "includes/parser/Parser.hpp"
#include "includes/parser/Lexer.hpp"
#include "includes/Multiplex.hpp"

#include <cstdlib>
#include <algorithm>

int main( int argc, char **argv )
{
	Parser::servers_t servers ;
	Lexer::tokens_t tokens ;
	try
	{
		if (argc != 2)
		{
			tokens = Lexer::checkSyntax("./default.conf") ;
		}
		else
		{
			tokens = Lexer::checkSyntax(argv[1]) ;
		}

		servers = Parser::parse(tokens) ;
		Multiplex::setup(servers) ;
		Multiplex::start() ;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl ;
	}

	return (0) ;
}
