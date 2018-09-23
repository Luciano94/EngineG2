#include "Game.h"
#include <iostream>
using namespace std;

int main() {
	Game* game = new Game();
	if (game->Start(800,600, (char*)&"Hoola")) {
		game->Loop();
	}
	game->Stop();
	delete game;
	return 0;
}