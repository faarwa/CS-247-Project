#include "Deck.h"

Deck::Deck() {

	for (int i = CLUB; i != SUIT_COUNT; i++) {
		for (int j = ACE; j != RANK_COUNT; j++) {
			Card card = Card(static_cast<Suit>(i), static_cast<Rank>(j));
			_cards.push_back(card);
		}
	}
}

void Deck::print() const {
	for (int i = 0; i < _cards.size(); i++) {
		cout << _cards.at(i);
		if ((i+1)%13 == 0) {
			cout << endl;
		} else {
			cout << " ";
		}
	}
}