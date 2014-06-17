#ifndef CARDHAND_H
#define CARDHAND_H

#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

class CardHand {
public:
	CardHand();
	CardHand(vector<Card*> cards);
	void addCard(const Card card);
	bool has7S() const;
	vector<Card*> hand() const { return _cards; }
private:
	vector<Card*> _cards;
};

#endif