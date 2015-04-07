
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
	this->puzzles.push_back( new Puzzle( size, this->puzzle_init, this->puzzle_end ) );
	this->sortPuzzles.push_back( new Puzzle( size, this->puzzle_init, this->puzzle_end ) );

	this->aStar();
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

void									NPuzzle::aStar( void )
{
	int					tmp;
	unsigned long		i = 0;
	std::vector<Puzzle *>			tmpList;

	tmp = this->sortPuzzles[0]->getWeight();
	while ( i < this->sortPuzzles.size() && this->sortPuzzles[i]->getWeight() == tmp )
	{
		tmpList.push_back( this->sortPuzzles[i] );
		i++;
	}
	this->sortPuzzles.erase( this->sortPuzzles.begin(), this->sortPuzzles.begin() + i );

	for ( size_t j = 0; j < tmpList.size(); ++j )
	{
		this->findMove( tmpList[j] );
	}

	this->aStar();
}

void									NPuzzle::findMove( Puzzle *puzzle )
{
	std::vector< std::vector<int> >		tmp = puzzle->getPuzzle();
	int j;
	int i = 0;

	while ( i < this->size )
	{
		j = 0;
		while ( j < this->size )
		{
			if ( tmp[i][j] == 0 )
			{
				this->generateMove( tmp, i, j, i - 1, j );
				this->generateMove( tmp, i, j, i + 1, j );
				this->generateMove( tmp, i, j, i, j - 1 );
				this->generateMove( tmp, i, j, i, j + 1 );
				return ;
			}
			j++;
		}
		i++;
	}

	return ;
}

void			NPuzzle::generateMove( std::vector< std::vector<int> > src, int y, int x, int y2, int x2 )
{
	int				tmp;
	unsigned long	index;
	Puzzle			*step;

	if ( x2 < 0 || x2 >= this->size || y2 < 0 || y2 >= this->size )
		return ;

	tmp = src[y][x];
	src[y][x] = src[y2][x2];
	src[y2][x2] = tmp;
	step = new Puzzle( this->size, src, this->puzzle_end );
	if ( step->isSolution() )
		this->end();

	index = 0;
	while ( index < this->sortPuzzles.size() && step->getWeight() > this->sortPuzzles[index]->getWeight() )
		index++;

	if ( index < this->sortPuzzles.size() )
		this->sortPuzzles.insert( this->sortPuzzles.begin() + index, step );
	else
		this->sortPuzzles.push_back( step );

	for ( int i = 0; i < this->size; ++i )
	{
		for ( int j = 0; j < this->size; ++j )
		{
			std::cout << src[i][j] << "  ";
		}
		std::cout << std::endl;
	}

	this->puzzles.push_back( step );
}


void									NPuzzle::end( void )
{
	std::cout << "Good" << std::endl;
	exit( 1 );
}

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
		while ( x < this->size && y < this->size && x >= 0 && y >= 0 && this->puzzle_end[y][x] == 0 )
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

