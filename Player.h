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
	Player(vector<Card*> cards);
	~Player();
	void addCardToHand(const Card card) const;
	virtual void print() const {};
	virtual Card* play(Card *card) { return card; };
	virtual void discard(Card *card) const {};
	CardHand cards() const { return _cards; }
	vector<Card*> discardedCards() { return _discardedCards; }
protected:
	CardHand _cards;
	vector<Card*> _discardedCards;
	vector<Card*> getLegalPlays() const;
	static map<Suit, vector<Card*> > cardsPlayed;
};

void printCardList(vector<Card> list);

#endif