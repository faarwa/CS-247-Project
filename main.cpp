#include <gtkmm.h>
#include <iostream>	
#include <cstdlib>

#include "Command.h"
#include "Game.h"
#include "GameViewController.h"
#include "GameView.h"
#include "GameDialogBox.h"

using namespace std;

Game *game;

int main(int argc, char* argv[]) {
	Gtk::Main   kit( argc, argv );          

	int randomSeed = 0;
	if (argc > 1) {
		randomSeed = atoi(argv[1]);
	}

	srand48(randomSeed);

	game = new Game();
	GameViewController controller (game);
	GameView view(&controller, game);

	Gtk::Main::run( view );
	//game->start();

	return 0;
}
