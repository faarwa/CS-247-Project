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
private:
	vector<Card> _cards;
};

#endif