#pragma once
#include<fstream>
class Move
{
	char src_col;		// source column
	char src_row;		// source row
	char des_col;		// destination column
	char des_row;		// destination row
public:
	// constructors
	Move();
	Move(char src_col, char src_row, char des_col, char des_row);

	// getters and setters
	char getSourceColumn();
	char getSourceRow();
	char getDestinationColumn();
	char getDestinationRow();

	// overload ofstream operator
	friend std::ofstream& operator<<(std::ofstream& _fout, const Move& move);
};

