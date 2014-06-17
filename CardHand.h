#ifndef CARDHAND_H
#define CARDHAND_H

#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class CardHand {
public:
	CardHand();
	CardHand(vector<Card> cards);
	void addCard(const Card card);
private:
	vector<Card> _suits;
	vector<Card> _clubs;
	vector<Card> _hearts;
	vector<Card> _spades;
};

#endif