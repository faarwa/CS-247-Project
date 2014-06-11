#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include "Player.h"

class HumanPlayer : Player {
public:
	HumanPlayer();
private:
	vector<Card> _suits;
	vector<Card> _clubs;
	vector<Card> _hearts;
	vector<Card> _spades;
};

#endif