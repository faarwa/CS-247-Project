#include "Player.h"

Player::Player(vector<Card*> cards) {
	_cards = CardHand(cards);
	_topCard = NULL;
}

Player::~Player() {
	delete _topCard;
	for (vector<Card*>::iterator it = _hearts.begin(); it != _hearts.end(); it++) {
		delete (*it);
	}

	for (vector<Card*>::iterator it = _diamonds.begin(); it != _diamonds.end(); it++) {
		delete (*it);
	}

	for (vector<Card*>::iterator it = _clubs.begin(); it != _clubs.end(); it++) {
		delete (*it);
	}

	for (vector<Card*>::iterator it = _spades.begin(); it != _spades.end(); it++) {
		delete (*it);
	}
}