#ifndef PIECE_H
#define PIECE_H

#include<cstring>
#include"Board.h"
#include"Move.h"

class Piece
{
protected:
	char* piece_type;
	bool is_first_move;
	bool is_white;
public:
	//constructors and destructor
	Piece(const char* piece_type, bool is_white, bool is_first_move = true);

	// getter and setters
	void setPieceType(const char* piece_type);
	void setFirstMove(bool is_first_move);
	void setIsWhite(bool is_white);
	char* getPieceType();
	bool getIsWhitePiece();
	bool getIsFirstMove();

	//en passant
	virtual bool isEnPassant(Board& game_board, Move* lastMove, int row, int col, Block**& listOfValidBlocks, int& numOfValidBlocks) {
		std::cout << "Hello\n";
		return false;
	}

	// return all valid coordinates for a specific piece to move
	virtual Block** getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves) = 0;
};
#endif
