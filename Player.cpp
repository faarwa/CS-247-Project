#include "Player.h"

// static map of all cards played in the game
map<Suit, vector<Card*>* > Player::cardsPlayed;

// initializes cards played to empty vectors
void Player::initializeCardsPlayed() {
	cardsPlayed[HEART] = new vector<Card*>();
	cardsPlayed[SPADE] = new vector<Card*>();
	cardsPlayed[CLUB] = new vector<Card*>();
	cardsPlayed[DIAMOND] = new vector<Card*>();
}

// member function - constructor that constructs a player with a number, intializes their score to zero, and their cards played to empty vectors
Player::Player(int playerNumber) {
	_playerNumber = playerNumber;
	_score = 0;
	_discards = 0;
	_cards = new CardHand();
}

// player discard method, calls notify to update the View that a card was discarded
void Player::discard(Card card) {
	notify();
}

// sets the cards of the player's hand
void Player::setCards(vector<Card*> cards) {
	_cards = new CardHand(cards);
}

// clears the players hand
void Player::clearHand() {
	_cards->clearCards();
}

void Player::insertCardOnBoard(Card* card) {
	//inserts the played card into the proper spot for the static map used to keep track of all the cards played
	if (!cardsPlayed.at(card->getSuit())->empty() && cardsPlayed.at(card->getSuit())->at(0)->getRank() > card->getRank()) {
		//puts the played card in the front of the vector if it is less than the current lowest card played of that suit
		cardsPlayed.at(card->getSuit())->insert(cardsPlayed.at(card->getSuit())->begin(), card);
	} else {
		//otherwise, puts the played card at the back of the vector
		cardsPlayed.at(card->getSuit())->push_back(card);
	}

}

// member function - copy constructor that constructs a new player, given a player
Player::Player(Player &player) {
	_playerNumber = player.playerNumber();
	setCards(player.cards()->hand());
	_discardedCards = player.discardedCards();
	_score = player.score();
	_discards = player.discards();
}

// member function - destructor
Player::~Player() {
	// deletes all Card* from the cardsPlayed map
	for (map<Suit, vector<Card*>* >::iterator it = cardsPlayed.begin(); it != cardsPlayed.end(); it++) {
		vector<Card*>* suitCards = (*it).second;
		for (vector<Card*>::iterator it2 = suitCards->begin(); it2 != suitCards->end(); it2++) {
			delete (*it2);
		}
	}
}

// member function - clears the hand and discarded cards of a player (for a new round)
void Player::newHand() {
	_discardedCards.clear();
}

// member function - returns the legal plays for a player's turn based on their hand and the map of cardsPlayed
vector<Card*> Player::getLegalPlays() const {
	vector<Card*> legalPlays;

	return _cards->legalPlays(cardsPlayed);
}

// member function - calculates the score based on the cards in the player's discarded cards
int Player::gameScore(){
	int score = 0;
	for (int i = 0; i < _discardedCards.size(); i++) {
		score += _discardedCards.at(i)->getRank()+1;
	}

	return score;
}
