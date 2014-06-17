#include "CardHand.h"

CardHand::CardHand() {
}

CardHand::CardHand(const vector<Card*> cards) {
	_cards = cards;
}

bool isCard7S(Card *c) {
	if (c->getSuit() == SPADE && c->getRank() == SEVEN) {
		return true;
	}

	return false;
}

bool CardHand::has7S() const {

	if (find_if(_cards.begin(), _cards.end(), isCard7S) == _cards.end()) {
		return false;
	}

	return true;
}