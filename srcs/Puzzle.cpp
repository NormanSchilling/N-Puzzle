#include <Puzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
Puzzle::Puzzle( void ) : size( 3 )
{
	return ;
}

Puzzle::Puzzle( int size ) : size( size )
{
	return ;
}

Puzzle::Puzzle( Puzzle const & cpy )
{
	*this = cpy;
}

Puzzle::~Puzzle( void )
{
	return ;
}

/*
** OPERATOR
*/
Puzzle		Puzzle::operator=( Puzzle const & cpy )
{
	return ( cpy );
}