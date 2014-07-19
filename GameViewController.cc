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

GameViewController::GameViewController(Game *g) : _game(g) {
	_game = g;
}


void GameViewController::startButtonClicked() {
    _game->start();
} 


void GameViewController::endButtonClicked() {
    _game->resetCards();
} 

void GameViewController::rageButtonClicked() {
	_game->ragequit();
}

void GameViewController::cardClicked(Card *card){
	_game -> playOrDiscard(card);
}
