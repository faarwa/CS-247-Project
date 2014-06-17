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
	vector<Card> diamonds() const { return _diamonds; }
	vector<Card> clubs() const { return _clubs; }
	vector<Card> hearts() const { return _hearts; }
	vector<Card> spades() const { return _spades; }
private:
	vector<Card*> _cards;
	vector<Card> _diamonds;
	vector<Card> _clubs;
	vector<Card> _hearts;
	vector<Card> _spades;
};

#endif