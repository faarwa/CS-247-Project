#include "CardHand.h"

CardHand::CardHand() {
}

CardHand::CardHand(const vector<Card> cards) {

}

bool CardHand::has7S() const {
	if (find(_spades.begin(), _spades.end(), Card(SPADE, SEVEN)) == _spades.end()) {
		return false;
	}

	return true;
}