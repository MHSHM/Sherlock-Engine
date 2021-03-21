#include "Game.h"

int main(void)
{

	Game game;		

	if (game.Initialize()) 
	{
		game.Run_Game(); 
	}

	game.Shutdown_Game();

	return 0; 
}