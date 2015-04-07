#include <Puzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
Puzzle::Puzzle( void ) : size( 3 )
{
	return ;
}

Puzzle::Puzzle( int size, std::vector< std::vector<int> > puzzle,  std::vector< std::vector<int> > puzzle_end, int rank ) : size( size ), weight(rank), rank(rank), puzzle( puzzle ), puzzle_end( puzzle_end )
{
	this->calculWeight();
	return ;
}

Puzzle::Puzzle( Puzzle const & cpy )
{
	this->weight = cpy.getWeight();
	this->puzzle = cpy.getPuzzle();
	this->rank = cpy.getRank();
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
