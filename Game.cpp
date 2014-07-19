#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "Command.h"
#include <typeinfo>

// default constructor
Game::Game() {
	for (int i = 1; i <= 4; i++) {
		_players.push_back(new Player(i));
	}
	Player::initializeCardsPlayed();
	_seed = 0;
}

void Game::setPlayers(vector<Player*> players){
	_players = players;
}

void Game::setSeed(int s) {
	_seed = s;
}

void Game::newRound() {
	shuffleAndDeal();
	// Iterate through vector of players to find who has the 7 of spades; this player is set as current and goes first
	for (int i = 0; i < _players.size(); i++) {
		if (_players.at(i)->cards()->has7S()) {
			_currentPlayer = i+1;
			break;
		}
	}

	cout << "A new round begins. It's player " << _currentPlayer << "'s turn to play." << endl;
	play();
}

// Shuffle the deck using deck's shuffle method and deal the cards to players
void Game::shuffleAndDeal() {
	_deck.shuffle();	
	int cardIndex = 0;
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		(*it)->newHand();
		vector<Card*> cards;
		for (int j = cardIndex; j < cardIndex+13; j++) {
			cards.push_back(_deck.cards().at(j));
		}
		(*it)->setCards(cards);
		cardIndex += 13;
	}
}

// Start the game by shuffling the deck and dealing
void Game::start() {
	srand(_seed);
	newRound();
}

// play method that handles everything during game play
void Game::play() {
	notify();
	if (!_players.at(_currentPlayer-1)->canRage()) {
		playOrDiscard(new Card(NOSUIT, NORANK));
	}
}

// rage quit method for human players
void Game::ragequit() {
	cout << "Player " << _currentPlayer << " ragequits.  A computer will now take over." << endl;
	// Construct a new computer player using the copy constructor with the human player's info and execute turn 
	Player *newPlayer = new ComputerPlayer(*_players.at(_currentPlayer-1));
	_players.at(_currentPlayer-1) = newPlayer;	
	playOrDiscard(new Card(NOSUIT, NORANK));
	notify();
}

// finish game by calculating score and starting a new round if no one has 80 points
void Game::finishGame() {
	cout << endl;
	bool gameOver = false;
	int lowestScorePlayer = 1; // keep track of who has the lowest score (winner)
	int lowestScore = _players.at(0)->score()+_players.at(0)->gameScore(); // keep track of what the lowest score is

	// Iterate through players and print their vector of discards
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		cout << "Player " << (*it)->playerNumber() << "'s discards: ";
		vector<Card*> discards = (*it)->discardedCards();
		// Calculate score and output it
		cout << "Player " << (*it)->playerNumber() << "'s score: ";
		cout << (*it)->score() << " + " << (*it)->gameScore() << " = ";

		// Increment the score for the player
		// (*it)->incrementScore((*it)->gameScore());
		cout << (*it)->score() << endl;
		cout << endl;

		// if any of the players has a score of greater than or equal to 80, then the game will be over
		if ((*it)->score() >= 80) {
			gameOver = true;
		}

		// check for lowest score/winning player
		if ((*it)->score() < lowestScore) {
			lowestScorePlayer = (*it)->playerNumber();
			lowestScore = (*it)->score();
		}

		(*it)->setDiscards(0);
	}

	// if the game isnt over yet, start a new round, otherwise output the winner and finish
	if (!gameOver) {
		newRound();
	} else {
		cout << "Player " << lowestScorePlayer << " wins!" << endl;
	}
}

vector<Card*> Game::getHand(){
	return _players.at(_currentPlayer-1)->cards()->hand();
}

void Game::playOrDiscard(Card *card){
	if(_players.at(_currentPlayer-1)->canPlay(card)){
		_players.at(_currentPlayer-1)->play(*card);
		notify();
	}
	else {
		_players.at(_currentPlayer-1)->discard(*card);
		notify();
	}

	if (_currentPlayer == 4) {
		_currentPlayer = 1;
	} else {
		_currentPlayer++;
	}

	notify();

	int sumCards = 0;
	bool roundOver = false;

	map<Suit, vector<Card*>* > cards = Player::playedCards();

	// Get the number of cards that have been played and add to sum
	for (map<Suit, vector<Card*>* >::iterator it = cards.begin(); it != cards.end(); it++) {
		sumCards += (*it).second->size();
	}

	// Get the number of cards that have been discarded and add to sum
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		sumCards += (*it)->discardedCards().size();
	}

	if (sumCards >= 52) {
		roundOver = true;
	}

	while (!_players.at(_currentPlayer-1)->canRage() && !roundOver) {
		notify();
		_players.at(_currentPlayer-1)->play(*card);
		if (_currentPlayer == 4) {
			_currentPlayer = 1;
		} else {
			_currentPlayer++;
		}
		notify();
		sumCards++;
		if (sumCards >= 52) {
			roundOver = true;
		}
	}

	notify();

	if (roundOver) {
		resetCards();
		finishGame();
		notify();
	}
}

void Game::resetCards() {
	for (int i = 0; i < 4; i++) {
		if (Player::playedCards().at((Suit)i)) {
			Player::playedCards().at((Suit)i)->clear();
		}
	}

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		(*it)->clearHand();
	}

	notify();
}

void Game::endCurrentGame() {
	resetCards();
	for (int i = 0; i < _players.size(); i++) {
		_players.at(i)->resetHand();
	}
}

Player* Game::getCurrentPlayer(){
	return _players.at(_currentPlayer-1);
}
