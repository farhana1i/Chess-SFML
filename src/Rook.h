#ifndef ROOK_H
#define ROOK_H

#include"Piece.h"

class Rook : public Piece {
public:
	// constructors
	Rook(bool is_white, bool is_first_move = true);

	// get all valid moves
	Block** getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves);
};
#endif