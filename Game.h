#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Deck.h"

using namespace std;

class Game {
public:
	Game();
	void start();
	void play(Card *card);
	Deck deck;

private:
	vector<Player*> _players;
	int _currentPlayer;
};

#endif