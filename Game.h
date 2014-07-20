#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"

using namespace std;

// Game class with basic functionality for running the game (model)
class Game : public Subject {
public:
	Game();							// default constructor								
	void setPlayers(vector<Player*> players);		// mutator for the players of the game 

	void start();						// start the game
	void shuffleAndDeal();					// shuffle the deck and deal the cards to the player
	void play();						// plays the game
	void finishGame();					// finish the game and calculate scores
	void ragequit();					// if a player ragequits
	vector<Card*> getHand();				// accessor for the players' hands
	vector<Player*> players() { return _players; }		// accessor - returns vector of players
	void playOrDiscard(Card *card);				// main method of the game - gets called when user clicks on a card or on a computer player's turn
	Player* getCurrentPlayer();				// accessor for the current player
	int currentPlayer() { return _currentPlayer; }		// accessor for the number of the current player
	void resetCards();					// clears the cards on the board
	bool isGameOver();					// returns true if the game is over
	bool isRoundOver();					// returns true if the round is over
	int getWinningPlayer();					// accessor for the number of the winning player
	void setSeed(int s);					// mutator for the seed for shuffling
	void endCurrentGame();					// ends the current game
private:
	int _seed;						// private data member - seed for shuffling
	Deck _deck;						// private data member - deck for the game
	vector<Player*> _players;				// vector of all the players (abstract, can be human or computer)
	int _currentPlayer;					// int from 1-4 indicating which player is playing
	bool isGameOver_;					// boolean for if the game is over
	bool isRoundOver_;					// boolean for if the round is over
	int winningPlayer_;					// int from 1-4 indicating which player won
};

#endif
