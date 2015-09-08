#include "GameSupervisor.h"


int main(void)
{

	GameSupervisor marioGame(990, 595);
	marioGame.gameLoop();

	return 0;
}