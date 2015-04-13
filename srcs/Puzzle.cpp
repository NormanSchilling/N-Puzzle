#include <Puzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
Puzzle::Puzzle( void ) : size( 3 )
{
	return ;
}

Puzzle::Puzzle( int size, std::vector< std::vector<int> > puzzle, std::vector< std::vector<int> > puzzle_end, 
	int rank, std::string heuristic ) : size( size ), weight( rank ), rank( rank ), puzzle( puzzle ), puzzle_end( puzzle_end )
{
	if ( heuristic.compare( "weight" ) == 0 )
		this->weight = this->calculWeight( );
	else if ( heuristic.compare( "distance" ) == 0 )
		this->weight = this->calculDistance( );
	else if ( heuristic.compare( "together" ) == 0 )
		this->weight = this->calculDistance( ) + this->calculWeight( );

	std::cout << "WEIGHT FINAL = " << this->weight << std::endl;

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
int		Puzzle::calculWeight()
{
	int		weight = 0;

	for (int i = 0; i < this->size; ++i)
	{
		for (int j = 0; j < this->size; ++j)
		{
			if ( this->puzzle[i][j] != this->puzzle_end[i][j] )
				weight++;
		}
	}

	return ( weight );
}

int		Puzzle::calculDistanceOneNumber( int a, int b )
{
	int weightOfNumber = 0;
	int	x;
	int y;

	x = 0;
	while ( x < this->size )
	{
		y = 0;
		while ( y < this->size )
		{
			if ( this->puzzle_end[y][x] == this->puzzle[a][b] )
			{
				weightOfNumber = abs(x - b) + abs(y - a);
				std::cout << "weight of Number " << this->puzzle[a][b] << " = " << weightOfNumber << std::endl;
			}
			y++;
		}
		x++;
	}
	return ( weightOfNumber );
}

int		Puzzle::calculDistance()
{
	int		weight = 0;

	for (int i = 0; i < this->size; ++i)
	{
		for (int j = 0; j < this->size; ++j)
		{
			weight += calculDistanceOneNumber( i, j );
		}
	}
	return ( weight );
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
