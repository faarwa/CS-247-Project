#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include <iostream>
#include "Player.h"

class ComputerPlayer : public Player {
public:
	ComputerPlayer(vector<Card*> cards) : Player(cards) {}
	void play() const;
	void print() const;
	void discard() const;
};

#endif