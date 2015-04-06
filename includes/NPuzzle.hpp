#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

// #include <Puzzle.hpp>

class NPuzzle
{
	public:

		/*
		** CONSTRUCT & DESTRUCT
		*/
		NPuzzle( void );
		NPuzzle( int size );
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


		/*
		** METHOD
		*/


	private:
		int						size;
		// int						**puzzle_init;
		// int						**puzzle_end;
		// std::vector<Puzzle *>	puzzles;
		// Heuristic				*heuristic;

};

#endif
