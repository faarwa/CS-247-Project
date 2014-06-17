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
		cout << (*it)->getRank() << (*it)->getSuit();
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
	printCardsRank(_cards.hand());
	cout << endl;
}

void HumanPlayer::discard(Card *card) const {

}
