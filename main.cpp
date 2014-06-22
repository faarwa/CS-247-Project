#include <iostream>	
#include <cstdlib>

#include "Command.h"
#include "Game.h"

using namespace std;

Game *game;

int main(int argc, const char* argv[]) {
	int randomSeed = 0;
	if (argc > 1) {
		cout << "AFJLSK" << endl;
		randomSeed = atoi(argv[1]);
	}

	game = new Game(randomSeed);
	game->start();

	return 0;
}