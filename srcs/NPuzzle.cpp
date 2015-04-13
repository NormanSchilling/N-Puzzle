
#include <NPuzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
NPuzzle::NPuzzle( void ) : size( 3 ), heuristic( 1 )
{
	return ;
}

NPuzzle::NPuzzle( int size, std::vector< std::vector<int> > tab, int heuristic ) : size( size ), puzzle_init( tab ), heuristic( heuristic )
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
	this->puzzles.push_back( new Puzzle( size, this->puzzle_init, this->puzzle_end, 0, heuristic ) );
	this->sortPuzzles.push_back( new Puzzle( size, this->puzzle_init, this->puzzle_end, 0, heuristic ) );

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
	Puzzle *			tmpPuzzle;

	int					i = 0;
	while ( 1 )
	{
		tmpPuzzle = new Puzzle( *(this->sortPuzzles[0]) );
		this->puzzles.push_back( tmpPuzzle );
		delete this->sortPuzzles[0];
		this->sortPuzzles.erase( this->sortPuzzles.begin() );

		// std::cout << "Search solution for the following state (weight = " << tmpPuzzle->getWeight() << ") : " << std::endl;
		// this->printStep( tmpPuzzle );
		std::cout << i++ << std::endl;

		// std::cout << std::endl;
		// std::cout << "GROSSE list" << std::endl;
		// for (unsigned long w = 0; w < this->puzzles.size(); ++w)
		// {
		// 	this->printStep(this->puzzles[w]);
		// }
		this->findMove( tmpPuzzle );

		// std::cout << std::endl;
		// std::cout << "Sort list" << std::endl;
		// for (unsigned long w = 0; w < this->sortPuzzles.size(); ++w)
		// {
		// 	this->printStep(this->sortPuzzles[w]);
		// }
		// std::cout << std::endl;
		// std::cout << std::endl;
		// std::cout << std::endl;
		// std::cout << std::endl;
		// std::cout << std::endl;
		// std::cout << std::endl;


		// delete tmpPuzzle;
		// if ( this->sortPuzzles.size() > 10 )
		// 	exit( -1 );
	}

}

void									NPuzzle::printStep( Puzzle *puzzle )
{

	// if ( this->sortPuzzles.size() > 10 )
	// {
	// 	exit( - 1);
	// }
	// // td::cout << "rank: " << puzzle->getRank() << std::endl;
	// for (unsigned long w = 0; w < this->sortPuzzles.size(); ++w)
	// {
	// 	for ( int i = 0; i < this->size; ++i )
	// 	{
	// 		for ( int j = 0; j < this->size; ++j )
	// 		{
	// 			std::cout << this->sortPuzzles[w]->getPuzzle()[i][j] << "\t";
	// 		}
	// 		std::cout << std::endl;
	// 	}
	// 		std::cout << std::endl;

	// }
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;
	// 		std::cout << std::endl;

	// for (unsigned long w = 0; w < this->puzzles.size(); ++w)
	// {
	// 	for ( int i = 0; i < this->size; ++i )
	// 	{
	// 		for ( int j = 0; j < this->size; ++j )
	// 		{
	// 			std::cout << this->puzzles[w]->getPuzzle()[i][j] << "\t";
	// 		}
	// 		std::cout << std::endl;
	// 	}
	// 		std::cout << std::endl;

	// }

	// if ( puzzle )
	// 	return;


	std::vector< std::vector<int> >		tmp = puzzle->getPuzzle();

	std::cout << "rank: " << puzzle->getRank() << std::endl;
	std::cout << "weight: " << puzzle->getWeight() << std::endl;
	for ( int i = 0; i < this->size; ++i )
	{
		for ( int j = 0; j < this->size; ++j )
		{
			std::cout << tmp[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "--------" << std::endl;
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
				// std::cout << "solution genere : " << std::endl;
				this->generateMove( puzzle, i, j, i - 1, j );
				this->generateMove( puzzle, i, j, i + 1, j );
				this->generateMove( puzzle, i, j, i, j - 1 );
				this->generateMove( puzzle, i, j, i, j + 1 );
				return ;
			}
			j++;
		}
		i++;
	}

	return ;
}

bool			NPuzzle::alreadyExist( Puzzle *puzzle )
{

	for ( unsigned long i = 0; i < this->puzzles.size(); ++i )
	{
		if ( *(this->puzzles[i]) == *(puzzle) )
			return ( true );
	}

	for ( unsigned long i = 0; i < this->sortPuzzles.size(); ++i )
	{
		if ( *(this->sortPuzzles[i]) == *(puzzle) )
			return ( true );
	}
	return ( false );
}

void			NPuzzle::generateMove( Puzzle *puzzle, int y, int x, int y2, int x2 )
{
	std::vector< std::vector<int> >		src = puzzle->getPuzzle();
	unsigned long	index = 0;

	Puzzle			*step;

	if ( x2 < 0 || x2 >= this->size || y2 < 0 || y2 >= this->size )
		return ;

	src[y][x] = src[y2][x2];
	src[y2][x2] = 0;
	step = new Puzzle( this->size, src, this->puzzle_end, puzzle->getRank() + 1, this->heuristic );

	if ( step->isSolution() )
		this->end( puzzle, step );
	if ( this->alreadyExist( step ) )
	{
		delete step;
		return ;
	}

	// this->printStep( step );

	// this->puzzles.push_back( step );

	while ( index < this->sortPuzzles.size() && step->getWeight() > this->sortPuzzles[index]->getWeight() )
		index++;

	this->puzzles.push_back( step );

	if ( index < this->sortPuzzles.size() )
		this->sortPuzzles.insert( this->sortPuzzles.begin() + index, new Puzzle( *step ) );
	else
		this->sortPuzzles.push_back( new Puzzle( *step ) );

}


void									NPuzzle::end( Puzzle * src, Puzzle * solution )
{
	std::cout << "Solution found ! It's the next of this state : " << std::endl;
	this->printStep( src );

	std::cout << "And the solution is : " << std::endl;
	this->printStep( solution );

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

