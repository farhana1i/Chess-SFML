#include "King.h"
#include"Block.h"

King::King(bool is_white, bool is_first_move) : Piece("King", is_white, is_first_move) {}

// to get all valid moves
Block** King::getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves)
{
	// king can has 8 maximum possible moves
	Block** listOfValidBlocks = new Block * [8];
	for (int i = 0; i < 8; i++)
		listOfValidBlocks[i] = nullptr;

	// vertically upward
	if (src_row - 1 >= 0) {
		if (game_board[src_row - 1][src_col]->getPiece() == nullptr ||
			game_board[src_row - 1][src_col]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row - 1][src_col];
	}

	// vertically downward
	if (src_row + 1 < 8) {
		if (game_board[src_row + 1][src_col]->getPiece() == nullptr ||
			game_board[src_row + 1][src_col]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 1][src_col];
	}

	// horizontally backward
	if (src_col - 1 >= 0) {
		if (game_board[src_row][src_col - 1]->getPiece() == nullptr ||
			game_board[src_row][src_col - 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row][src_col - 1];
	}

	// horizontally forward
	if (src_col + 1 < 8) {
		if (game_board[src_row][src_col + 1]->getPiece() == nullptr ||
			game_board[src_row][src_col + 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row][src_col + 1];
	}


	// diagonally upward backward
	if (src_row - 1 >= 0 && src_col - 1 >= 0) {
		if (game_board[src_row - 1][src_col - 1]->getPiece() == nullptr ||
			game_board[src_row - 1][src_col - 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row - 1][src_col - 1];
	}

	// diagonally upward forward
	if (src_row - 1 >= 0 && src_col + 1 < 8) {
		if (game_board[src_row - 1][src_col + 1]->getPiece() == nullptr ||
			game_board[src_row - 1][src_col + 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row - 1][src_col + 1];
	}

	// diagonally downward backward
	if (src_row + 1 < 8 && src_col - 1 >= 0) {
		if (game_board[src_row + 1][src_col - 1]->getPiece() == nullptr ||
			game_board[src_row + 1][src_col - 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 1][src_col - 1];
	}

	// diagonally downward forward
	if (src_row + 1 < 8 && src_col + 1 < 8) {
		if (game_board[src_row + 1][src_col + 1]->getPiece() == nullptr ||
			game_board[src_row + 1][src_col + 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 1][src_col + 1];
	}
	return listOfValidBlocks;
}