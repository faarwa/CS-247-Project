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
	// printCardsRank(_clubs);
	// cout << endl;
	// cout << "Diamonds: ";
	// printCardsRank(_diamonds);
	// cout << endl;
	// cout << "Hearts: ";
	// printCardsRank(_hearts);
	// cout << endl;
	// cout << "Spades: ";
	// printCardsRank(_spades);
	// cout << endl;

	// cout << "Your hand: ";
	// printCards(_cards.hand());
	// cout << endl;

	// cout << "Legal plays: ";
	// printCards(getLegalPlays());
	// cout << endl;
}

void HumanPlayer::discard(Card *card) const {

}

vector<Card*> HumanPlayer::getLegalPlays() const {
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



	}


	// cout << *HumanPlayer::topCard << endl;

	// for (vector<Card*>::iterator it = _cards.hand().begin(); it != _cards.hand().end(); it++) {
	// 	if (isLegalPlay(*it)) {
	// 		legalPlays.push_back(*it);
	// 	}
	// }

	return legalPlays;
}

bool isLegalPlay(Card *card) {
	// if (HumanPlayer::topCard->getRank() == (card)->getRank()) {
	// 	return true;
	// } 

	// if (HumanPlayer::topCard->getSuit() == (card)->getSuit() && HumanPlayer::topCard->getRank()+1 == (card)->getRank()) {
	// 	return true;
	// }

	// if (HumanPlayer::topCard->getSuit() == (card)->getSuit() && HumanPlayer::topCard->getRank()-1 == (card)->getRank()) {
	// 	return true;
	// }

	return false;
}
