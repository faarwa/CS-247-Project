#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>
#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer(vector<Card*> cards) : Player(cards) {}
	void play() const;
	void print() const;
	void discard() const;
private:
};

#endif