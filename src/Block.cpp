#include"Block.h"
#include"Piece.h"

//constructors and destructors
Block::Block(): x(0), y(0), piece(nullptr) {}
Block::Block(int x, int y, Piece* piece) {
	this->x = x;
	this->y = y;
	this->piece = piece;
}
Block::~Block() {
	if (piece != nullptr)
		delete piece;
}

//getters and setters
int Block::getX() { return this->x; }
int Block::getY() { return this->y; }
bool Block::getIsWhitePiece() { return this->piece->getIsWhitePiece(); }
Piece* Block::getPiece() { return this->piece; }
void Block::setX(int x) { this->x = x; }
void Block::setY(int y) { this->y = y; }
void Block::setPiece(Piece* piece) { this->piece = piece; }

std::ostream& operator <<(std::ostream& _cout, const Block& obj) {
	if (&obj != nullptr) {
		if (obj.piece != nullptr) {
			std::cout << obj.piece->getPieceType();
		}
	}
	return _cout;
}