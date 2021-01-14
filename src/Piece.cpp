#include<cstring>
#include<iostream>
#include "Piece.h"

//constructors and destructor
Piece::Piece(const char* piece_type, bool is_white, bool is_first_move) {
	this->piece_type = new char[strlen(piece_type) + 1];
	strcpy_s(this->piece_type, strlen(piece_type) + 1, piece_type);
	
	this->is_first_move = is_first_move;
	this->is_white = is_white;
}


void Piece::setPieceType(const char* piece_type) {
	if (this->piece_type != nullptr)
		delete[] this->piece_type;
	this->piece_type = new char[strlen(piece_type) + 1];
	strcpy_s(this->piece_type, strlen(piece_type) + 1, piece_type);
}
void Piece::setFirstMove(bool is_first_move) {
	this->is_first_move = is_first_move;
}
void Piece::setIsWhite(bool is_white) {
	this->is_white = is_white;
}

char* Piece::getPieceType() { return piece_type; }
bool Piece::getIsWhitePiece() { return is_white; }
bool Piece::getIsFirstMove() { return is_first_move; }
