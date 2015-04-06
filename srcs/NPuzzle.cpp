
#include <NPuzzle.hpp>
#include <iostream>
#include <ctime>
#include <unistd.h>

/*
** CONSTRUCT & DESTRUCT
*/
NPuzzle::NPuzzle( void ) : size( 3 )
{
	return ;
}

NPuzzle::NPuzzle( int size ) : size( size )
{
	return ;
}

NPuzzle::NPuzzle( NPuzzle const & cpy )
{
	*this = cpy;
}

NPuzzle::~NPuzzle( void )
{
	return ;
}

/*
** OPERATOR
*/
NPuzzle		NPuzzle::operator=( NPuzzle const & cpy )
{
	return ( cpy );
}

/*
** METHOD
*/