#include "HumanPlayer.h"

//variable for the card that the human player is playing
Card *_playedCard;

//non-member function - prints the ranks from a list of cards
void printCardsRank(vector<Card*> list) {

	for (vector<Card*>::iterator it = list.begin(); it != list.end(); it++) {
		if (it != list.begin()) {
			cout << " ";
		}
		cout << (*it)->getRank()+1;
	}
}

//non-member function - prints the list of cards (rank and suit)
void printCards(vector<Card*> list) {
	for (vector<Card*>::iterator it = list.begin(); it != list.end(); it++) {
		if (it != list.begin()) {
			cout << " ";
		}
		cout << *(*it);
	}
}

//non-member function - returns true if the given card is equal to the card that the player played
bool equalCards(Card *card) {
	if (card->getSuit() == _playedCard->getSuit() && card->getRank() == _playedCard->getRank()) {
		return true;
	}

	return false;
}

//member function - this is called when the human player uses the "play" command
void HumanPlayer::play(Card c) {
	Card *card = new Card(c.getSuit(), c.getRank());
	if (!card) {
		return;
	}

	_playedCard = card;

	insertCardOnBoard(card);

	//removes the played card from the players hand
	_cards->removeCard(card);
}

// member function - discards a card from the player's hand
void HumanPlayer::discard(Card c) {
	Card *card = new Card(c.getSuit(), c.getRank());
	//throws an exception if there is a legal play that must be made
	if (getLegalPlays().size() != 0) {
		throw HumanPlayer::IllegalDiscardException();
	}

	//adds the card to the discarded cards for the player
	_discardedCards.push_back(card);
	//removes the card from the player's hand
	_cards->removeCard(card);
	_discards++;
	_score += c.getRank()+1;
	cout << "did it discard yo" << endl;
	Player::discard(c);
}

//member function - prints all of the game and card information required for the beginning of a human player's turn
void HumanPlayer::print() const {

	cout << endl << "Cards on the table:" << endl;
	cout << "Clubs: ";
	printCards(*cardsPlayed.at(CLUB));
	cout << endl;
	cout << "Diamonds: ";
	printCards(*cardsPlayed.at(DIAMOND));
	cout << endl;
	cout << "Hearts: ";
	printCards(*cardsPlayed.at(HEART));
	cout << endl;
	cout << "Spades: ";
	printCards(*cardsPlayed.at(SPADE));
	cout << endl;

	cout << "Your hand: ";
	printCards(_cards->hand());
	cout << endl;	

	cout << "Legal plays: ";
	printCards(getLegalPlays());
	cout << endl;
}

bool HumanPlayer::canPlay(Card *card){
	cout << *card << endl;
	vector<Card*> legalPlays = getLegalPlays();
	for(int i=0;i<legalPlays.size();i++) {
		cout << *(legalPlays.at(i)) << endl;	
	}
	
	for(int i = 0; i < legalPlays.size() ; i++) {
		if(card->getSuit() == legalPlays.at(i)->getSuit() && card->getRank() == legalPlays.at(i)->getRank()){
			return true;
		}	
	}
	return false;
}

