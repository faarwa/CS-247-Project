#include "ComputerPlayer.h"

void ComputerPlayer::play(Card* card) {
	vector<Card*> validCardsToPlay = getLegalPlays();

	Card *deleteCard = NULL;

	for (vector<Card*>::iterator it = _cards.hand().begin(); it != _cards.hand().end(); it++) {
		for (vector<Card*>::iterator it2 = validCardsToPlay.begin(); it2 != validCardsToPlay.end(); it2++) {
			if (**it == **it2) {
				cout << "Player " << playerNumber() << " plays " << **it << endl;
				deleteCard = *it;
				break;
			} 
		}
	}

	cout << "end?" << endl;

	if (!deleteCard) {
		cout << "discarding" << endl;
		discard(_cards.hand().at(0));
	} else {
		cout << "pushing" <<endl;
		Player::cardsPlayed.at(deleteCard->getSuit()).push_back(deleteCard);
		cout << "pushed" << endl;
	}
}

void ComputerPlayer::print() const {

}

Command ComputerPlayer::doTurn() {
	play(NULL);
	Command c = Command();
	c.type = PLAY;
	return c;
}