#include "Player.h"

map<Suit, vector<Card*> > Player::cardsPlayed;

Player::Player(int playerNumber) {
	vector<Card*> suitCards;
	cardsPlayed[SPADE] = suitCards;
	cardsPlayed[CLUB] = suitCards;
	cardsPlayed[HEART] = suitCards;
	cardsPlayed[DIAMOND] = suitCards;
	_playerNumber = playerNumber;
	_score = 0;
}

Player::Player(Player &player) {
	_playerNumber = player.playerNumber();
	_cards = player.cards();
	_discardedCards = player.discardedCards();
	_score = player.score();
}

Player::~Player() {
	for (map<Suit, vector<Card*> >::iterator it = cardsPlayed.begin(); it != cardsPlayed.end(); it++) {
		vector<Card*> suitCards = (*it).second;
		for (vector<Card*>::iterator it2 = suitCards.begin(); it2 != suitCards.end(); it2++) {
			delete (*it2);
		}
	}
}

void Player::newHand() {
	_discardedCards.clear();
	_cards.hand().clear();
}

vector<Card*> Player::getLegalPlays() const {
	vector<Card*> legalPlays;

	return _cards.legalPlays(cardsPlayed);
}

int Player::gameScore(){
	int score = 0;
	for (int i = 0; i < _discardedCards.size(); i++) {
		score += _discardedCards.at(i)->getRank()+1;
	}

	return score;
}