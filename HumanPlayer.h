#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "Player.h"

//Subclass of Player
class HumanPlayer : public Player {
public:
	HumanPlayer(int playerNumber) : Player(playerNumber) { _canRage = true; } 		//Constructor that constructs a human player with a player number
	void discard(Card c); 									// Overridden method to discard a card
	bool canPlay(Card *card);								// Boolean method to check if a card is a legal play

	class IllegalPlayException {								// Exception class to handle human player making illegal plays
	public:
		IllegalPlayException() {}
	};
	class IllegalDiscardException {								//Exception class to handle human player making illegal discards
	public:
		IllegalDiscardException() {}
	};
};

#endif
