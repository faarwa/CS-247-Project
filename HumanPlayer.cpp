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


	//inserts the played card into the proper spot for the static map used to keep track of all the cards played
	if (!cardsPlayed.at(card->getSuit()).empty() && cardsPlayed.at(card->getSuit()).at(0)->getRank() > card->getRank()) {
		//puts the played card in the front of the vector if it is less than the current lowest card played of that suit
		cardsPlayed.at(card->getSuit()).insert(cardsPlayed.at(card->getSuit()).begin(), card);
	} else {
		//otherwise, puts the played card at the back of the vector
		cardsPlayed.at(card->getSuit()).push_back(card);
	}

	//cout << "Player " << playerNumber() << " plays " << c << "." << endl;

	//removes the played card from the players hand
	_cards.removeCard(card);
}

//member function - this is called when a player has to do a turn
//necessary in human player to be able to handle different commands
Command HumanPlayer::doTurn() {
	//take in a command from the human player
	Command cmd = Command();
	cout << ">";
	cin >> cmd;

	bool isLegal = false;

	do {
		if (cmd.type == QUIT) { // handle quit command
			exit(0);
		} else if (cmd.type == PLAY) { // handle play command
			try {
				//tries to play the card
				play(cmd.card);
				isLegal = true;
			} catch (HumanPlayer::IllegalPlayException &e) {
				//handles the player playing a card that is not a legal play
				isLegal = false;
				cout << "This is not a legal play." << endl;
				cout << ">";
				cin >> cmd;
			}
		} else if (cmd.type == DISCARD) { //handle discard command
			try {
				//tries to discard a card
				discard(cmd.card);
				isLegal = true;
			} catch (HumanPlayer::IllegalDiscardException &e) {
				//handles the player trying to discard when they have a legal play
				isLegal = false;
				cout << "You have a legal play. You may not discard." << endl;
				cout<< ">";
				cin >> cmd;
			}
		} else {
			isLegal = true; //if it was none of these commands, stop the loop
		}
	} while (!isLegal); // stop looping for input if the player has made a legal play

	//for any commands that could not be handled within the player class, this returns to the Game class to handle them
	return cmd;
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
	_cards.removeCard(card);
	_discards++;
	_score += c.getRank()+1;
	cout << "did it discard yo" << endl;
	Player::discard(c);
}

//member function - prints all of the game and card information required for the beginning of a human player's turn
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

