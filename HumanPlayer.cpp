#include "HumanPlayer.h"

//variable for the card that the human player is playing
Card *_playedCard;

//non-member function - returns true if the given card is equal to the card that the player played
bool equalCards(Card *card) {
	if (card->getSuit() == _playedCard->getSuit() && card->getRank() == _playedCard->getRank()) {
		return true;
	}

	return false;
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
	Player::discard(c);
}

// boolean method returns true if the card that a human player is attemping to play is a legal play
bool HumanPlayer::canPlay(Card *card){
	cout << *card << endl;
	vector<Card*> legalPlays = getLegalPlays();
	
	for(int i = 0; i < legalPlays.size() ; i++) {
		if(card->getSuit() == legalPlays.at(i)->getSuit() && card->getRank() == legalPlays.at(i)->getRank()){
			return true;
		}	
	}
	return false;
}

