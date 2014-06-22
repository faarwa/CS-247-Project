#ifndef CARDHAND_H
#define CARDHAND_H

#include <iostream>
#include <vector>
#include "Card.h"
#include <map>

using namespace std;

class CardHand {
public:
	CardHand() {};									// default constructor for an empty hand
	CardHand(vector<Card*> cards);					// constructor with an array of cards
	void addCard(const Card card);					// method to add card to hand
	bool has7S() const;								// checks whether the hand has the 7 of spades
	vector<Card*> hand() const { return _cards; }	// accessor for vector of cards
	void removeCard(Card *card);					// method to remove a card from the hand

	// returns a list of legal plays from the hand given all the cards that have been played
	vector<Card*> legalPlays(map<Suit, vector<Card*> >) const;		
private:
	vector<Card*> _cards;							// private data member - vector of Cards
};

#endif