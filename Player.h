#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <map>

#include "Card.h"
#include "CardHand.h"

using namespace std;

class Player {
public:
	Player(vector<Card*> cards, int playerNumber);
	~Player();
	void addCardToHand(const Card card) const;
	virtual void print() const {}
	virtual void play(Card *card) {}
	// virtual void doTurn() {}
	void discard(Card *card);
	CardHand cards() const { return _cards; }
	vector<Card*> discardedCards() { return _discardedCards; }
	int playerNumber() { return _playerNumber; }
	int playerScore();
	class IllegalPlayException {
	public:
		IllegalPlayException() {}
	};
protected:
	CardHand _cards;
	int _playerNumber;
	vector<Card*> _discardedCards;
	vector<Card*> getLegalPlays() const;
	static map<Suit, vector<Card*> > cardsPlayed;
};

void printCardList(vector<Card> list);

#endif