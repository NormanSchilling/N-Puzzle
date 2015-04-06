
#include <NPuzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
NPuzzle::NPuzzle( void ) : size( 3 )
{
	return ;
}

NPuzzle::NPuzzle( int size, std::vector< std::vector<int> > tab ) : size( size ), puzzle_init( tab )
{
	std::vector<int>		v;

	for ( int i = 0; i < this->size; ++i )
	{
		v.push_back( 0 );
	}

	for ( int i = 0; i < this->size; ++i )
	{
		this->puzzle_end.push_back( v );
	}

	this->generateSolution( );
	this->puzzles.push_back( new Puzzle( size, this->puzzle_init ) );
	this->sortPuzzles.push_back( new Puzzle( size, this->puzzle_init ) );

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
** GET & SET
*/
int										NPuzzle::getSize( void ) const
{
	return ( this->size );
}

std::vector< std::vector<int> >			NPuzzle::getPuzzleInit( void ) const
{
	return ( this->puzzle_init );
}

/*
** METHOD
*/

void									NPuzzle::generateSolution( void )
{
	int			x = 0;
	int			y = 0;
	int			i = 1;
	int			inc_x = 1;
	int			inc_y = 0;
	int			tmp;

	while ( i < this->size * this->size )
	{
		while ( this->puzzle_end[y][x] == 0 && x < this->size && y < this->size && x >= 0 && y >= 0 )
		{
			this->puzzle_end[y][x] = i++;
			x += inc_x;
			y += inc_y;
		}
		x -= inc_x;
		y -= inc_y;
		tmp = inc_y;
		inc_y = inc_x != 0 ? inc_x : 0;
		inc_x = tmp != 0 ? -tmp : 0;
		x += inc_x;
		y += inc_y;
	}
	return ;
}

