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


#include "GameViewController.h"

GameViewController::GameViewController(Game *g) : _game(g) {}


void GameViewController::nextButtonClicked() {
     // model_->nextCard();
} 


void GameViewController::resetButtonClicked() {
     // model_->resetCards();
} 
