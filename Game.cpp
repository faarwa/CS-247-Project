#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <typeinfo>

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
			Player *player = new HumanPlayer(cards, i+1);
			_players.push_back(player);
		} else if (playerType == "c") {
			vector<Card*> cards;
			for (int j = cardIndex; j < cardIndex+13; j++){
				cards.push_back(deck.cards().at(j));
			}
			Player *player = new ComputerPlayer(cards, i+1);
			_players.push_back(player);
		}

		cardIndex += 13;
	}
}

void Game::start() {
	for (int i = 0; i < _players.size(); i++) {
		if (_players.at(i)->cards().has7S()) {
			_currentPlayer = i+1;
			break;
		}
	}

	cout << "A new round begins. It's player " << _currentPlayer << "'s turn to play." << endl;
	_players.at(_currentPlayer-1)->print();
	play(NULL);
}

void Game::play(Card *card) {
	bool isLegalPlay = true;

	if (card) {
		do {
			try {
				_players.at(_currentPlayer-1)->play(card);
			} catch (Player::IllegalPlayException &e) {
				isLegalPlay = false;
				cout << "This is not a legal play." << endl;
				cin >> *card;	
			}
		} while (!isLegalPlay);
	} else {
		_players.at(_currentPlayer-1)->play(NULL);
	}

	if (isLegalPlay) {

		cout << "Player " << _currentPlayer << + " plays " << *card << "." << endl;
		if (_currentPlayer == 4) {
			_currentPlayer = 1;
		} else {
			_currentPlayer++;
			// _players.at(_currentPlayer-1)->print();
		}
	}
}

void Game::finishGame() {

}