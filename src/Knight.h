#ifndef KNIGHT_H
#define KNIGHT_H

#include"Piece.h"

class Knight : public Piece {
public:
	//constructors
	Knight(bool is_white, bool is_first_move = true);
	
	// to get all valid moves
	Block** getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves);
};
#endif