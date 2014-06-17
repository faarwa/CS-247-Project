#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "CardHand.h"

using namespace std;

class Player {
public:
	Player(vector<Card> cards);
	void addCardToHand(const Card card) const;
	virtual void print() const;
private:
	CardHand _cards;
};

#endif