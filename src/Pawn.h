#ifndef PAWN_H
#define PAWN_H

#include"Piece.h"
#include"Move.h"

class Pawn : public Piece {
public:
	//constructors
	Pawn(bool is_white, bool is_first_move = true);

	// get all valid moves
	Block** getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves);

	// en passant
	bool isEnPassant(Board& game_board, Move* lastMove, int row, int col, Block**& listOfValidBlocks, int& numOfValidBlocks);
};
#endif