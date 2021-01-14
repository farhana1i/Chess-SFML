#include "Knight.h"
#include"Block.h"

// constructors
Knight::Knight(bool is_white, bool is_first_move) : Piece("Knight", is_white, is_first_move) {}

// to get all valid moves
Block** Knight::getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves)
{
	// knight can has 8 maximum possible moves
	Block** listOfValidBlocks = new Block * [8];
	for (int i = 0; i < 8; i++)
		listOfValidBlocks[i] = nullptr;

	if (src_row - 1 >= 0 && src_col - 2 >= 0) {
		if (game_board[src_row - 1][src_col - 2]->getPiece() == nullptr ||
			game_board[src_row - 1][src_col - 2]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row - 1][src_col - 2];
	}

	if (src_row - 1 >= 0 && src_col + 2 < 8) {
		if (game_board[src_row - 1][src_col + 2]->getPiece() == nullptr ||
			game_board[src_row - 1][src_col + 2]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row - 1][src_col + 2];
	}

	if (src_row + 1 < 8 && src_col - 2 >= 0) {
		if (game_board[src_row + 1][src_col - 2]->getPiece() == nullptr ||
			game_board[src_row + 1][src_col - 2]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 1][src_col - 2];
	}

	if (src_row + 1 < 8 && src_col + 2 < 8) {
		if (game_board[src_row + 1][src_col + 2]->getPiece() == nullptr ||
			game_board[src_row + 1][src_col + 2]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 1][src_col + 2];
	}

	if (src_row - 2 >= 0 && src_col - 1 >= 0) {
		if (game_board[src_row - 2][src_col - 1]->getPiece() == nullptr ||
			game_board[src_row - 2][src_col - 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row - 2][src_col - 1];
	}

	if (src_row - 2 >= 0 && src_col + 1 < 8) {
		if (game_board[src_row - 2][src_col + 1]->getPiece() == nullptr ||
			game_board[src_row - 2][src_col + 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row - 2][src_col + 1];
	}

	if (src_row + 2 < 8 && src_col - 1 >= 0) {
		if (game_board[src_row + 2][src_col - 1]->getPiece() == nullptr ||
			game_board[src_row + 2][src_col - 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 2][src_col - 1];
	}

	if (src_row + 2 < 8 && src_col + 1 < 8) {
		if (game_board[src_row + 2][src_col + 1]->getPiece() == nullptr ||
			game_board[src_row + 2][src_col + 1]->getIsWhitePiece() != this->is_white)
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 2][src_col + 1];
	}
	return listOfValidBlocks;
}