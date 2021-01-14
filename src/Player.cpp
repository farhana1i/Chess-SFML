#include "Player.h"

//constructors and destructor
Player::Player() {
	this->name = nullptr;
	this->is_white = true;
	this->is_turn = true;
	this->isCastlingPerformed = false;
}
Player::Player(const char* name, bool is_white) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
	this->is_white = is_white;
	this->is_turn = this->is_white;			// white should move first
	this->isCastlingPerformed = false;
}
Player::~Player() {
	if (name != nullptr)
		delete[] name;
}

// getters and setters
void Player::setIsWhite(bool is_white) {
	this->is_white = is_white;
}
void Player::setName(const char* name) {
	if (this->name != nullptr)
		delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}
void Player::setIsTurn(bool is_turn) { this->is_turn = is_turn; }
void Player::setIsCastlingPerformed(bool isCastlingPerformed) { this->isCastlingPerformed = isCastlingPerformed; }
char* Player::getName() { return name; }
bool Player::getIsWhite() { return is_white; }
bool Player::getIsTurn() { return is_turn; }
bool Player::getIsCastlingPerformed() { return this->isCastlingPerformed; }
