#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

// #include <Puzzle.hpp>
#include <iostream>
#include <vector>
#include <Puzzle.hpp>

class NPuzzle
{
	public:

		/*
		** CONSTRUCT & DESTRUCT
		*/
		NPuzzle( void );
		NPuzzle( int size, std::vector< std::vector<int> > tab );
		NPuzzle( NPuzzle const & cpy );
		~NPuzzle( void );

		/*
		** OPERATOR
		*/
		NPuzzle operator=( NPuzzle const & cpy );

		/*
		** GET & SET
		*/
		int		getSize( void ) const;
		std::vector< std::vector<int> >		getPuzzleInit( void ) const;


		/*
		** METHOD
		*/
		void	generateSolution( void );
		void	aStar( void );
		void	end( void );
		void	findMove( Puzzle *puzzle );


	private:
		int									size;
		std::vector< std::vector<int> >		puzzle_init;
		std::vector< std::vector<int> >		puzzle_end;
		std::vector<Puzzle *>				puzzles;
		std::vector<Puzzle *>				sortPuzzles;

		void								generateMove( std::vector< std::vector<int> > src, int x, int y, int x2, int y2 );
		// Heuristic				*heuristic;

};

#endif
