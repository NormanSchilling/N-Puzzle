#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <NPuzzle.hpp>

static void				ft_usage( void )
{
	std::cout << "./npuzzle [file] [nameHeuristic]" << std::endl;
	std::cout << "| Heuristic ChooseList |" << std::endl;
	std::cout << "weight" << std::endl;
	std::cout << "distance" << std::endl;
	std::cout << "together" << std::endl;

	return ;
}

static std::string		parse( std::string line )
{
	std::stringstream		result;
	std::stringstream		verif;
	std::smatch				m;
	std::regex				e( "\\s{0,}#" );
	std::regex				f( "[0-9\\s]" );

	std::regex_search ( line, m, e );
	result << line.substr( 0, m.position(0) );
	verif << std::regex_replace( result.str(), f, "" );

	if ( verif.str().size() > 0 )
	{
		std::cout << "Forbiden character in your map !" << std::endl;
		exit( -1 );
	}

	return ( result.str() );
}

std::vector<int>	getArray( std::string line, int size )
{
	std::vector<int>		v;
	int						tmp;
	std::string				test;
	std::istringstream		try_len( parse( line ) );
	std::istringstream		is( parse( line ) );

	tmp = 0;
	while ( try_len >> test )
	{
		tmp++;
		if ( test.size() > 7 )
		{
			std::cout << "Verifiez que votre puzzle soit correct" << std::endl;
			exit( -1 );
		}
	}
	if ( tmp != size )
	{
		std::cout << "Verifiez que votre puzzle soit correct" << std::endl;
		exit( -1 );
	}

	while ( is >> tmp )
	{
		if ( tmp >= size * size)
		{
			std::cout << "Verifiez que votre puzzle soit correct" << std::endl;
			exit( -1 );
		}
		v.push_back( tmp );
	}

	return ( v );
}

bool			getHeuristic( std::string heuristic )
{
	if ( heuristic.compare( "weight" ) == 0 )
		return ( true );
	else if ( heuristic.compare( "distance" ) == 0 )
		return ( true );
	else if ( heuristic.compare( "together" ) == 0 )
		return ( true );

	return ( false );
}

int				main( int argc, char *argv[] )
{
	int							h;
	std::string 				heuristic( "weight" );

	if ( argc == 3 )
	{
		std::string				heuristic2( argv[2] );
		heuristic = heuristic2;
	}

	if ( argc < 2  && argc > 3 )
	{
		ft_usage( );
		return ( -1 );
	}

	h = getHeuristic( heuristic );
	if ( argc == 3 && h == -1 )
	{
		ft_usage( );
		return ( -1 );
	}

	std::string						line;
	std::ifstream					puzzle_file( argv[1] );
	std::stringstream				file_content;
	std::smatch						m;
	std::regex						e( "\\s{0,}#" );
	int								i = 0;
	int								size = 0;
	std::vector< std::vector<int> >	tab;
	NPuzzle							*np;

	if ( puzzle_file.is_open() )
	{
		while ( std::getline( puzzle_file, line ) )
		{
			std::regex_search ( line, m, e );
			if ( m.position(0) != 0 && i == 0 )
			{
				file_content << parse( line );
				if ( file_content.str().size() > 3 )
				{
					std::cout << "Puzzle trop grand" << std::endl;
					return ( -1 );
				}
				file_content >> size;
				i++;
			}
			else if ( m.position(0) )
				tab.push_back( getArray(line, size) );
		}
		puzzle_file.close();
		np = new NPuzzle( size, tab, h );
	}
	else
		std::cout << "Unable to open file" << std::endl;

	return ( 0 );
}

