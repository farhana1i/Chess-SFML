#include "Board.h"
#include"Pawn.h"
#include"Bishop.h"
#include"Rook.h"
#include"Knight.h"
#include"King.h"
#include"Queen.h"
#include"Block.h"

Board::Board() {
	listOfBlocks = new Block * *[8];
	for (int i = 0; i < 8; i++)
		listOfBlocks[i] = new Block * [8];
	this->resetBoard();
}
Board::~Board() {
	// deallocate memory
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (listOfBlocks[i][j] != nullptr)
				delete listOfBlocks[i][j];
		}
		if(listOfBlocks[i] != nullptr)
			delete[] listOfBlocks[i];
	}
	if(listOfBlocks != nullptr)
		delete[] listOfBlocks;
}

Block* Board::getBlock(int y, int x) {
	if (x < 0 || y < 0 || x > 7 || y > 7)
		return nullptr;
	return listOfBlocks[y][x];
}

bool Board::setBlock(int des_x, int des_y, Block* block) {
	if (des_x < 0 || des_y < 0 || des_x > 7 || des_y > 7)
		return false;
	listOfBlocks[des_x][des_y] = block;
	return true;
}

void Board::resetBoard() 
{
	// set Pawns
	for (int i = 0; i < 8; i++) {
		listOfBlocks[1][i] = new Block(i, 1, new Pawn(false));
		listOfBlocks[6][i] = new Block(i, 6, new Pawn(true));
	}

	// set rooks
	listOfBlocks[0][0] = new Block(0, 0, new Rook(false));
	listOfBlocks[0][7] = new Block(7, 0, new Rook(false));
	listOfBlocks[7][0] = new Block(0, 7, new Rook(true));
	listOfBlocks[7][7] = new Block(7, 7, new Rook(true));
	/*listOfBlocks[7][0] = new Block(0, 7, nullptr);
	listOfBlocks[7][7] = new Block(7, 7, nullptr);*/

	// set knights 
	listOfBlocks[0][1] = new Block(1, 0, new Knight(false));
	listOfBlocks[0][6] = new Block(6, 0, new Knight(false));
	listOfBlocks[7][1] = new Block(1, 7, new Knight(true));
	listOfBlocks[7][6] = new Block(6, 7, new Knight(true));
	/*listOfBlocks[7][1] = new Block(1, 7, nullptr);
	listOfBlocks[7][6] = new Block(6, 7, nullptr);*/

	// set bishops
	listOfBlocks[0][2] = new Block(2, 0, new Bishop(false));
	listOfBlocks[0][5] = new Block(5, 0, new Bishop(false));
	listOfBlocks[7][2] = new Block(2, 7, new Bishop(true));
	listOfBlocks[7][5] = new Block(5, 7, new Bishop(true));
	/*listOfBlocks[7][2] = new Block(2, 7, nullptr);
	listOfBlocks[7][5] = new Block(5, 7, nullptr);*/

	// set queens
	listOfBlocks[0][3] = new Block(3, 0, new Queen(false));
	listOfBlocks[7][3] = new Block(3, 7, new Queen(true));
	//listOfBlocks[7][3] = new Block(3, 7, nullptr);


	// set kings
	listOfBlocks[0][4] = new Block(4, 0, new King(false));
	listOfBlocks[7][4] = new Block(4, 7, new King(true));
	
	// set null to remaining blocks
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++)
			listOfBlocks[i][j] = new Block(j, i, nullptr);
	}

	//for checkmate
	//listOfBlocks[1][4] = new Block(4, 1, nullptr);
	//listOfBlocks[0][3] = new Block(3, 0, nullptr);
	//listOfBlocks[6][5] = new Block(5, 6, nullptr);
	//listOfBlocks[6][6] = new Block(6, 6, nullptr);
	//listOfBlocks[4][7] = new Block(7, 4, new Queen(false));
	//listOfBlocks[3][4] = new Block(4, 3, new Pawn(false));
	//listOfBlocks[5][5] = new Block(5, 5, new Pawn(true));
}

Block** Board::operator [] (int y) {
	if (y < 0 || y > 7)
		return nullptr;
	return listOfBlocks[y];
}

// overload insertion operator for "Board" class
std::ostream& operator << (std::ostream& _cout, Board& board) {
	if (&board != nullptr) {
		std::cout << "\n";
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j]->getPiece() == nullptr)
					std::cout << "\t  *  \t";
				else
					std::cout <<"\t"<< *board[i][j]<<"\t";
			}
			std::cout << std::endl<<std::endl;
		}
	}
	return _cout;
}