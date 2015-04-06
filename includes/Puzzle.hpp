#ifndef PUZZLE_HPP
# define PUZZLE_HPP

#include <vector>

class Puzzle
{
	public:

		/*
		** CONSTRUCT & DESTRUCT
		*/
		Puzzle( void );
		Puzzle( int size, std::vector< std::vector<int> > puzzle );
		Puzzle( Puzzle const & cpy );
		~Puzzle( void );

		/*
		** OPERATOR
		*/
		Puzzle operator=( Puzzle const & cpy );

		/*
		** METHOD
		*/
		// void	calculWeight();

		/*
		** GETTER
		*/
		int		getWeight( void ) const;

	private:
		int									size;
		int									weight;
		int									rank;
		int									state;
		std::vector< std::vector<int> >		puzzle;

};

#endif
