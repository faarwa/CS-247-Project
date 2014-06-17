#include "HumanPlayer.h"

bool isLegalPlay(Card *card);

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

void HumanPlayer::play(Card *card) {

	// vector<Card*> *cards = &HumanPlayer::cardsPlayed.at(card->getSuit());
	// _cards.hand().erase(remove_if(_cards.hand().begin(), _cards.hand().end(), HumanPlayer::isCardTopCard), _cards.hand().end());
}

void HumanPlayer::print() const {
	cout << "Cards on the table:" << endl;
	cout << "Clubs: ";
	printCardsRank(cardsPlayed.at(CLUB));
	cout << endl;
	cout << "Diamonds: ";
	printCardsRank(cardsPlayed.at(DIAMOND));
	cout << endl;
	cout << "Hearts: ";
	printCardsRank(cardsPlayed.at(HEART));
	cout << endl;
	cout << "Spades: ";
	printCardsRank(cardsPlayed.at(SPADE));
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