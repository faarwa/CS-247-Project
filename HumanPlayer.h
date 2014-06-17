#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>
#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer(vector<Card*> cards, int playerNumber) : Player(cards, playerNumber) {}
	void play(Card *card);
	void print() const;
private:
};

#endif