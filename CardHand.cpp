#include "CardHand.h"

Card *_cardPlayed;

CardHand::CardHand() {
}

CardHand::CardHand(const vector<Card*> cards) {
	_cards = cards;
}

bool isCard7S(Card *c) {
	if (c->getSuit() == SPADE && c->getRank() == SEVEN) {
		return true;
	}

	return false;
}

bool CardHand::has7S() const {

	if (find_if(_cards.begin(), _cards.end(), isCard7S) == _cards.end()) {
		return false;
	}

	return true;
}

bool cardIsEqual(Card *card) {
	if (card->getSuit() == _cardPlayed->getSuit() && card->getRank() == _cardPlayed->getRank()) {
		return true;
	}

	return false;
}

void CardHand::removeCard (Card *card) {
	_cardPlayed = card;
	vector<Card*>::iterator deleteIt = find_if(_cards.begin(), _cards.end(), cardIsEqual);
	_cards.erase(deleteIt);
}

vector<Card*> CardHand::legalPlays(map<Suit, vector<Card*> > cardsPlayed) const {
	vector<Card*> legalPlays;

	if (cardsPlayed.at(SPADE).empty()) {
		legalPlays.push_back(new Card(SPADE, SEVEN));
		return legalPlays;
	}

	vector<Card*> cards = _cards;

	for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
		Card *card = (*it);
		vector<Card*> suitCards = cardsPlayed.at(card->getSuit());
		if (!suitCards.empty() && (card->getRank()+1 == suitCards.at(0)->getRank() || card->getRank() == suitCards.at(suitCards.size()-1)->getRank()+1)) {
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