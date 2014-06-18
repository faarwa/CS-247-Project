#include "HumanPlayer.h"

Card *_playedCard;

void printCardsRank(vector<Card*> list) {

	for (vector<Card*>::iterator it = list.begin(); it != list.end(); it++) {
		if (it != list.begin()) {
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

bool equalCards(Card *card) {
	if (card->getSuit() == _playedCard->getSuit() && card->getRank() == _playedCard->getRank()) {
		return true;
	}

	return false;
}

void HumanPlayer::play(Card c) {
	Card *card = new Card(c.getSuit(), c.getRank());
	if (!card) {
		return;
	}

	vector<Card*> legalPlays = getLegalPlays();
	_playedCard = card;

	if (find_if(legalPlays.begin(), legalPlays.end(), equalCards) == legalPlays.end()) {
		throw Player::IllegalPlayException();
	}

	if (!cardsPlayed.at(card->getSuit()).empty() && cardsPlayed.at(card->getSuit()).at(0)->getRank() > card->getRank()) {
		cout << "before" << endl;
		cardsPlayed.at(card->getSuit()).insert(cardsPlayed.at(card->getSuit()).begin(), card);
		cout << "inserted" << endl;
	} else {
		cout << "after" << endl;
		cardsPlayed.at(card->getSuit()).push_back(card);
		cout << "inserted" << endl;
	}

	_cards.removeCard(card);
}

Command HumanPlayer::doTurn() {
	Command cmd = Command();
	cout << "Enter command:";
	cin >> cmd;

	if (cmd.type == DECK) {
		// game->deck.print();
	} else if (cmd.type == QUIT) {
		exit(0);
	} else if (cmd.type == PLAY) {
		play(cmd.card);
	}

	return cmd;
}

void HumanPlayer::print() const {

	cout << endl << "Cards on the table:" << endl;
	cout << "Clubs: ";
	printCards(cardsPlayed.at(CLUB));
	cout << endl;
	cout << "Diamonds: ";
	printCards(cardsPlayed.at(DIAMOND));
	cout << endl;
	cout << "Hearts: ";
	printCards(cardsPlayed.at(HEART));
	cout << endl;
	cout << "Spades: ";
	printCards(cardsPlayed.at(SPADE));
	cout << endl;

	cout << "Your hand: ";
	printCards(_cards.hand());
	cout << endl;	

	cout << "Legal plays: ";
	printCards(getLegalPlays());
	cout << endl;
}

