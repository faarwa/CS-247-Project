#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

Game::Game() {
	for (int i = 1; i <= 4; i++) {
		string playerType;
		cout << "Is player " << i << " a human(h) or a computer(c)?" << endl;
		cin >> playerType;

		if (playerType == "h") {
			vector<Card> cards;
			Player player = HumanPlayer(cards);
			_players.push_back(player);
		} else if (playerType == "c") {
			vector<Card> cards;
			Player player = ComputerPlayer(cards);
			_players.push_back(player);
		}
	}
}