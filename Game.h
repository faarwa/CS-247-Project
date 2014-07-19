#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"

using namespace std;

// Game class with basic functionality for running the game (controller)
class Game : public Subject {
public:
	Game();								// default constructor
	void setPlayers(vector<Player*> players);
	void start();						// start the game
	void play();						// plays the game
	void shuffleAndDeal();				// shuffle the deck and deal the cards to the player
	void finishGame();					// finish the game and calculate scores
	void turn();						// change the player's turn
	void ragequit();					// if a player ragequits
	vector<Card*> getHand();										// if a player ragequits
	vector<Player*> players() { return _players; }			// accessor - returns vector of players
	void playOrDiscard(Card *card);
	Player* getCurrentPlayer();
	int currentPlayer() { return _currentPlayer; }
	void resetCards();
	void setSeed(int s);
	void endCurrentGame();
private:
	int _seed;
	Deck _deck;							// private data member - deck for the game
	vector<Player*> _players;			// vector of all the players (abstract, can be human or computer)
	int _currentPlayer;					// int from 1-4 indicating which player is playing
};

#endif
