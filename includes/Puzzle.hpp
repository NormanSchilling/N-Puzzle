#ifndef PUZZLE_HPP
# define PUZZLE_HPP

#include <iostream>
#include <vector>

class Puzzle
{
	public:

		/*
		** CONSTRUCT & DESTRUCT
		*/
		Puzzle( void );
		Puzzle( int size, std::vector< std::vector<int> > puzzle, std::vector< std::vector<int> > puzzle_end, int rank );
		Puzzle( Puzzle const & cpy );
		~Puzzle( void );

		/*
		** OPERATOR
		*/
		Puzzle operator=( Puzzle const & cpy );

		/*
		** METHOD
		*/
		void	calculWeight();

		/*
		** GETTER
		*/
		int									getWeight( void ) const;
		std::vector< std::vector<int> >		getPuzzle( void ) const;
		int									getRank( void ) const;
		bool								isSolution( void );


	private:
		int									size;
		int									weight;
		int									rank;
		std::vector< std::vector<int> >		puzzle;
		std::vector< std::vector<int> >		puzzle_end;

};

#endif
