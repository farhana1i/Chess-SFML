#include "Game.h"
#include"Queen.h"
#include"Bishop.h"
#include"Rook.h"
#include"Knight.h"
#include<fstream>
#include<Windows.h>

// constructors
Game::Game(Board* game_board, Player* whitePlayer, Player* blackPlayer)
{
	this->whitePlayer = whitePlayer;
	this->blackPlayer = blackPlayer;
	this->game_board = game_board;
	this->isCastlingDone = false;

	listOfAllMoves = new Move * [500];			// all moves which have done in a game
	numOfAllMoves = 0;
	listOfKilledPieces = new Piece * [32];		// maximum pieces are 32, 16 pieces for each player
	numOfKilledPieces = 0;
}

//destructor
Game::~Game()
{
	std::ofstream fout("moves.txt");
	if (fout.is_open()) {
		for (int i = 0; i < numOfAllMoves; i++) {
			if (listOfAllMoves[i] != nullptr)
				fout<<(*listOfAllMoves[i]);
		}
	}

	for (int i = 0; i < numOfAllMoves; i++) {
		if (listOfAllMoves[i] != nullptr)
			delete listOfAllMoves[i];
	}
	if (listOfAllMoves != nullptr)
		delete[] listOfAllMoves;
}

// control of game
void Game::runGame()
{
	/***************************************		FOR	GRAPHIC			**********************************/
	// to ignore hardware connection errors
	sf::err().rdbuf(NULL);

	sf::RenderWindow window(sf::VideoMode(850, 610), "CHESS by Farhan", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape background(sf::Vector2f(550, 600));
	background.setPosition(sf::Vector2f(5, 5));

	int numOfRectangles = 8;
	sf::RectangleShape** matrixOfRectangles = new sf::RectangleShape * [numOfRectangles];
	for (int i = 0; i < numOfRectangles; i++)
		matrixOfRectangles[i] = new sf::RectangleShape[numOfRectangles];

	// dark and light box with green border
	sf::Texture dark_box_texture, light_box_texture;
	dark_box_texture.loadFromFile("images\\dark-box.png");
	light_box_texture.loadFromFile("images\\light-box.png");


	// stalemate, checkmate, check ,etc textures
	sf::Texture cm, sm, wp, bp;
	sf::RectangleShape checkmate_texture(sf::Vector2f(400.f, 100.f)), stalemate_texture(sf::Vector2f(400.f, 100.f)),
		whitePlayer_texture(sf::Vector2f(400.f, 100.f)), blackPlayer_texture(sf::Vector2f(400.f, 100.f));
	
	// set textures
	cm.loadFromFile("images\\checkmate_icon.png");
	checkmate_texture.setTexture(&cm);
	checkmate_texture.setPosition(sf::Vector2f(85.f, 290.f));
	sm.loadFromFile("images\\stalemate_icon.png");
	stalemate_texture.setTexture(&sm);
	stalemate_texture.setPosition(sf::Vector2f(85.f, 290.f));
	wp.loadFromFile("images\\white_player_icon.png");
	whitePlayer_texture.setTexture(&wp);
	whitePlayer_texture.setPosition(sf::Vector2f(85.f, 190.f));
	bp.loadFromFile("images\\black_player_icon.png");
	blackPlayer_texture.setTexture(&bp);
	blackPlayer_texture.setPosition(sf::Vector2f(85.f, 190.f));

	//	click button music
	sf::Music click_audio;
	click_audio.openFromFile("images\\click.wav");
	
	// load font
	sf::Font font;
	font.loadFromFile("images\\font.ttf");
	sf::Font font_1;
	font_1.loadFromFile("images\\font_1.ttf");


	//width of each rectangle ---> width = 56.3f
	//height of each rectangle ---> height = 61.9f
	float ycord = 57.2f;
	//set positions of rectangles
	for (int i = 0; i < numOfRectangles; i++) {
		float xcord = 54.f;
		for (int j = 0; j < numOfRectangles; j++) {
			matrixOfRectangles[i][j].setSize(sf::Vector2f(56.3f, 61.9f));
			matrixOfRectangles[i][j].setPosition(sf::Vector2f(xcord, ycord));
			xcord += 56.3f;
		}
		ycord += 61.9f;
	}

	sf::Texture background_texture;
	background_texture.loadFromFile("images\\background.png");
	background.setTexture(&background_texture);

	//textures of CHESS white pieces
	sf::Texture* p1 = new sf::Texture();
	sf::Texture* r1 = new sf::Texture();
	sf::Texture* n1 = new sf::Texture();
	sf::Texture* b1 = new sf::Texture();
	sf::Texture* k1 = new sf::Texture();
	sf::Texture* q1 = new sf::Texture();
	p1->loadFromFile("images\\white-pawn.png");
	p1->setSmooth(true);
	r1->loadFromFile("images\\white-rook.png");
	r1->setSmooth(true);
	n1->loadFromFile("images\\white-knight.png");
	n1->setSmooth(true);
	b1->loadFromFile("images\\white-bishop.png");
	b1->setSmooth(true);
	k1->loadFromFile("images\\white-king.png");
	k1->setSmooth(true);
	q1->loadFromFile("images\\white-queen.png");
	q1->setSmooth(true);

	//textures of CHESS black pieces
	sf::Texture* p2 = new sf::Texture();
	sf::Texture* r2 = new sf::Texture();
	sf::Texture* n2 = new sf::Texture();
	sf::Texture* b2 = new sf::Texture();
	sf::Texture* k2 = new sf::Texture();
	sf::Texture* q2 = new sf::Texture();
	p2->loadFromFile("images\\pawn.png");
	p2->setSmooth(true);
	r2->loadFromFile("images\\rook.png");
	r2->setSmooth(true);
	n2->loadFromFile("images\\knight.png");
	n2->setSmooth(true);
	b2->loadFromFile("images\\bishop.png");
	b2->setSmooth(true);
	k2->loadFromFile("images\\king.png");
	k2->setSmooth(true);
	q2->loadFromFile("images\\queen.png");
	q2->setSmooth(true);


	// for pawn promotion, to display options
	sf::RectangleShape pawn_window(sf::Vector2f(450.f, 150.f));
	pawn_window.setPosition(sf::Vector2f(54.5f, 200.f));
	sf::Texture pawn_window_texture;
	pawn_window_texture.loadFromFile("images\\pawn_window.png");
	pawn_window.setTexture(&pawn_window_texture);
	pawn_window.setOutlineColor(sf::Color(200, 60, 60));
	pawn_window.setOutlineThickness(5.f);
	sf::RectangleShape pawn_promotion_menu[4];
	float xcord = 62.8f;
	for (int i = 0; i < 4; i++) {
		pawn_promotion_menu[i].setSize(sf::Vector2f(100.f, 110.f));
		pawn_promotion_menu[i].setPosition(sf::Vector2f(xcord, 220.f));
		xcord += 110.f;
	}


	/***************************************	pp	FOR	GRAPHIC	END		**********************************/

	Piece* pieceToMove = nullptr;		// the piece to move
	Piece* pieceToKill = nullptr;		// the piece to kill

	int src_row = -1; int src_col = -1;
	int des_row = -1; int des_col = -1;

	bool is_pre_check_1 = true;
	bool is_pre_check_2 = true;
game_start:
	
	// game loop
	while (window.isOpen())
	{
		sf::Event evnt;
		closeWindow(window, evnt);				// to close window

		char* player_turn = new char[50];
		char* waste = new char[50];
		// to display name of player
		strcpy_s(player_turn, 50, getPlayer()->getName());
		
		if (getPlayer()->getIsWhite())
			strcpy_s(waste, 50, "'s Turn [White_Player]");
		else
			strcpy_s(waste, 50, "'s Turn [Black_Player]");
		strcat_s(player_turn, 50, waste);
		sf::Text turn(player_turn, font_1, 18);
		turn.setPosition(sf::Vector2f(570.f, 50.f));
		turn.setFillColor(sf::Color(200, 50 ,50));


		// to clear window
		window.clear(sf::Color::White);
		// to draw something
		window.draw(background);
		drawRectangles(window, matrixOfRectangles, numOfRectangles, p1, r1, n1, b1, k1, q1, p2, r2, n2, b2, k2, q2);			// draw matrix of rectangles
		window.draw(turn);

		// to find king's position
		int kingPosRow; int kingPosCol;
		findKingPosition(kingPosRow, kingPosCol, getPlayer());

		// stalemate
		if (isCheckmate(getPlayer())) 
		{
			bool prev_check;
			if (getPlayer()->getIsWhite())
				prev_check = is_pre_check_1;
			else
				prev_check = is_pre_check_2;

			if (!prev_check) 
			{
				sf::Text text("Press Escape to exit", font, 60);
				text.setPosition(sf::Vector2f(110.f, 370.f));
				text.setFillColor(sf::Color::Black);
				window.draw(text);
				window.draw(stalemate_texture);
				// to display on window
				window.display();
				closeWindow(window, evnt);			// to close window
			}
			else
			{
				sf::Text text("Press Escape to exit", font, 60);
				text.setPosition(sf::Vector2f(110.f, 370.f));
				text.setFillColor(sf::Color::Black);
				if (!getPlayer()->getIsWhite())
					window.draw(whitePlayer_texture);
				else
					window.draw(blackPlayer_texture);
				window.draw(text);
				window.draw(checkmate_texture);
				window.display();					// to display on window
				closeWindow(window, evnt);			// ti close window
			}
		}
		else
		{
			// king in check
			if (isKingInCheck(kingPosRow, kingPosCol, getPlayer()))
			{
				// for stalemate, store either player was in check or not
				if (getPlayer()->getIsWhite())
					is_pre_check_1 = false;			// for white player
				else
					is_pre_check_2 = false;			// for black player

				sf::Text text("::Your King Is In Check::", font_1, 18);
				text.setPosition(sf::Vector2f(590.f, 80.f));
				text.setFillColor(sf::Color::Red);
				// to draw something
				window.draw(text);
			}

			// to draw something
			window.draw(background);
			// draw matrix of rectangles
			drawRectangles(window, matrixOfRectangles, numOfRectangles, p1, r1, n1, b1, k1, q1, p2, r2, n2, b2, k2, q2);																														// to display on window
			window.display();

			//loop for taking valid source inputs
			while (true)
			{
				// getting valid indexes in input
				if (getValidInput(window, src_row, src_col)) {
					click_audio.play();
					if ((*game_board)[src_row][src_col]->getPiece() != nullptr &&
						(*game_board)[src_row][src_col]->getIsWhitePiece() == getPlayer()->getIsWhite())
						break;
				}
			}

			// assume valid inputs are given
			int numOfAllValidBlocks = 0;
			pieceToMove = (*game_board)[src_row][src_col]->getPiece();
			Block** listOfAllValidBlocks = pieceToMove->getAllValidBlocks(*game_board, src_row, src_col, numOfAllValidBlocks);

			//again take inputs, if number of all valid blocks are zero
			if (numOfAllValidBlocks == 0)
				goto game_start;

			// enpassant moves
			Block** enpassantBlocks = new Block * [5];
			int enpassantBlocksCount = 0;
			bool is_enpassant = false;
			// en passant
			if (!strcmp(pieceToMove->getPieceType(), "Pawn") && numOfAllMoves > 0) {
				pieceToMove->isEnPassant(*game_board, listOfAllMoves[numOfAllMoves - 1], src_row, src_col, listOfAllValidBlocks, numOfAllValidBlocks);
				is_enpassant = pieceToMove->isEnPassant(*game_board, listOfAllMoves[numOfAllMoves - 1], src_row, src_col, enpassantBlocks, enpassantBlocksCount);
			}

			// display boarder of all valid blocks of a specific piece
			colorBorder(matrixOfRectangles, dark_box_texture, light_box_texture, listOfAllValidBlocks, numOfAllValidBlocks);


			//	*******************************		Castling	  **********************
			Block** listOfCastleBlocks = nullptr;
			int numOfCastleBlocks = 0;
			if (!getPlayer()->getIsCastlingPerformed()) {
				listOfCastleBlocks = castling(src_row, src_col, des_row, des_col, numOfCastleBlocks);

				// display boarder of all valid blocks of a specific piece
				colorBorder(matrixOfRectangles, dark_box_texture, light_box_texture, listOfCastleBlocks, numOfCastleBlocks);
			}

			// to clear window
			window.clear(sf::Color::White);
			// to draw something
			window.draw(background);
			// to display border around valid blocks
			for (int i = 0; i < numOfRectangles; i++)
				for (int j = 0; j < numOfRectangles; j++) {
					if (matrixOfRectangles[i][j].getTexture() == nullptr) continue;
					window.draw(matrixOfRectangles[i][j]);
				}
			// to display on window
			window.draw(turn);
			window.display();


			//loop for taking valid destination inputs
			if (numOfAllValidBlocks > 0) {
				bool isBreak = true;
				while (isBreak)
				{
					if (getValidInput(window, des_row, des_col))
					{
						click_audio.play();
						for (int i = 0; i < numOfAllValidBlocks; i++) {
							if (listOfAllValidBlocks[i]->getX() == des_col &&
								listOfAllValidBlocks[i]->getY() == des_row) {
								isBreak = false;
								break;
							}
						}

						// for castling blocks
						for (int i = 0; i < numOfCastleBlocks; i++) {
							if (listOfCastleBlocks[i]->getX() == des_col &&
								listOfCastleBlocks[i]->getY() == des_row) {
								isBreak = false;
								break;
							}
						}
					}
				}
			}

			// hide border of valid blocks
			for (int i = 0; i < numOfAllValidBlocks; i++) {
				int x = listOfAllValidBlocks[i]->getX();
				int y = listOfAllValidBlocks[i]->getY();
				if (x != des_col || y != des_row) {
					matrixOfRectangles[y][x].setTexture(nullptr);
				}
				matrixOfRectangles[y][x].setOutlineColor(sf::Color::Transparent);
			}

			// for castling blocks
			for (int i = 0; i < numOfCastleBlocks; i++) {
				int x = listOfCastleBlocks[i]->getX();
				int y = listOfCastleBlocks[i]->getY();
				if (x != des_col || y != des_row) {
					matrixOfRectangles[y][x].setTexture(nullptr);
				}
				matrixOfRectangles[y][x].setOutlineColor(sf::Color::Transparent);
			}

			// to check either destination inputs are valid or not
			bool should_move = false;
			for (int i = 0; i < numOfAllValidBlocks; i++) {
				if (listOfAllValidBlocks[i]->getX() == des_col && listOfAllValidBlocks[i]->getY() == des_row) {
					should_move = true;
					break;
				}
			}
			bool castle_should_move = false;
			for (int i = 0; i < numOfCastleBlocks; i++) {
				if (listOfCastleBlocks[i]->getX() == des_col && listOfCastleBlocks[i]->getY() == des_row) {
					castle_should_move = true;
					break;
				}
			}

			// if moves are invalid, again take inputs
			if (!castle_should_move && !should_move) 
			{
				goto game_start;
			}
			else 
			{
				pieceToKill = game_board->getBlock(des_row, des_col)->getPiece();
			}


			// if destination coordinates are valid, move the piece
			if (should_move)
			{
				//move piece ---> set board
				game_board->getBlock(des_row, des_col)->setPiece(pieceToMove);
				game_board->getBlock(src_row, src_col)->setPiece(nullptr);

				// for enpassant ---> set board
				if (is_enpassant) {
					for (int i = 0; i < enpassantBlocksCount; i++) {
						if (enpassantBlocks[i]->getX() == des_col && enpassantBlocks[i]->getY() == des_row) {
							int downward = -1;
							if (getPlayer()->getIsWhite())
								downward = 1;

							Piece* p = game_board->getBlock(des_row + downward, des_col)->getPiece();
							game_board->getBlock(des_row + downward, des_col)->setPiece(nullptr);

							if (isKingInCheck(kingPosRow, kingPosCol, getPlayer())) {
								game_board->getBlock(des_row + downward, des_col)->setPiece(p);
							}
						}
					}
				}
			}

			// if destination coordinates are valid, move the piece ---> set board for castling
			if (castle_should_move)
			{
				game_board->getBlock(des_row, des_col)->setPiece(pieceToMove);
				game_board->getBlock(src_row, src_col)->setPiece(nullptr);
				int col1 = -1, col2 = -1;

				if (src_col == 4) {
					if (src_col - des_col > 0) {		// castling queen-sdie
						game_board->getBlock(src_row, 3)->setPiece(game_board->getBlock(src_row, 0)->getPiece());
						game_board->getBlock(src_row, 0)->setPiece(nullptr);
						col1 = 0;
						col2 = 3;
					}
					else {								// castling king-sdie
						game_board->getBlock(src_row, 5)->setPiece(game_board->getBlock(src_row, 7)->getPiece());
						game_board->getBlock(src_row, 7)->setPiece(nullptr);
						col1 = 7;
						col2 = 5;
					}
				}
				// for check conditions
				findKingPosition(kingPosRow, kingPosCol, getPlayer());
				if (isKingInCheck(kingPosRow, kingPosCol, getPlayer()))
				{
					(*game_board)[src_row][col1]->setPiece((*game_board)[src_row][col2]->getPiece());
					(*game_board)[src_row][col2]->setPiece(nullptr);
				}
				else {
					getPlayer()->setIsCastlingPerformed(true);
				}
			}

			//deallocate memory
			if (enpassantBlocks != nullptr)
				delete[] enpassantBlocks;

			// for check conditions
			findKingPosition(kingPosRow, kingPosCol, getPlayer());
			if (isKingInCheck(kingPosRow, kingPosCol, getPlayer()))
			{
				sf::Text text("::Your King Is In Check::", font_1, 18);
				text.setPosition(sf::Vector2f(590.f, 80.f));
				text.setFillColor(sf::Color::Red);
				// to draw something
				window.draw(text);
				(*game_board)[src_row][src_col]->setPiece(pieceToMove);
				(*game_board)[des_row][des_col]->setPiece(pieceToKill);
				goto game_start;
			}

			// pawn promotion
			if (!strcmp(pieceToMove->getPieceType(), "Pawn"))
			{
				if (des_row == 0 || des_row == 7)
				{
					if (getPlayer()->getIsWhite()) {
						pawn_promotion_menu[0].setTexture(q1);
						pawn_promotion_menu[1].setTexture(b1);
						pawn_promotion_menu[2].setTexture(r1);
						pawn_promotion_menu[3].setTexture(n1);
					}
					else {
						pawn_promotion_menu[0].setTexture(q2);
						pawn_promotion_menu[1].setTexture(b2);
						pawn_promotion_menu[2].setTexture(r2);
						pawn_promotion_menu[3].setTexture(n2);
					}

					pawn_promotion_menu[0].setOutlineColor(sf::Color(200, 70, 70));
					pawn_promotion_menu[0].setOutlineThickness(5.f);
					pawn_promotion_menu[1].setOutlineColor(sf::Color(200, 70, 70));
					pawn_promotion_menu[1].setOutlineThickness(5.f);
					pawn_promotion_menu[2].setOutlineColor(sf::Color(200, 70, 70));
					pawn_promotion_menu[2].setOutlineThickness(5.f);
					pawn_promotion_menu[3].setOutlineColor(sf::Color(200, 70, 70));
					pawn_promotion_menu[3].setOutlineThickness(5.f);

					window.clear(sf::Color::White);
					// to draw something
					window.draw(background);
					// to display border around valid blocks
					for (int i = 0; i < numOfRectangles; i++)
						for (int j = 0; j < numOfRectangles; j++) {
							if (matrixOfRectangles[i][j].getTexture() == nullptr) continue;
							window.draw(matrixOfRectangles[i][j]);
						}
					window.draw(turn);
					window.draw(pawn_window);
					for (int i = 0; i < 4; i++)
						window.draw(pawn_promotion_menu[i]);
					// to display on window
					window.display();

					Piece* newPiece = nullptr;
					int input_row = -1; int input_col = -1;
					bool isBreak = false;
					while (!isBreak)
					{
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							sf::Vector2i mousePos = sf::Mouse::getPosition(window);
							click_audio.play();

							input_col = int((mousePos.x - 62.8) / 100) + 1;
							input_row = mousePos.y;

							if ((input_col > 0 && input_col < 5) && input_row >= 220 && input_row <= 320)
							{
								afterPawnPromotion(newPiece, input_col + 48);
								isBreak = true;
								break;
							}
						}
					}

					game_board->getBlock(des_row, des_col)->setPiece(newPiece);
				}
			}

			// HINT: conversion from "int --> char"
			char source_row = abs(src_row - 8) + 48;
			char source_col = src_col + 97;
			char destination_row = abs(des_row - 8) + 48;
			char destination_col = des_col + 97;
			listOfAllMoves[numOfAllMoves++] = new Move(source_col, source_row, destination_col, destination_row);

			// to change turn
			Player* player = getPlayer();
			getNotTurnPlayer()->setIsTurn(true);
			player->setIsTurn(false);

			pieceToMove->setFirstMove(false);
		}

		// deallocate memory
		if (player_turn != nullptr)
			delete[] player_turn;
		if (waste != nullptr)
			delete[] waste;
	}
	// deallocate memory
	delete p1;
	delete r1;
	delete b1;
	delete n1;
	delete k1;
	delete q1;
	delete p2;
	delete r2;
	delete b2;
	delete n2;
	delete k2;
	delete q2;
	// deallocate memory
	for (int i = 0; i < numOfRectangles; i++) {
		if (matrixOfRectangles[i] != nullptr)
			delete[] matrixOfRectangles[i];
	}
	if (matrixOfRectangles != nullptr)
		delete[] matrixOfRectangles;
}

// after pawn promotion, get player choice
bool Game::afterPawnPromotion(Piece*& newPiece, char pieceType) 
{
	if (newPiece != nullptr)
		delete newPiece;

	if (pieceType == '1') {
		newPiece = new Queen(getPlayer()->getIsWhite(), false);
	}
	else if (pieceType == '2') {
		newPiece = new Bishop(getPlayer()->getIsWhite(), false);
	}
	else if (pieceType == '3') {
		newPiece = new Rook(getPlayer()->getIsWhite(), false);
	}
	else if (pieceType == '4') {
		newPiece = new Knight(getPlayer()->getIsWhite(), false);
	}
	return true;
}

// to color boarder
void Game::colorBorder(sf::RectangleShape**& matrixOfRectangles, sf::Texture& dark_box_texture, sf::Texture& light_box_texture, Block**& list, int num) {
	// display boarder of all valid blocks of a specific piece
	for (int i = 0; i < num; i++) {
		int x = list[i]->getX();
		int y = list[i]->getY();
		if (matrixOfRectangles[y][x].getTexture() == nullptr) {
			if ((x + y) % 2 == 0) {
				matrixOfRectangles[y][x].setTexture(&light_box_texture);
			}
			else
			{
				matrixOfRectangles[y][x].setTexture(&dark_box_texture);
			}
		}
		matrixOfRectangles[y][x].setOutlineColor(sf::Color::Green);
		matrixOfRectangles[y][x].setOutlineThickness(2.3f);
	}
}

// get texture for a specific piece
sf::Texture* Game::getTexture(Piece* piece, sf::Texture*& p1, sf::Texture*& r1, sf::Texture*& n1, sf::Texture*& b1, sf::Texture*& k1,
	sf::Texture*& q1, sf::Texture*& p2, sf::Texture*& r2, sf::Texture*& n2, sf::Texture*& b2, sf::Texture*& k2, sf::Texture*& q2)
{	
	if (piece == nullptr)
		return nullptr;

	// pawn's texture
	if (!strcmp(piece->getPieceType(), "Pawn")) {
		if (piece->getIsWhitePiece())
			return p1;
		else
			return p2;
	}

	// rook's texture
	if (!strcmp(piece->getPieceType(), "Rook")) {
		if (piece->getIsWhitePiece())
			return r1;
		else
			return r2;
	}

	// knight's texture
	if (!strcmp(piece->getPieceType(), "Knight")) {
		if (piece->getIsWhitePiece())
			return n1;
		else
			return n2;
	}

	// bishop's texture
	if (!strcmp(piece->getPieceType(), "Bishop")) {
		if (piece->getIsWhitePiece())
			return b1;
		else
			return b2;
	}

	// queen's texture
	if (!strcmp(piece->getPieceType(), "Queen")) {
		if (piece->getIsWhitePiece())
			return q1;
		else
			return q2;
	}

	// king's texture
	if (!strcmp(piece->getPieceType(), "King")) {
		if (piece->getIsWhitePiece())
			return k1;
		else
			return k2;
	}
}


// to close window
void Game::closeWindow(sf::RenderWindow& window, sf::Event& evnt){
	// to close window
	while (window.pollEvent(evnt))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)
			|| evnt.type == sf::Event::Closed) {
			window.close();
			break;
		}
	}
}


// to draw and display on window
void Game::drawRectangles(sf::RenderWindow& window, sf::RectangleShape**& matrixOfRectangles, int numOfRectangles,
	sf::Texture*& p1, sf::Texture*& r1, sf::Texture*& n1, sf::Texture*& b1, sf::Texture*& k1, sf::Texture*& q1,
	sf::Texture*& p2, sf::Texture*& r2, sf::Texture*& n2, sf::Texture*& b2, sf::Texture*& k2, sf::Texture*& q2) {
	for (int i = 0; i < numOfRectangles; i++) {
		for (int j = 0; j < numOfRectangles; j++) 
		{
			matrixOfRectangles[i][j].setTexture(getTexture(game_board->getBlock(i,j)->getPiece(), p1, r1, n1, b1, k1, q1, p2, r2, n2, b2, k2, q2), true);
			if (matrixOfRectangles[i][j].getTexture() == nullptr) continue;
			window.draw(matrixOfRectangles[i][j]);
		}
	}
}

// to get valid inputs
bool Game::getValidInput(sf::RenderWindow& window, int& row, int& col) {
	// getting valid indexes in input
	while (true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			// convert mouse position into valid index
			col = int((mousePos.x - 54.f) / 56.3f);
			row = int((mousePos.y - 56.3f) / 61.9f);

			if (col >= 0 && col < 8 && row >= 0 && row < 8) {
				return true;
			}
		}
	}
	return false;
}

//get Player opposite to turn
Player* Game::getNotTurnPlayer() {
	if (!whitePlayer->getIsTurn())
		return whitePlayer;
	return blackPlayer;
}

//get Player according to turn
Player* Game::getPlayer() {
	if (whitePlayer->getIsTurn())
		return whitePlayer;
	return blackPlayer;
}

// return true, if checkmate
bool Game::isCheckmate(Player* player) {
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			if ((*game_board)[i][j]->getPiece() != nullptr) 
			{
				if ((*game_board)[i][j]->getIsWhitePiece() == player->getIsWhite()) 
				{
					Piece* pieceToCheck = (*game_board)[i][j]->getPiece();
					int numOfAllValidBlocks = 0;
					Block** listOfAllValidMoves = pieceToCheck->getAllValidBlocks(*game_board, i, j, numOfAllValidBlocks);
					int prev_xcord = j;			// store x-coordinate of a piece
					int prev_ycord = i;			// store y-coordinate of a piece

					Piece* pieceToKill = nullptr;
					for (int n = 0; n < numOfAllValidBlocks; n++)
					{
						int xcord = listOfAllValidMoves[n]->getX();
						int ycord = listOfAllValidMoves[n]->getY();
						pieceToKill = (*game_board)[ycord][xcord]->getPiece();		//piece to kill temporarily


						(*game_board)[ycord][xcord]->setPiece(pieceToCheck);
						(*game_board)[prev_ycord][prev_xcord]->setPiece(nullptr);

						int kingPosRow; int kingPosCol;
						findKingPosition(kingPosRow, kingPosCol, player);

						if (!isKingInCheck(kingPosRow, kingPosCol, player)) 
						{
							(*game_board)[ycord][xcord]->setPiece(pieceToKill);
							(*game_board)[prev_ycord][prev_xcord]->setPiece(pieceToCheck);
							return false;
						}
						else 
						{
							(*game_board)[ycord][xcord]->setPiece(pieceToKill);
							(*game_board)[prev_ycord][prev_xcord]->setPiece(pieceToCheck);
						}
					}
				}
			}
		}
	}
	return true;
}

// conditions for castling 
Block** Game::castling(int src_row, int src_col, int des_row, int des_col, int& numOfAllValidMoves) 
{
	Block** listOfAllValidMoves = nullptr;
	if (game_board->getBlock(src_row, src_col)->getPiece() != nullptr)
	{
		if (game_board->getBlock(src_row, src_col)->getPiece()->getIsFirstMove()) 
		{
			if (src_row == 0 || src_row == 7)
			{
				if (!strcmp(game_board->getBlock(src_row, src_col)->getPiece()->getPieceType(), "King"))
				{
					// maximum possible moves is 2 for KING
					listOfAllValidMoves = new Block * [2];
					if (game_board->getBlock(src_row, 0)->getPiece() != nullptr && !strcmp(game_board->getBlock(src_row, 0)->getPiece()->getPieceType(), "Rook"))
					{
						if (game_board->getBlock(src_row, 0)->getPiece()->getIsFirstMove())
						{
							bool isSpace = true;
							for (int i = src_col - 1; i > 1; i--) {
								if (game_board->getBlock(src_row, i)->getPiece() != nullptr
									|| isKingInCheck(src_row, i, getPlayer())) {
									isSpace = false;
									break;
								}
							}
							if (game_board->getBlock(src_row, 1)->getPiece() != nullptr)
								isSpace = false;

							if (isSpace) {
								listOfAllValidMoves[numOfAllValidMoves++] = game_board->getBlock(src_row, src_col - 2);

							}
						}
					}
					if (game_board->getBlock(src_row, 7)->getPiece() != nullptr && !strcmp(game_board->getBlock(src_row, 7)->getPiece()->getPieceType(), "Rook"))
					{
						if (game_board->getBlock(src_row, 7)->getPiece()->getIsFirstMove())
						{
							bool isSpace = true;
							for (int i = src_col + 1; i < 7; i++) {
								if (game_board->getBlock(src_row, i)->getPiece() != nullptr
									|| isKingInCheck(src_row, i, getPlayer())) {
									isSpace = false;
									break;
								}
							}
							if (isSpace) {
								listOfAllValidMoves[numOfAllValidMoves++] = game_board->getBlock(src_row, src_col + 2);
							}
						}
					}
				}
			}
		}
	}
	return listOfAllValidMoves;
}

// to find position of "KING" of a player
bool Game::findKingPosition(int& kingPosRow, int& kingPosCol, Player* player) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game_board->getBlock(i, j)->getPiece() != nullptr) {
				if (!strcmp(game_board->getBlock(i, j)->getPiece()->getPieceType(), "King")) {
					if (game_board->getBlock(i, j)->getIsWhitePiece() == player->getIsWhite()) {
						kingPosCol = j;
						kingPosRow = i;
						return true;
					}
				}
			}
		}
	}
	return false;
}

// return true if "KING" is in check
bool Game::isKingInCheck(int kingPosRow, int kingPosCol, Player* player) {
	// conditions for "KING" in check
	Block** listOfAllValidBlocks;			// keep record of all valid moves of a piece
	int numOfAllValidBlocks = 0;			// number of all valid moves of a piece
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (game_board->getBlock(i, j)->getPiece() != nullptr) {
				if (game_board->getBlock(i, j)->getIsWhitePiece() == !player->getIsWhite()) {
					numOfAllValidBlocks = 0;
					listOfAllValidBlocks = game_board->getBlock(i, j)->
						getPiece()->getAllValidBlocks(*game_board, i, j, numOfAllValidBlocks);
					for (int k = 0; k < numOfAllValidBlocks; k++) {
						if (listOfAllValidBlocks[k]->getX() == kingPosCol &&
							listOfAllValidBlocks[k]->getY() == kingPosRow) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
