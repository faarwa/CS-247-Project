#include "CardHand.h"

Card *_cardPlayed;

// Helper method - checks whether a card is the 7 of spades
bool isCard7S(Card *c) {
	if (c->getSuit() == SPADE && c->getRank() == SEVEN) {
		return true;
	}

	return false;
}

// Constructs the card hand with a vector of Cards
CardHand::CardHand(vector<Card*> cards) {
	for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
		_cards.push_back(*it);
	}
}

CardHand::~CardHand() {
	_cards.clear();
}

// member function - returns whether the hand has the 7 of spades
bool CardHand::has7S() const {
	// search the vector using an iterator
	if (find_if(_cards.begin(), _cards.end(), isCard7S) == _cards.end()) {
		return false;
	}

	return true;
}

vector<Card*> CardHand::hand() {
	vector<Card*> c;
	for (vector<Card*>::iterator it = _cards.begin(); it != _cards.end(); it++) {
		c.push_back(*it);
	}
	return c;
}

// Unary predicate for find iterator ; checks whether two pointers to Cards are equal
bool cardIsEqual(Card *card) {
	if (card->getSuit() == _cardPlayed->getSuit() && card->getRank() == _cardPlayed->getRank()) {
		return true;
	}

	return false;
}

// member function - searches hand for a card to remove and deletes it from the vector
void CardHand::removeCard (Card *card) {
	_cardPlayed = card;
	vector<Card*>::iterator deleteIt = find_if(_cards.begin(), _cards.end(), cardIsEqual);
	_cards.erase(deleteIt);
}

// member function - returns vector of legal plays that the hand has based on what's played
vector<Card*> CardHand::legalPlays(map<Suit, vector<Card*>* > cardsPlayed) const {
	vector<Card*> legalPlays;

	// If there are no spades on the board, the first player must play a 7S (this is for the first player)
	// That's the only legal play so return immediately
	if (cardsPlayed.at(SPADE)->empty()) {
		legalPlays.push_back(new Card(SPADE, SEVEN));
		return legalPlays;
	}

	vector<Card*> cards = _cards;

	// Iterate through the card hand:
	// If the rank of a card in the hand is one less or greater than that played for the same suit, it's a legal play
	for (vector<Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
		Card *card = (*it);
		vector<Card*> *suitCards = cardsPlayed.at(card->getSuit());
		if (!suitCards->empty() && (card->getRank()+1 == suitCards->at(0)->getRank() || card->getRank() == suitCards->at(suitCards->size()-1)->getRank()+1)) {
			legalPlays.push_back(card);
			continue;
		}

		// Sevens are always legal plays since they must be played first for a suit
		if (card->getRank() == SEVEN) {
			legalPlays.push_back(card);
			continue;
		}
	}

	return legalPlays;
}

void CardHand::print() {
	for (vector<Card*>::iterator it = _cards.begin(); it != _cards.end(); it++) {
		cout << "Card " << **it << endl;
	}
}