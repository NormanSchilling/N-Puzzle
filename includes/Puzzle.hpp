#ifndef PUZZLE_HPP
# define PUZZLE_HPP

class Puzzle
{
	public:

		/*
		** CONSTRUCT & DESTRUCT
		*/
		Puzzle( void );
		Puzzle( int size );
		Puzzle( NPuzzle const & cpy );
		~Puzzle( void );

		/*
		** OPERATOR
		*/
		Puzzle operator=( Puzzle const & cpy );

		/*
		** METHOD
		*/


	private:
		int						size;
		int						poids;
		int						rank;
		int						**plateform;

};

#endif