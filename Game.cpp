#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

Game::Game() {
	deck.shuffle();

	for (int i = 1; i <= 4; i++) {
		string playerType;
		cout << "Is player " << i << " a human(h) or a computer(c)?" << endl;
		cin >> playerType;

		if (playerType == "h") {
			vector<Card*> cards;
			for(int j=i;j<i+13;j++){
				cards.push_back(deck.cards().at(j));
			}
			Player player = HumanPlayer(cards);
			_players.push_back(player);
		} else if (playerType == "c") {
			vector<Card*> cards;
			for(int j=i;j<i+13;j++){
				cards.push_back(deck.cards().at(j));
			}
			Player player = ComputerPlayer(cards);
			_players.push_back(player);
		}
	}
}

void Game::start() const {
	cout << "A new round begins. It's player ";
	for (int i = 0; i < _players.size(); i++) {
		if (_players.at(i).cards().has7S()) {
			cout << i << endl;
			break;
		}
	}

	cout << "'s turn to play." << endl;
}