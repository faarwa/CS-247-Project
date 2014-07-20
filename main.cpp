#include <gtkmm.h>
#include <iostream>	
#include <cstdlib>

#include "Game.h"
#include "GameViewController.h"
#include "GameView.h"
#include "GameDialogBox.h"

using namespace std;

// global game
Game *game;

// main definition
int main(int argc, char* argv[]) {
	
	// creating a new game
	Gtk::Main   kit( argc, argv );          
	game = new Game();
	// creating a controller for the model game
	GameViewController controller (game);
	// creating a view and connecting it to the conntroller
	GameView view(&controller, game);
	// runs the game
	Gtk::Main::run( view );

	return 0;
}
