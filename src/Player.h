#ifndef PLAYER_H
#define PLAYER_H

#include"Piece.h"

class Player {
	char* name;
	bool is_white;
	bool is_turn;
	bool isCastlingPerformed;
public:
	Player();
	Player(const char* name, bool is_white);
	~Player();

	void setIsCastlingPerformed(bool isCastlingPerformed);
	void setName(const char* name);
	void setIsWhite(bool is_white);
	void setIsTurn(bool is_turn);
	char* getName();
	bool getIsWhite();
	bool getIsTurn();
	bool getIsCastlingPerformed();
};
#endif // !PLAYER_H
