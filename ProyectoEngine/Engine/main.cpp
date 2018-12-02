#include "Game.h"
#include <iostream>
using namespace std;

int main() {
	GameBase* game = new Game();
	if (game->Start(800,600, (char*)&"IziEngine")) {
		game->Loop();
	}
	game->Stop();
	delete game;
	return 0;
}