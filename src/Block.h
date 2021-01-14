#ifndef BLOCK_H
#define BLOCk_H
#include<iostream>
class Piece;

class Block
{
private:
	int x; int y;
	Piece* piece;
public:
	//constructor
	Block();
	Block(int x, int y, Piece* piece);
	~Block();

	//getters and setters
	int getX();
	int getY();
	bool getIsWhitePiece();
	Piece* getPiece();
	void setX(int x);
	void setY(int y);
	void setPiece(Piece* piece);

	// overload insertion operator
	friend std::ostream& operator <<(std::ostream& _cout, const Block& obj);
};
#endif