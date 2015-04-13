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
		Puzzle( int size, int **puzzle, int **puzzle_end, int rank, Puzzle *parent );
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
		void	calculWeight();
		bool	isSolution( void );

		/*
		** GETTER
		*/
		int			getWeight( void ) const;
		int			**getPuzzle( void ) const;
		int			**getPuzzleAddr( void ) const;
		int			getRank( void ) const;
		int			**getPuzzleEnd( void ) const;
		int			getSize( void ) const;
		Puzzle *	getParent( void ) const;



	private:
		int			size;
		int			weight;
		int			rank;
		int			**puzzle;
		int			**puzzle_end;
		Puzzle		*parent;
};

#endif
