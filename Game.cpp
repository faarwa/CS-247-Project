#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Command.h"
#include <typeinfo>

Game::Game() {
	for (int i = 0; i < 4; i++) {
		string playerType;
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl;
		cin >> playerType;

		if (playerType == "h") {
			Player *player = new HumanPlayer(i+1);
			_players.push_back(player);
		} else if (playerType == "c") {
			Player *player = new ComputerPlayer(i+1);
			_players.push_back(player);
		}
	}
}

void Game::shuffleAndDeal() {
	deck.shuffle();
	int cardIndex = 0;
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		(*it)->newHand();
		vector<Card*> cards;
		for (int j = cardIndex; j < cardIndex+13; j++) {
			cards.push_back(deck.cards().at(j));
		}
		(*it)->setCards(cards);
		cardIndex += 13;
	}
}

void Game::start() {
	shuffleAndDeal();

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
			Command command = _players.at(_currentPlayer-1)->doTurn();
			if(command.type == RAGEQUIT){
				ragequit();
			}
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

void Game::ragequit(){
	cout << "Player " << _currentPlayer << " ragequits.  A computer will now take over.";
	Player *newPlayer = new ComputerPlayer(_currentPlayer);
	newPlayer->setCards(_players.at(_currentPlayer-1)->cards().hand());
	_players.at(_currentPlayer-1) = newPlayer;
}

void Game::finishGame() {
	cout << endl;
	bool gameOver = false;
	int lowestScorePlayer = 1;
	int lowestScore = _players.at(0)->score()+_players.at(0)->gameScore();
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		cout << "Player " << (*it)->playerNumber() << "'s discards: ";
		vector<Card*> discards = (*it)->discardedCards();
		for (vector<Card*>::iterator it = discards.begin(); it != discards.end(); it++) {
			if (it != discards.begin()) {
				cout << " ";
			}
			cout << *(*it);
		}
		cout << endl;
		cout << "Player " << (*it)->playerNumber() << "'s score: ";
		cout << (*it)->score() << " + " << (*it)->gameScore() << " = ";
		(*it)->incrementScore((*it)->gameScore());
		cout << (*it)->score() << endl;
		cout << endl;

		if ((*it)->score() >= 80) {
			gameOver = true;
		}

		if ((*it)->score() < lowestScore) {
			lowestScorePlayer = (*it)->playerNumber();
			lowestScore = (*it)->score();
		}
	}

	if (!gameOver) {
		start();
	} else {
		cout << "Player " << lowestScorePlayer << " wins!" << endl;
	}
}