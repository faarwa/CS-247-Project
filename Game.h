#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"

using namespace std;

// Game class with basic functionality for running the game (controller)
class Game {
public:
	Game();								// default constructor
	void start();						// start the game
	void play();						// plays the game
	void shuffleAndDeal();				// shuffle the deck and deal the cards to the player
	void finishGame();					// finish the game and calculate scores
	void turn();						// change the player's turn
	void ragequit();					// if a player ragequits
private:
	Deck _deck;							// private data member - deck for the game
	vector<Player*> _players;			// vector of all the players (abstract, can be human or computer)
	int _currentPlayer;					// int from 1-4 indicating which player is playing
};

#endif