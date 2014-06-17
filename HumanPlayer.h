#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>
#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer(vector<Card*> cards) : Player(cards) {}
	Card* play(Card* card);
	void print() const;
	void discard(Card *card) const;
private:
};

#endif