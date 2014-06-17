#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>
#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer(vector<Card*> cards) : Player(cards) {}
	void play(Card* card) const;
	void print() const;
	void discard(Card *card) const;
private:
	vector<Card*> _hearts;
	vector<Card*> _spades;
	vector<Card*> _diamonds;
	vector<Card*> _clubs;
};

#endif