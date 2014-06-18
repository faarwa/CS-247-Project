#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include <iostream>
#include "Player.h"

class ComputerPlayer : public Player {
public:
	ComputerPlayer(vector<Card*> cards, int playerNumber) : Player(cards, playerNumber) {}
	void play(Card card);
	void print() const;
	Command doTurn();
};

#endif