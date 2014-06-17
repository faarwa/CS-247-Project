#include "Player.h"

map<Suit, vector<Card*> > Player::cardsPlayed;

Player::Player(vector<Card*> cards, int playerNumber) {
	_cards = CardHand(cards);
	vector<Card*> suitCards;
	cardsPlayed[SPADE] = suitCards;
	cardsPlayed[CLUB] = suitCards;
	cardsPlayed[HEART] = suitCards;
	cardsPlayed[DIAMOND] = suitCards;
	_playerNumber = playerNumber;
}

Player::~Player() {
	for (map<Suit, vector<Card*> >::iterator it = cardsPlayed.begin(); it != cardsPlayed.end(); it++) {
		vector<Card*> suitCards = (*it).second;
		for (vector<Card*>::iterator it2 = suitCards.begin(); it2 != suitCards.end(); it2++) {
			delete (*it2);
		}
	}
}

vector<Card*> Player::getLegalPlays() const {
	vector<Card*> legalPlays;

	if (cardsPlayed.at(SPADE).empty()) {
		legalPlays.push_back(new Card(SPADE, SEVEN));
		return legalPlays;
	}

	for (vector<Card*>::iterator it = _cards.hand().begin(); it != _cards.hand().end(); it++) {
		Card *card = (*it);
		vector<Card*> suitCards = cardsPlayed.at(card->getSuit());
		if (card->getRank()+1 == suitCards.at(0)->getRank() || card->getRank() == suitCards.at(suitCards.size()-1)->getRank()+1) {
			legalPlays.push_back(card);
			continue;
		}

		if (card->getRank() == SEVEN) {
			legalPlays.push_back(card);
			continue;
		}
	}

	return legalPlays;
}

void Player::discard(Card *card){
	vector<Card*> playerHand = cards().hand();
	for(int i=0;i<playerHand.size();i++){
		if(playerHand.at(i) == card){
			_discardedCards.push_back(card);
			_cards.removeCard(_cards.hand().begin()+i);
			break;
		}
	}
}