#ifndef BOARD_H
#define BOARD_H
#include<iostream>

class Block;

class Board{
	Block*** listOfBlocks;
public:
	Board();
	~Board();

	Block* getBlock(int y, int x);
	bool setBlock(int des_x, int des_y, Block* block);
	void resetBoard();

	Block** operator [] (int y);

	friend std::ostream& operator << (std::ostream& _cout, Board& board);

};
#endif