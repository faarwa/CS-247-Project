#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"

using namespace std;

class Game {
public:
	Game();
	void play();
	void start();
	Deck deck;
	void finishGame();
	void turn();
	void ragequit();
private:
	vector<Player*> _players;
	int _currentPlayer;
};

#endif