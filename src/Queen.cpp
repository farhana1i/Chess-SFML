#include "Queen.h"
#include"Block.h"
#include"Bishop.h"

// constructors
Queen::Queen(bool is_white, bool is_first_move) : Piece("Queen", is_white, is_first_move) {}

Block** Queen::getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves)
{
	// Queen can has 27 maximum possible moves
	Block** listOfValidBlocks = new Block * [27];
	for (int i = 0; i < 27; i++)
		listOfValidBlocks[i] = nullptr;

	// backward Horizontally
	for (int i = src_row, j = src_col - 1; j >= 0; j--)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	// forward horizontally
	for (int i = src_row, j = src_col + 1; j < 8; j++)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	// upward vertically
	for (int i = src_row - 1, j = src_col; i >= 0; i--)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	//downward vertically
	for (int i = src_row + 1, j = src_col; i < 8; i++)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	//upaward backward diagonally
	for (int i = src_row - 1, j = src_col - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	//upaward forward diagonally
	for (int i = src_row - 1, j = src_col + 1; i >= 0 && j < 8; i--, j++)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	//downward backward diagonally
	for (int i = src_row + 1, j = src_col - 1; i < 8 && j >= 0; i++, j--)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	//downward forward diagonally
	for (int i = src_row + 1, j = src_col + 1; i < 8 && j < 8; i++, j++)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if (game_board[i][j]->getIsWhitePiece() == !this->is_white)
				listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
			break;
		}
		listOfValidBlocks[numOfValidMoves++] = game_board[i][j];
	}

	return listOfValidBlocks;
}