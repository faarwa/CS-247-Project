#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include <iostream>
#include "Player.h"

// Subclass of Player
class ComputerPlayer : public Player {
public:
	ComputerPlayer(int playerNumber) : Player(playerNumber) { _canRage = false; }	// Constructor that constructs a computer player with a player number
	ComputerPlayer(Player &player) : Player(player) {}			// Copy constructor that constructs a player with another player
	void play(Card card);										// Overridden method for play
	void print() const {}										// Overridden method to print lines (empty for computer)
	void discard(Card card);									// Overridden method to discard a card
	Command doTurn();											// Ovverridden method for a player to do a turn

	bool canPlay(Card *card){return true;}
};

#endif
