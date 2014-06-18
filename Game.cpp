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
	play();
}

void Game::play() {
	while(true){
		int sumCards = 0;

		map<Suit, vector<Card*> > cards = Player::playedCards();

		for (map<Suit, vector<Card*> >::iterator it = cards.begin(); it != cards.end(); it++) {
			// cout << "SUIT " << (*it).first << endl;
			sumCards += (*it).second.size();
		}

		for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
			// cout << "PLAYER " << (*it)->playerNumber() << endl;
			sumCards += (*it)->discardedCards().size();
		}

		// cout << "SUM " << sumCards << endl;

		if (sumCards < 52) {
			_players.at(_currentPlayer-1)->print();
			_players.at(_currentPlayer-1)->doTurn();
			if (_currentPlayer == 4) {
				_currentPlayer = 1;
			} else {
				_currentPlayer++;
			}
		} else {
			break;
		}
	}
	finishGame();
}

void Game::finishGame() {

}