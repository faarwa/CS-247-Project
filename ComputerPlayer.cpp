	#include "ComputerPlayer.h"

void ComputerPlayer::play(Card card) {
	vector<Card*> validCardsToPlay = getLegalPlays();
	
	Card *deleteCard = NULL;

	for (vector<Card*>::iterator it = _cards.hand().begin(); it != _cards.hand().end(); it++) {
		for (vector<Card*>::iterator it2 = validCardsToPlay.begin(); it2 != validCardsToPlay.end(); it2++) {
			if (**it == **it2) {
				deleteCard = *it;
				cout << endl << "Player " << playerNumber() << " plays " << **it << endl;
				cardsPlayed.at(deleteCard->getSuit()).push_back(deleteCard);
				_cards.removeCard(deleteCard);

				return;
			} 
		}
	}

	if (!deleteCard) {
		cout << endl << "Player " << playerNumber() << " discards " << *_cards.hand().at(0) << endl;
		discard(*_cards.hand().at(0));
	}
}

void ComputerPlayer::print() const {

}

Command ComputerPlayer::doTurn() {
	Command c = Command();
	c.type = PLAY;
	play(c.card);
	return c;
}

void ComputerPlayer::discard(Card c) {
	Card *card = new Card(c.getSuit(), c.getRank());
	vector<Card*> playerHand = cards().hand();
	for(int i=0;i<playerHand.size();i++){
		if(*playerHand.at(i) == c){
			_discardedCards.push_back(card);
			_cards.removeCard(card);
			break;
		}
	}
}