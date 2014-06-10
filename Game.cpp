#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

Game::Game() {
	for (int i = 1; i <= 4; i++) {
		string playerType;
		cout << "Is player " << i << " a human(h) or a computer(c)?" << endl;
		cin >> playerType;

		if (playerType == "h") {
			//HumanPlayer player = HumanPlayer();
			//_players.push_back(player);
		} else if (playerType == "c") {
			// ComputerPlayer player = ComputerPlayer();
			// _players.push_back(player);
		}
	}
}