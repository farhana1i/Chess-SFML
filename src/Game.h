#ifndef GAME_H
#define GAME_H

#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"Piece.h"
#include"Player.h"
#include"Board.h"
#include"Block.h"
#include"Move.h"

class Game
{
	Board* game_board;				// chess board
	Player* whitePlayer;
	Player* blackPlayer;
	Move** listOfAllMoves;			// to store all moves
	Piece** listOfKilledPieces;		// all killed pieces irrespective of color
	int numOfKilledPieces;
	int numOfAllMoves;				// count of all moves
	bool isCastlingDone;
public:
	Game(Board* game_board, Player* whitePlayer, Player* blackPlayer);
	~Game();

	// control of game
	void runGame();

	//get Player according to turn
	Player* getPlayer();
	Player* getNotTurnPlayer();

	// conditions for castling 
	// HINT:
	// i)	direction = -1             // king towards right
	// ii)	direction = 1              // king towards left
	// iii)	direction = -5             // right side rook
	// iv)	direction = 5              // left side rook
	Block** castling(int src_row, int src_col, int des_row, int des_col, int& numOfAllValidMoves);

	//	conditions for checkmate
	bool isCheckmate(Player* player);

	// to find position of opponent's "KING"
	bool findKingPosition(int& kingPosRow, int& kingPosCol, Player* player);

	// return true if "KING" is in check
	bool isKingInCheck(int kingPosRow, int kingPosCol, Player* player);

	// if pawn is reached towards the opponent boundary
	bool afterPawnPromotion(Piece*& newPiece, char pieceType);

	// to close window
	void closeWindow(sf::RenderWindow& window, sf::Event& evnt);

	// to draw and display on window
	void drawRectangles(sf::RenderWindow& window,sf::RectangleShape**& matrixOfRectangles, int numOfRectangles,
		sf::Texture*& p1, sf::Texture*& r1, sf::Texture*& n1, sf::Texture*& b1, sf::Texture*& k1, sf::Texture*& q1,
		sf::Texture*& p2, sf::Texture*& r2, sf::Texture*& n2, sf::Texture*& b2, sf::Texture*& k2, sf::Texture*& q2);

	// to get valid source input
	bool getValidInput(sf::RenderWindow& window, int& row, int& col);

	// get texture for a specific piece
	sf::Texture* getTexture(Piece* piece, sf::Texture*& p1, sf::Texture*& r1, sf::Texture*& n1, sf::Texture*& b1, sf::Texture*& k1, sf::Texture*& q1,
		sf::Texture*& p2, sf::Texture*& r2, sf::Texture*& n2, sf::Texture*& b2, sf::Texture*& k2, sf::Texture*& q2);

	// to color boarder
	void colorBorder(sf::RectangleShape**& matrixOfRectangles, sf::Texture& dark_box_texture, sf::Texture& light_box_texture, Block**& list, int num);
};
#endif // !GAME_H