#include "ComputerPlayer.h"

// member function - this is called when a player has to do a turn
// (more important for human player to determine other commands)
// since computer player doesnt take commands, just call play with a null card
Command ComputerPlayer::doTurn() {
	Command c = Command();
	c.type = PLAY;
	play(c.card);
	return c;
}

// member function - this is called for the computer player to do a turn
void ComputerPlayer::play(Card card) {
	// get the legal plays that computer player can do
	vector<Card*> validCardsToPlay = getLegalPlays();

	Card *deleteCard = NULL;

	// Iterate hand to find the first legal play and play that card 
	// Return immediately
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

	// If the function reaches here, there are no legal plays, so discard the first card in the hand
	if (!deleteCard) {
		cout << endl << "Player " << playerNumber() << " discards " << *_cards.hand().at(0) << endl;
		discard(*_cards.hand().at(0));
	}
}

// member function - discards a card from the hand 
void ComputerPlayer::discard(Card c) {
	Card *card = new Card(c.getSuit(), c.getRank());
	vector<Card*> playerHand = cards().hand();

	// Iterate the hand and call card hand to remove the card once it's found
	for(int i=0;i<playerHand.size();i++){
		if(*playerHand.at(i) == c){
			_discardedCards.push_back(card);
			_cards.removeCard(card);
			break;
		}
	}
}