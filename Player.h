#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <map>

#include "Card.h"
#include "CardHand.h"
#include "Command.h"

using namespace std;

class Player {
public:
	Player(int playerNumber);
	Player(Player &player);
	~Player();
	void setCards(vector<Card*> cards) { _cards = CardHand(cards); }
	void addCardToHand(const Card card) const;
	void newHand();
	virtual void print() const {}
	virtual void play(Card card) {}
	virtual Command doTurn() { return Command(); }
	virtual void discard(Card card) {};
	CardHand cards() const { return _cards; }
	vector<Card*> discardedCards() { return _discardedCards; }
	int playerNumber() { return _playerNumber; }
	int gameScore();
	int score() { return _score; }
	void incrementScore(int score) { _score += score; }
	void printDiscards();
	static map<Suit, vector<Card*> > playedCards() { return Player::cardsPlayed; }
protected:
	CardHand _cards;
	int _playerNumber;
	vector<Card*> _discardedCards;
	vector<Card*> getLegalPlays() const;
	static map<Suit, vector<Card*> > cardsPlayed;
	int _score;
};

void printCardList(vector<Card> list);

#endif