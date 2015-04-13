#include <Puzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
Puzzle::Puzzle( void ) : size( 3 )
{
	return ;
}

Puzzle::Puzzle( int size, std::vector< std::vector<int> > puzzle, std::vector< std::vector<int> > puzzle_end, int rank ) : size( size ), weight( rank ), rank( rank ), puzzle( puzzle ), puzzle_end( puzzle_end )
{
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
Puzzle &	Puzzle::operator=( Puzzle const & cpy )
{
	if ( this == &cpy )
		return ( *this );

	this->weight = cpy.getWeight();
	this->puzzle = cpy.getPuzzle();
	this->rank = cpy.getRank();
	this->size = cpy.getSize();
	this->puzzle_end = cpy.getPuzzleEnd();
	return ( *this );
}

bool	Puzzle::operator==( Puzzle const & rhs )
{
	if ( this == &rhs )
		return ( true );

	for ( int y = 0; y < this->size; ++y )
	{
		for ( int x = 0; x < this->size; ++x )
		{
			if ( this->puzzle[y][x] != rhs.getPuzzle()[y][x] )
				return ( false );
		}
	}

	// std::cout << "POKPOKPOK" << std::endl;
	// for ( int i = 0; i < this->size; ++i )
	// {
	// 	for ( int j = 0; j < this->size; ++j )
	// 	{
	// 		std::cout << this->puzzle[i][j] << "\t";
	// 	}
	// 		std::cout << "\t\t\t";
	// 	for ( int j = 0; j < this->size; ++j )
	// 	{
	// 		std::cout << rhs.puzzle[i][j] << "\t";
	// 	}
	// 	std::cout << std::endl;
	// }

	return ( true );
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
	std::vector< std::vector<int> >		tmp;

	for (int i = 0; i < this->size; ++i)
	{
		std::vector<int>	tmp2;
		for (int j = 0; j < this->size; ++j)
		{
			tmp2.push_back( this->puzzle[i][j] );
		}
		tmp.push_back( tmp2 );
	}

	return ( tmp );
}

int									Puzzle::getRank( void ) const
{
	return ( this->rank );
}

std::vector< std::vector<int> >		Puzzle::getPuzzleEnd( void ) const
{
	return ( this->puzzle_end );
}

int									Puzzle::getSize( void ) const
{
	return ( this->size );
}
