#ifndef PUZZLE_HPP
# define PUZZLE_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Puzzle
{
	public:

		/*
		** CONSTRUCT & DESTRUCT
		*/
		Puzzle( void );
		Puzzle( int size, std::vector< std::vector<int> > puzzle, std::vector< std::vector<int> > puzzle_end, int rank, int heuristic );
		Puzzle( Puzzle const & cpy );
		~Puzzle( void );

		/*
		** OPERATOR
		*/
		Puzzle &	operator=( Puzzle const & cpy );
		bool		operator==( Puzzle const & rhs );

		/*
		** METHOD
		*/
		int		calculWeight();
		int		calculDistance();
		int		calculDistanceOneNumber( int a, int b );
		bool	isSolution( void );

		/*
		** GETTER
		*/
		int									getWeight( void ) const;
		std::vector< std::vector<int> >		getPuzzle( void ) const;
		int									getRank( void ) const;
		std::vector< std::vector<int> >		getPuzzleEnd( void ) const;
		int									getSize( void ) const;



	private:
		int									size;
		int									weight;
		int									rank;
		std::vector< std::vector<int> >		puzzle;
		std::vector< std::vector<int> >		puzzle_end;

};

#endif
