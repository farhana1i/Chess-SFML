#ifndef KING_H
#define KING_H

#include"Piece.h"

class King : public Piece {
public:
	// constructors
	King(bool is_white, bool is_first_move = true);

	// to get all valid moves
	Block** getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves);
};
#endif