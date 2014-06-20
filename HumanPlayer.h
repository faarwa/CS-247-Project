#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>
#include "Player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer(int playerNumber) : Player(playerNumber) {}
	void play(Card c);
	void print() const;
	void discard(Card c);
	Command doTurn();
	class IllegalPlayException {
	public:
		IllegalPlayException() {}
	};
	class IllegalDiscardException {
	public:
		IllegalDiscardException() {}
	};
private:
};

#endif