#ifndef BISHOP_H
#define BISHOP_H

#include"Piece.h"

class Bishop : public Piece {
public:
	//constructors
	Bishop(bool is_white, bool is_first_move = true);

	// get all valid moves
	Block** getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves);
};

#endif // !BISHOP_H