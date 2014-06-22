#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include <iostream>
#include "Player.h"

class ComputerPlayer : public Player {
public:
	ComputerPlayer(int playerNumber) : Player(playerNumber) {}
	ComputerPlayer(Player &player) : Player(player) {}
	void play(Card card);
	void print() const;
	void discard(Card card);
	Command doTurn();
};

#endif