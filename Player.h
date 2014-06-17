#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Card.h"
#include "CardHand.h"

using namespace std;

class Player {
public:
	Player(vector<Card*> cards);
	~Player();
	void addCardToHand(const Card card) const;
	virtual void print() const {};
	virtual void play(Card *card) const {};
	virtual void discard(Card *card) const {};
	CardHand cards() const { return _cards; }
protected:
	CardHand _cards;
	vector<Card*> _hearts;
	vector<Card*> _spades;
	vector<Card*> _diamonds;
	vector<Card*> _clubs;
	Card *_topCard;
};

void printCardList(vector<Card> list);

#endif