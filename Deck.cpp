#include "Deck.h"
#include <cstdlib>

// Default constructor
Deck::Deck() {

	// Construct each of the 52 cards and add to vector
	for (int i = CLUB; i != SUIT_COUNT; i++) {
		for (int j = ACE; j != RANK_COUNT; j++) {
			Card* card = new Card(static_cast<Suit>(i), static_cast<Rank>(j));
			_cards.push_back(card);
		}
	}
}

// Iterate through the vector and print the cards
void Deck::print() const {
	for (int i = 0; i < _cards.size(); i++) {
		cout << *_cards.at(i);
		if ((i+1)%13 == 0) {
			cout << endl;
		} else {
			cout << " ";
		}
	}
}

// Shuffle function given in assignment
void Deck::shuffle() {
	int n = _cards.size();

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = _cards[n];
		_cards[n] = _cards[k];
		_cards[k] = c;
	}
}