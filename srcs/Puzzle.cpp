#include <Puzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
Puzzle::Puzzle( void ) : size( 3 )
{
	return ;
}

Puzzle::Puzzle( int size, std::vector< std::vector<int> > puzzle,  std::vector< std::vector<int> > puzzle_end ) : size( size ), rank(0), puzzle( puzzle ), puzzle_end( puzzle_end )
{
	this->weight = 0;
	// std::cout << this->size << std::endl;
	this->calculWeight();
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

/*
** METHOD
*/
void	Puzzle::calculWeight()
{
	for (int i = 0; i < this->size; ++i)
	{
		for (int j = 0; j < this->size; ++j)
		{
			if ( this->puzzle[i][j] != this->puzzle_end[i][j] )
				this->weight++;
		}
	}
	std::cout << this->weight << std::endl;
}

bool	Puzzle::isSolution( void )
{
	for ( int i = 0; i < this->size; ++i )
	{
		for (int j = 0; j < this->size; ++j)
		{
			if ( this->puzzle[i][j] != this->puzzle_end[i][j] )
				return ( false );
		}
	}

	return ( true );
}

/*
** GETTER & SETTER
*/
int									Puzzle::getWeight( void ) const
{
	return ( this->weight );
}

std::vector< std::vector<int> >		Puzzle::getPuzzle( void ) const
{
	return ( this->puzzle );
}

int									Puzzle::getRank( void ) const
{
	return ( this->rank );
}
