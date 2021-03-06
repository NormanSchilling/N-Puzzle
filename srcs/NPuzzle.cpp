
#include <NPuzzle.hpp>

/*
** CONSTRUCT & DESTRUCT
*/
NPuzzle::NPuzzle( void ) : size( 3 ), heuristic( 1 ), inversion(0)
{
	return ;
}


NPuzzle::NPuzzle( int size, std::vector< std::vector<int> > tab, int heuristic ) : size( size ), heuristic( heuristic ), inversion(0)
{
	this->puzzle_init = new int*[this->size];

	for (int i = 0; i < this->size; ++i)
	{
		for (int j = 0; j < this->size; ++j)
		{
			if ( j == 0 )
				this->puzzle_init[i] = new int[this->size];
			this->puzzle_init[i][j] = tab[i][j];
		}
	}

	if ( !this->isValidPuzzle() )
		this->error( "Verifier que votre puzzle est correct" );

	this->generateSolution( );
	this->sortPuzzles.push_back( new Puzzle( size, this->puzzle_init, this->puzzle_end, 0, NULL, heuristic ) );
	if ( !this->isSolvable() )
		this->error( "Ce puzzle est insoluble" );

	std::cout << "Nous recherchons la solution a la grande question, veuillez patienter ..." << std::endl;
	this->start = time(nullptr);

	if ( this->sortPuzzles[0]->isSolution() )
		this->end( this->sortPuzzles[0] );

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

int **									NPuzzle::getPuzzleInit( void ) const
{
	return ( this->puzzle_init );
}

/*
** METHOD
*/
void									NPuzzle::error( const char *msg ) const
{
	std::cout << msg << std::endl;
	exit(-1);
}

bool									NPuzzle::isValidPuzzle( void ) const
{
	for ( int i = 0; i < this->size; ++i )
	{
		for ( int j = 0; j < this->size; ++j )
		{
			for ( int y = 0; y < this->size; ++y )
			{
				for ( int x = 0; x < this->size; ++x )
				{
					if ( ( x != j || y != i ) && this->puzzle_init[i][j] == this->puzzle_init[y][x] )
						return ( false );
				}
			}
		}
	}

	return ( true );
}

void									NPuzzle::aStar()
{
	Puzzle *			tmpPuzzle;

	while (1)
	{
		tmpPuzzle = new Puzzle( *(this->sortPuzzles[0]) );
		this->puzzles.push_back( tmpPuzzle );
		delete this->sortPuzzles[0];
		this->sortPuzzles.erase( this->sortPuzzles.begin() );
		this->findMove( tmpPuzzle );
	}
}

void									NPuzzle::printStep( Puzzle *puzzle )
{
	int		**tmp = puzzle->getPuzzleAddr();

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
	int		**tmp = puzzle->getPuzzleAddr();
	int j;
	int i = 0;

	while ( i < this->size )
	{
		j = 0;
		while ( j < this->size )
		{
			if ( tmp[i][j] == 0 )
			{
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
	if ( puzzle->getParent() && puzzle->getParent()->getParent() && *(puzzle->getParent()->getParent()) == *(puzzle) )
		return ( true );

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
	int				**src = puzzle->getPuzzle();
	unsigned long	index = 0;

	Puzzle			*step;

	if ( x2 < 0 || x2 >= this->size || y2 < 0 || y2 >= this->size )
		return ;

	src[y][x] = src[y2][x2];
	src[y2][x2] = 0;
	step = new Puzzle( this->size, src, this->puzzle_end, puzzle->getRank() + 1, new Puzzle( *puzzle ), this->heuristic );

	if ( step->isSolution() )
		this->end( step );
	if ( this->alreadyExist( step ) )
	{
		delete step;
		return ;
	}

	while ( index < this->sortPuzzles.size() && step->getWeight() > this->sortPuzzles[index]->getWeight() )
		index++;

	if ( index < this->sortPuzzles.size() )
		this->sortPuzzles.insert( this->sortPuzzles.begin() + index, step );
	else
		this->sortPuzzles.push_back( step );
}


void									NPuzzle::end( Puzzle * solution )
{
	std::vector<Puzzle *>		list;
	std::cout << "Solution trouvee !" << std::endl;
	std::cout << "Temps d'execution : " << time(nullptr) - this->start << "sec" <<  std::endl;
	std::cout << this->puzzles.size() << " puzzles closed" << std::endl;
	std::cout << this->sortPuzzles.size() << " puzzles open" << std::endl;
	std::cout << this->sortPuzzles.size() + this->puzzles.size() << " puzzles calcules" << std::endl;


	while ( solution )
	{
		list.insert( list.begin(), solution );
		solution = solution->getParent();
	}

	std::cout << list.size() << " mouvements afin d'atteindre la solution" << std::endl;
	std::cout << std::endl << "Affichage de la solution dans 2 secondes" << std::endl;
	sleep( 2 );

	for ( unsigned long i = 0; i < list.size(); ++i )
	{
		this->printStep( list[i] );
	}

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
	int			correct = 0;

	this->puzzle_check = new int[this->size * this->size];
	this->puzzle_end = new int*[this->size];

	for ( int index = 0; index < this->size; ++index )
	{
		this->puzzle_end[index] = new int[this->size];
		for ( int tmp_index = 0; tmp_index < this->size; ++tmp_index )
		{
			this->puzzle_end[index][tmp_index] = 0;
		}
	}

	while ( i < this->size * this->size )
	{
		while ( x < this->size && y < this->size && x >= 0 && y >= 0 && this->puzzle_end[y][x] == 0 )
		{
			if ( this->puzzle_init[y][x] != 0 )
				this->puzzle_check[i - 1 - correct] = this->puzzle_init[y][x];
			else
			{
				this->row_zero = (this->size - 1) - y;
				correct = 1;
			}
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
	this->puzzle_check[i - 1 - correct] = this->puzzle_init[y][x];

	return ;
}

bool								NPuzzle::isSolvable( void )
{
	int		tmp;

	for ( int i = 0; i < this->size * this->size - 1; ++i )
	{
		tmp = this->puzzle_check[i];
		for ( int j = i + 1; j < this->size * this->size - 1; ++j )
		{
			if ( tmp > this->puzzle_check[j] )
				this->inversion++;
		}
	}

	return ( this->inversion % 2 == 0 );
}
