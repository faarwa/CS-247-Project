#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Card.h"

using namespace std;

class Player {
public:
	Player();
	vector<Card> cards() const { return _cards; }
private:
	vector<Card> _cards;
};

#endif