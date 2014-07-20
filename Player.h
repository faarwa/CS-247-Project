#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <map>

#include "Card.h"
#include "CardHand.h"
#include "subject.h"

using namespace std;

// Player class
class Player: public Subject {
public:
	Player(int playerNumber); 													// constructs a player with a number													
	Player(Player &player);														// copy constructor that constructs a player with another player
	~Player(); 															// destructor
	void setCards(vector<Card*> cards); 												// method that sets the hand of the player
	void addCardToHand(const Card card) const; 											// method that adds a card to the player's hand
	void newHand(); 														// method that clears the player's hand and discarded pile - for when a new game begins
	virtual void print() const {} 													// method to be overidden to print lines for human player
	virtual void play(Card card) {} 												// method to be overidden for a player to play
	virtual void discard(Card card);												// method to be overidden for a player to discard a card
	CardHand* cards() const { return _cards; } 											// accessor for the player's hand
	vector<Card*> discardedCards() { return _discardedCards; } 									// accessor for they player's discarded cards
	int playerNumber() { return _playerNumber; } 											// accessor for the player's number
	int gameScore(); 														// method that calculates the player's score based on discarded cards
	int score() { return _score; } 													// accessor for the player's current score
	void printDiscards(); 														// method to print a list of discarded cards
	int discards() { return _discards; }												// accessor for num discards for the round
	void setDiscards(int discards) {_discards = discards; }										// mutator for the discarded cards
	static map<Suit, vector<Card*>* > playedCards() { return Player::cardsPlayed; }  						// accessor for the static map of all cards played in the game
	bool canRage() { return _canRage; }												// accessor for canRage boolean
	virtual bool canPlay(Card *card){ return true; }										// virtual method that checks if a played card is a legal play
	static void initializeCardsPlayed();												// member function that initializes the cards played as empty vectors
	void clearHand();														// clears the player's hand
	void resetHand() { delete _cards; }												// delete's the player's hand
	void insertCardOnBoard(Card *card);												// inserts a card to be on the table (adds it properly to the map of cards played)
protected:
	bool _canRage;															// protected data member - indicates whether player can ragequit (is comp or human)
	CardHand *_cards;														// protected data member - the hand of the player
	int _playerNumber;														// protected data member - the player's number (1-4)
	vector<Card*> _discardedCards;													// protected data member - a vector of cards that the player has discarded
	vector<Card*> getLegalPlays() const;												// protected method to get list of legal plays based on the static map of all cards played and the player's hand
	static map<Suit, vector<Card*>* > cardsPlayed;											// protected static map of all cards played in the game
	int _score;															// protected data member - current score of the player
	int _discards;															// protected data member - number of discards for the round
};

void printCardList(vector<Card> list);													// non-member function - prints cards given a list of cards

#endif
