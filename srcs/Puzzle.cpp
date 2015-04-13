#include <Puzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
Puzzle::Puzzle( void ) : size( 3 )
{
	return ;
}

Puzzle::Puzzle( int size, int **puzzle, int **puzzle_end, int rank, Puzzle * parent, std::string heuristic ) : size( size ),
				weight( rank ), rank( rank ), puzzle( puzzle ), puzzle_end( puzzle_end ), parent( parent )
{
	if ( heuristic.compare( "weight" ) == 0 )
		this->weight = this->calculWeight( );
	else if ( heuristic.compare( "distance" ) == 0 )
		this->weight = this->calculDistance( );
	else if ( heuristic.compare( "together" ) == 0 )
		this->weight = this->calculDistance( ) + this->calculWeight( );

	return ;
}

Puzzle::Puzzle( Puzzle const & cpy )
{
	*this = cpy;
}

Puzzle::~Puzzle( void )
{
	// for ( int i = 0; i < this->size; ++i )
	// {
	// 	delete [] this->puzzle[i];
	// }
	// delete [] this->puzzle;
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
	this->parent = cpy.getParent();
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
			if ( this->puzzle[y][x] != rhs.puzzle[y][x] )
				return ( false );
		}
	}

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
				weightOfNumber = abs(x - b) + abs(y - a);
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

int **								Puzzle::getPuzzle( void ) const
{
	int		**tmp = new int*[this->size];

	for (int i = 0; i < this->size; ++i)
	{
		tmp[i] = new int[this->size];
		for (int j = 0; j < this->size; ++j)
		{
			tmp[i][j] = this->puzzle[i][j];
		}
	}

	return ( tmp );
}

int **								Puzzle::getPuzzleAddr( void ) const
{
	return ( this->puzzle );
}

int									Puzzle::getRank( void ) const
{
	return ( this->rank );
}

int **								Puzzle::getPuzzleEnd( void ) const
{
	return ( this->puzzle_end );
}

int									Puzzle::getSize( void ) const
{
	return ( this->size );
}

Puzzle *							Puzzle::getParent( void ) const
{
	return ( this->parent );
}
