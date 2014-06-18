#include "HumanPlayer.h"

Card* _cardPlayed;

void printCardsRank(vector<Card*> *list) {

	for (vector<Card*>::iterator it = list->begin(); it != list->end(); it++) {
		if (it != list->begin()) {
			cout << " ";
		}
		cout << (*it)->getRank()+1;
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

bool cardIsEqual(Card *card) {
	if (card->getSuit() == _cardPlayed->getSuit() && card->getRank() == _cardPlayed->getRank()) {
		return true;
	}

	return false;
}

void HumanPlayer::play(Card *card) {

	if (!card) {
		return;
	}

	vector<Card*> legalPlays = getLegalPlays();
	_cardPlayed = card;

	if (find_if(legalPlays.begin(), legalPlays.end(), cardIsEqual) == legalPlays.end()) {
		throw Player::IllegalPlayException();
	}

	vector<Card*>::iterator deleteIt = find_if(_cards.hand().begin(), _cards.hand().end(), cardIsEqual);

	cardsPlayed.at(card->getSuit()).push_back(card);

	_cards.hand().erase(deleteIt);
}

Command HumanPlayer::doTurn() {
	// while (!cin.eof()) {
		Command cmd = Command();
		cout << "Enter command:";
		cin >> cmd;

		if (cmd.type == DECK) {
			// game->deck.print();
		} else if (cmd.type == QUIT) {
			exit(0);
		} else if (cmd.type == PLAY) {
			play(&cmd.card);
		}

		return cmd;
	// }
}

void HumanPlayer::print() const {

	cout << "Cards on the table:" << endl;
	cout << "Clubs: ";
	printCardsRank(&cardsPlayed.at(CLUB));
	cout << endl;
	cout << "Diamonds: ";
	printCardsRank(&cardsPlayed.at(DIAMOND));
	cout << endl;
	cout << "Hearts: ";
	printCardsRank(&cardsPlayed.at(HEART));
	cout << endl;
	cout << "Spades: " << cardsPlayed.at(SPADE).size() << " ";
	printCardsRank(&cardsPlayed.at(SPADE));
	cout << endl;

	cout << "Your hand: ";
	printCards(_cards.hand());
	cout << endl;	

	cout << "Legal plays: ";
	printCards(getLegalPlays());
	cout << endl;
}

