#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"

using namespace std;

class Game {
public:
	Game();

private:
	vector<Player> _players;
};

#endif