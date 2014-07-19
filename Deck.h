#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

// Deck class
class Deck {
public:
	Deck();												// default constructor - constructs a deck with all the 52 cards		
	void print() const;									// print method - to be called when the user uses the deck command (debugging)
	void shuffle(int seed);										// shuffles the deck
	vector<Card*> cards() const { return _cards; }		// accessor - returns the cards in the deck
private:
	vector<Card*> _cards;								// private data member - vector of Cards in the deck
};

#endif