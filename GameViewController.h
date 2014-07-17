/*
 * MVC example of GTKmm program
 *
 * Controller class.  Is responsible for translating UI events (from the View)
 * into method calls to the Model.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H


#include <gtkmm.h>
#include "Game.h"

// class Card;

class GameViewController {
public:
   GameViewController( Game* );
   void startButtonClicked();
   void endButtonClicked();
private:
   Game *_game;
}; // Controller


#endif

