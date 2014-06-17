#include "HumanPlayer.h"

void printCardsRank(vector<Card*> list) {
	for (vector<Card*>::iterator it = list.begin(); it != list.end(); it++) {
		if (it != list.begin()) {
			cout << " ";
		}
		cout << (*it)->getRank();
	}
}

void printCards(vector<Card*> list) {
	for (vector<Card*>::iterator it = list.begin(); it != list.end(); it++) {
		if (it != list.begin()) {
			cout << " ";
		}
		cout << *(*it);
	}
}

void HumanPlayer::play(Card *card) const {


}

void HumanPlayer::print() const {
	cout << "Cards on the table:" << endl;
	cout << "Clubs: ";
	printCardsRank(_clubs);
	cout << endl;
	cout << "Diamonds: ";
	printCardsRank(_diamonds);
	cout << endl;
	cout << "Hearts: ";
	printCardsRank(_hearts);
	cout << endl;
	cout << "Spades: ";
	printCardsRank(_spades);
	cout << endl;

	cout << "Your hand: ";
	printCards(_cards.hand());
	cout << endl;

	cout << "Legal plays: ";
	printCards(getLegalPlays());
	cout << endl;
}

void HumanPlayer::discard(Card *card) const {

}

vector<Card*> HumanPlayer::getLegalPlays() const {
	vector<Card*> legalPlays;
	if (!_topCard) {
		legalPlays.push_back(new Card(SPADE, SEVEN));
		return legalPlays;
	}

	cout << *_topCard << endl;

	for (vector<Card*>::iterator it = _cards.hand().begin(); it != _cards.hand().end(); it++) {
		if (_topCard->getRank() == (*it)->getRank()) {
			legalPlays.push_back(*it);
			continue;
		} 

		if (_topCard->getSuit() == (*it)->getSuit() && _topCard->getRank()+1 == (*it)->getRank()) {
			legalPlays.push_back(*it);
		}

		if (_topCard->getSuit() == (*it)->getSuit() && _topCard->getRank()-1 == (*it)->getRank()) {
			legalPlays.push_back(*it);
		}
	}

	return legalPlays;
}
