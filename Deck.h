#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class Deck {
public:
	Deck();
	void print() const;
	void shuffle();
	vector<Card*> cards() const { return _cards; }
private:
	vector<Card*> _cards;
};

#endif