#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

// #include <Puzzle.hpp>
#include <iostream>
#include <vector>
#include <Puzzle.hpp>
#include <unistd.h>

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
		int		**getPuzzleInit( void ) const;


		/*
		** METHOD
		*/
		void	generateSolution( void );
		void	aStar( );
		void	end( Puzzle * solution );


	private:
		int									size;
		int									**puzzle_init;
		int									**puzzle_end;
		std::vector<Puzzle *>				puzzles;
		std::vector<Puzzle *>				sortPuzzles;

		void								generateMove( Puzzle *puzzle, int x, int y, int x2, int y2 );
		void								findMove( Puzzle *puzzle );
		void								printStep( Puzzle *puzzle );
		bool								alreadyExist( Puzzle *puzzle );

};

#endif
