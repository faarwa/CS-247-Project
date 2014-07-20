#include <gtkmm.h>
#include <iostream>	
#include <cstdlib>

#include "Game.h"
#include "GameViewController.h"
#include "GameView.h"
#include "GameDialogBox.h"

using namespace std;

Game *game;

int main(int argc, char* argv[]) {
	Gtk::Main   kit( argc, argv );          
	game = new Game();
	GameViewController controller (game);
	GameView view(&controller, game);
	Gtk::Main::run( view );

	return 0;
}
