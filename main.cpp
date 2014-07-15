#include <gtkmm.h>
#include <iostream>	
#include <cstdlib>

#include "Command.h"
#include "Game.h"

using namespace std;

Game *game;

int main(int argc, char* argv[]) {
	Gtk::Main   kit( argc, argv );          
	Gtk::Window window;

	int randomSeed = 0;
	if (argc > 1) {
		randomSeed = atoi(argv[1]);
	}

	srand48(randomSeed);

	game = new Game();
	Gtk::Main::run( window );
	game->start();

	return 0;
}
