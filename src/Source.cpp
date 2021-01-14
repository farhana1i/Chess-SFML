#include"SFML/Graphics.hpp"
#include"Game.h"
#include"Player.h"

int main() 
{	
	Player* whitePlayer = new Player("Farhan", true);
	Player* blackPlayer = new Player("Raza", false);
	Board* game_board = new Board();
	Game game(game_board, whitePlayer, blackPlayer);

	game.runGame();				// implementation of game

	// deallocate memory
	if(whitePlayer!= nullptr)
		delete whitePlayer;
	if (blackPlayer != nullptr)
		delete blackPlayer;
	if (game_board != nullptr)
		delete game_board;

	return 0;
}
