#include <iostream>	
#include <cstdlib>

#include "Command.h"
#include "Game.h"

using namespace std;

Game *game;

int main(int argc, const char* argv[]) {
	int randomSeed = 0;
	if (argc > 1) {
		randomSeed = atoi(argv[1]);
	}

	game = new Game();

	while (!cin.eof()) {
		Command cmd = Command();
		cout << "Enter command:";
		cin >> cmd;

		if (cmd.type == DECK) {
			game->deck.print();
		} else if (cmd.type == QUIT) {
			exit(0);
		}
	}

	return 0;
}