#include "Pawn.h"
#include"Block.h"

Pawn::Pawn(bool is_white, bool is_first_move) : Piece("Pawn", is_white, is_first_move) {}

Block** Pawn::getAllValidBlocks(Board& game_board, int src_row, int src_col, int& numOfValidMoves)
{
	// pawn's maximum possible moves must be lover than 5 (i.e 3)
	Block** listOfValidBlocks = new Block * [5];
	for (int i = 0; i < 5; i++)
		listOfValidBlocks[i] = nullptr;

	// to check color of a piece
	int downward = 1;
	if (is_white)
		downward = -1;

	// pawn moves one sqaure towards enemy's side
	if (game_board[src_row + downward][src_col]->getPiece() == nullptr) {
		listOfValidBlocks[numOfValidMoves++] = game_board[src_row + downward][src_col];
	}

	// pawn can move twop blocks vertically, if it is first move
	if (is_first_move) {
		if (game_board[src_row + downward][src_col]->getPiece() == nullptr && 
			game_board[src_row + 2 * downward][src_col]->getPiece() == nullptr) {
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + 2 * downward][src_col];
		}
	}

	// if there is an opponent piece, pawn can move one square diagonally
	if (src_row + downward < 8 && src_row + downward >= 0 && src_col + 1 < 8) {
		if (game_board[src_row + downward][src_col + 1]->getPiece() != nullptr &&
			game_board[src_row + downward][src_col + 1]->getIsWhitePiece() == !this->is_white) {
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + downward][src_col + 1];
		}
	}

	if (src_row + downward < 8 && src_row + downward >= 0 && src_col - 1 >= 0) {
		if (game_board[src_row + downward][src_col - 1]->getPiece() != nullptr &&
			game_board[src_row + downward][src_col - 1]->getIsWhitePiece() == !this->is_white) {
			listOfValidBlocks[numOfValidMoves++] = game_board[src_row + downward][src_col - 1];
		}
	}
	return listOfValidBlocks;
}

// en passant
bool Pawn::isEnPassant(Board& game_board, Move* lastMove, int row, int col, Block**& listOfValidBlocks, int& numOfValidBlocks) 
{
	// to check color of a piece
	int downward = 1;
	if (is_white)
		downward = -1;

	int src_row = abs((lastMove->getSourceRow() - 48) - 8);			// char ---> int 
	int src_col = lastMove->getSourceColumn() - 97;					// char ---> int

	int des_row = abs((lastMove->getDestinationRow() - 48) - 8);	// char ---> int 
	int des_col = lastMove->getDestinationColumn() - 97;			// char ---> int

	// conditions for en passant
	if (abs(src_row - des_row) == 2 && game_board[des_row][des_col]->getPiece() != nullptr) {
		if (game_board[des_row][des_col]->getIsWhitePiece() == !this->is_white) {
			if (row - des_row == 0) {
				if (game_board[row + downward][des_col]->getPiece() == nullptr) {
					listOfValidBlocks[numOfValidBlocks++] = game_board[row + downward][des_col];
					return true;
				}
			}
		}
	}
	return false;
}