#include "Player.h"

map<Suit, vector<Card*> > Player::cardsPlayed;

Player::Player(vector<Card*> cards) {
	_cards = CardHand(cards);
}

Player::~Player() {
	for (map<Suit, vector<Card*> >::iterator it = cardsPlayed.begin(); it != cardsPlayed.end(); it++) {
		vector<Card*> suitCards = (*it).second;
		for (vector<Card*>::iterator it2 = suitCards.begin(); it2 != suitCards.end(); it2++) {
			delete (*it2);
		}
	}
}