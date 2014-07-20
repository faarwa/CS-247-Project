#include "GameViewController.h"

// constructor for the game view controller
GameViewController::GameViewController(Game *g) : _game(g) {
	// initialize the model for the controller
	_game = g;
}

// controller calling the model's start method
void GameViewController::startButtonClicked() {
    _game->start();
} 

// controller calling the model's end button clicked method
void GameViewController::endButtonClicked() {
    _game->endCurrentGame();
} 

// controller calling the model's ragequit method when a user ragequits
void GameViewController::rageButtonClicked() {
	_game->ragequit();
}

// controller calling the model's cardClicked method when a card is clicked
void GameViewController::cardClicked(Card *card){
	_game->playOrDiscard(card);
}

// controller calling the model's computerPlay method 
void GameViewController::computerPlay() {
	_game->playOrDiscard(new Card(NOSUIT, NORANK));
}
