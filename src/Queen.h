#ifndef QUEEN_H
#define QUEEN_H

#include"Piece.h"

class Queen : public Piece {
public:
	// constructors
	Queen(bool is_white, bool is_first_move = true);

	// to get all valid moves
	Block** getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves);
};
#endif