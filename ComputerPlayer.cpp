#include "ComputerPlayer.h"

void ComputerPlayer::play(Card* card) {
	vector<Card*> validCardsToPlay = getLegalPlays();

	vector<Card*>::iterator deleteCard;

	for (vector<Card*>::iterator it = _cards.hand().begin(); it != _cards.hand().end(); it++) {
		for (vector<Card*>::iterator it2 = validCardsToPlay.begin(); it2 != validCardsToPlay.end(); it2++) {
			if ((*it)->getSuit() == (*it2)->getSuit() && (*it)->getRank() == (*it2)->getRank()) {
				cout << "Player " << playerNumber() << " plays " << **it << endl;
				return;
			}
		}
	}

	// _cards.hand().erase(deleteCard);

	//if we get here, there was no valid play, so discard first card in hand
	// discard(_cards.hand().at(0));
}

void ComputerPlayer::print() const {

}

void ComputerPlayer::doTurn() {
	play(NULL);
}