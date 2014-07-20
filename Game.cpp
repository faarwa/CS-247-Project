#include "Game.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <typeinfo>

// default constructor initializes players, the cards played, the seed for the game
Game::Game() {
	for (int i = 1; i <= 4; i++) {
		_players.push_back(new Player(i));
	}
	Player::initializeCardsPlayed();

	isGameOver_ = false;
	isRoundOver_ = false;
	_seed = 0;
}

// mutator for the players of the game
void Game::setPlayers(vector<Player*> players){
	_players = players;
}

// mutator for the seed for the shuffle
void Game::setSeed(int s) {
	_seed = s;
}

// Shuffle the deck using deck's shuffle method and deal the cards to players
void Game::shuffleAndDeal() {
	srand48(_seed);
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
	isRoundOver_ = false;
	isGameOver_ = false;
	isRoundOver_ = false;
	shuffleAndDeal();
	// Iterate through vector of players to find who has the 7 of spades; this player is set as current and goes first
	for (int i = 0; i < _players.size(); i++) {
		if (_players.at(i)->cards()->has7S()) {
			_currentPlayer = i+1;
			break;
		}
	}

	play();
}

// play method that handles everything during game play
void Game::play() {
	notify();
	// if the player is a computer player, automatically play or discard
	if (!_players.at(_currentPlayer-1)->canRage()) {
		playOrDiscard(new Card(NOSUIT, NORANK));
	}
}

// rage quit method for human players
void Game::ragequit() {
	// Construct a new computer player using the copy constructor with the human player's info and execute turn 
	Player *newPlayer = new ComputerPlayer(*_players.at(_currentPlayer-1));
	_players.at(_currentPlayer-1) = newPlayer;	
	playOrDiscard(new Card(NOSUIT, NORANK));
	notify();
}

// finish game by calculating score and starting a new round if no one has 80 points
void Game::finishGame() {
	cout << endl;
	isGameOver_ = false;
	int lowestScorePlayer = 1; // keep track of who has the lowest score (winner)
	int lowestScore = _players.at(0)->score()+_players.at(0)->gameScore(); // keep track of what the lowest score is

	// Iterate through players and print their vector of discards
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		vector<Card*> discards = (*it)->discardedCards();

		// if any of the players has a score of greater than or equal to 80, then the game will be over
		if ((*it)->score() >= 80) {
			isGameOver_ = true;
		}

		// check for lowest score/winning player
		if ((*it)->score() < lowestScore) {
			lowestScorePlayer = (*it)->playerNumber();
			lowestScore = (*it)->score();
		}

		(*it)->setDiscards(0);
	}

	// if the game isnt over yet, start a new round, otherwise output the winner and finish
	if (!isGameOver_) {
		start();
	} else {
		// set the winning player and update the view
		winningPlayer_ = lowestScorePlayer;
		notify();
		isGameOver_ = false;
	}
}

// accessor for the hand of the current player
vector<Card*> Game::getHand(){
	return _players.at(_currentPlayer-1)->cards()->hand();
}

// play or discard method
void Game::playOrDiscard(Card *card){
	// checks if the card the player chose is a legal play
	if(_players.at(_currentPlayer-1)->canPlay(card)){
		// plays the card and updates the view
		_players.at(_currentPlayer-1)->play(*card);
		notify();
	}
	else {
		// discards and updates the view
		_players.at(_currentPlayer-1)->discard(*card);
		notify();
	}
	
	// increments players
	if (_currentPlayer == 4) {
		_currentPlayer = 1;
	} else {
		_currentPlayer++;
	}

	notify();

	int sumCards = 0;
	isRoundOver_ = false;

	map<Suit, vector<Card*>* > cards = Player::playedCards();

	// Get the number of cards that have been played and add to sum
	for (map<Suit, vector<Card*>* >::iterator it = cards.begin(); it != cards.end(); it++) {
		sumCards += (*it).second->size();
	}

	// Get the number of cards that have been discarded and add to sum
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++) {
		sumCards += (*it)->discardedCards().size();
	}

	// checks if all of the cards have been played, ends the round if they have
	if (sumCards >= 52) {
		isRoundOver_ = true;
	}

	// automatically call play for a computer player
	while (!_players.at(_currentPlayer-1)->canRage() && !isRoundOver_) {
		_players.at(_currentPlayer-1)->play(*card);
		if (_currentPlayer == 4) {
			_currentPlayer = 1;
		} else {
			_currentPlayer++;
		}
		notify();
		sumCards++;
		if (sumCards >= 52) {
			isRoundOver_ = true;
		}
	}

	// resets and updates the view if a round ends
	if (isRoundOver_) {
		resetCards();
		isRoundOver_ = false;
		finishGame();
		notify();
	}
}

// resets the cards in the players hand and the table cards
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

// ends the current game, resets the player hands
void Game::endCurrentGame() {
	resetCards();
	for (int i = 0; i < _players.size(); i++) {
		_players.at(i)->resetHand();
	}
}

// accessor for the current player
Player* Game::getCurrentPlayer(){
	return _players.at(_currentPlayer-1);
}

// accesorr for if the game is over
bool Game::isGameOver(){
	return isGameOver_;
}

// accessor for if the round is over
bool Game::isRoundOver(){
	return isRoundOver_;
}

// accessor for the number of the winning player
int Game::getWinningPlayer(){
	return winningPlayer_;
}
