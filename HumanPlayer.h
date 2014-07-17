#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "Player.h"

//Subclass of Player
class HumanPlayer : public Player {
public:
	HumanPlayer(int playerNumber) : Player(playerNumber) { _canRage = false; } //Constructor that constructs a human player with a player number
	void play(Card c); 										// Overridden method for play
	void print() const; 									// Overridden method to print lines
	void discard(Card c); 									// Overridden method to discard a card
	Command doTurn(); 										// Ovverridden method for a player to do a turn
	bool canPlay(Card *card);

	class IllegalPlayException {							// Exception class to handle human player making illegal plays
	public:
		IllegalPlayException() {}
	};
	class IllegalDiscardException {							//Exception class to handle human player making illegal discards
	public:
		IllegalDiscardException() {}
	};
private:
};

#endif
