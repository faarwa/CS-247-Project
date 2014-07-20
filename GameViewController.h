#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H


#include <gtkmm.h>
#include "Game.h"

// class for the game view controller
class GameViewController {
public:
   GameViewController( Game* );		// contructor
   void startButtonClicked();		// startButtonClicked method to be called from the View
   void endButtonClicked();		// endButtonClicked method to be called from the View
   void rageButtonClicked();		// rageButtonClicked method to be called from the View
   void cardClicked(Card *card);	// cardClicked method to be called from the View
   void computerPlay();			// computerPlay method to be called from the View
private:
   Game *_game;				// private game member - the model associated with the controller
};


#endif

