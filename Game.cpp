#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

Game::Game() {
	deck.shuffle();

	int cardIndex = 0;

	for (int i = 0; i < 4; i++) {
		string playerType;
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl;
		cin >> playerType;

		if (playerType == "h") {
			vector<Card*> cards;
			for (int j = cardIndex; j < cardIndex+13; j++){
				cards.push_back(deck.cards().at(j));
			}
			Player player = HumanPlayer(cards);
			_players.push_back(player);
		} else if (playerType == "c") {
			vector<Card*> cards;
			for (int j = cardIndex; j < cardIndex+13; j++){
				cards.push_back(deck.cards().at(j));
			}
			Player player = ComputerPlayer(cards);
			_players.push_back(player);
		}

		cardIndex += 13;
	}
}

void Game::start() {
	for (int i = 0; i < _players.size(); i++) {
		if (_players.at(i).cards().has7S()) {
			_currentPlayer = i+1;
			break;
		}
	}

	cout << "A new round begins. It's player " << _currentPlayer << "'s turn to play." << endl;
}