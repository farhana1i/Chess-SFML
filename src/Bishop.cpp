#include "Bishop.h"
#include"Block.h"

Bishop::Bishop(bool is_white, bool is_first_move) : Piece("Bishop", is_white, is_first_move) {}

Block** Bishop::getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves)
{
	// bishop can has 13 maximum possible moves
	Block** listOfValidBlocks = new Block * [13];
	for (int i = 0; i < 13; i++)
		listOfValidBlocks[i] = nullptr;

	//upaward backward diagonally
	for (int i = src_row - 1, j = src_col - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (game_board[i][j]->getPiece() != nullptr) {
			if(game_board[i][j]->getIsWhitePiece() == !this->is_white)
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