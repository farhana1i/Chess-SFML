#include "Move.h"

// constructors
Move::Move() :src_col(0), src_row(0), des_col(0), des_row(0) {}
Move::Move(char src_col, char src_row, char des_col, char des_row) {
	this->src_col = src_col;
	this->src_row = src_row;

	this->des_col = des_col;
	this->des_row = des_row;
}

// getters and setters
char Move::getSourceColumn() { return src_col; }
char Move::getSourceRow() { return src_row; }
char Move::getDestinationColumn() { return des_col; }
char Move::getDestinationRow() { return des_row; }

// overload ofstream operator
std::ofstream& operator<<(std::ofstream& _fout, const Move& move) {
	if (&move != nullptr) {
		_fout << move.src_col << move.src_row << " " << move.des_col << move.des_row << std::endl;
	}
	return _fout;
}