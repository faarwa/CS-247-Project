#include "observer.h"
#include "GameView.h"
#include "GameViewController.h"
#include "Game.h"
#include "subject.h"
#include "GameDialogBox.h"
#include "CardButton.h"
#include "TableCard.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "RoundDialogBox.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

// helper function that converts an integer to a string
std::string convertInt(int num){
	std::stringstream ss;
	ss << num;
	return ss.str();
}

// Constructor for the main game view
GameView::GameView(GameViewController *c, Game *m) : model_(m), controller_(c), vpanels(false,10), card(deck.null()),
	cardsPlayedFrame("Cards on the table"), handFrame("Your hand") {

	// sets default size for the game window
	set_default_size(1000,700);

	// creates 4 player info views (these views contain rage button, score, and number of discards)
	for (int i = 0; i < 4; i++) {
		playerInfoFrames.push_back(new PlayerInfoView(controller_, model_));
	}

	// sets up view, labels, and buttons
	set_resizable(false);

	set_size_request(1000,700);

	add(vpanels);

	start_button.set_label( "Start new game with seed" );
	end_button.set_label( "End current game" );
	end_button.set_sensitive(false);

	menu.set_homogeneous(true);
	menu.set_spacing(10);
	vpanels.add(menuFrame);

	menuFrame.add(menu);

	menu.add(start_button);
	menu.add(seed);
	menu.add(end_button);

	seed.get_buffer()->set_text("0");
	model_->setSeed(0);

	playing_space.set_homogeneous(true);
	vpanels.add(cardsPlayedFrame);
	playing_space.set_homogeneous(true);
	playing_space.set_spacing(10);
	cardsPlayedFrame.add(playing_space);
	players_controls.set_homogeneous(true);
	vpanels.add(players_controls);

	for (int i = 0; i < 4; i++) {
		ostringstream s1;
		s1 << "Player " << i+1 << endl;
		playerInfoFrames.at(i)->set_label(s1.str());
		players_controls.add(*playerInfoFrames.at(i));
	}

	player_hand.set_homogeneous(true);
	player_hand.set_spacing(10);
	vpanels.add(handFrame);
	handFrame.add(player_hand);
	
	// sets up empty buttons that will be used for displaying the player's hand and for input on playing a card
	for(int i=0; i < 13; i++){
		CardButton *cardbutton = new CardButton(NULL);
		cards_.push_back(cardbutton);
		player_hand.add(*cardbutton);
	}

	vector<TableCard*> suitCards;
	cardsPlayed_[SPADE] = suitCards;
	cardsPlayed_[CLUB] = suitCards;
	cardsPlayed_[HEART] = suitCards;
	cardsPlayed_[DIAMOND] = suitCards;

	// sets up empty cards for the table - all blank cards used for intializing a game
	// creates 13 TableCard's for each suit
	spades.set_homogeneous(true);
	spades.set_spacing(10);
	playing_space.add(spades);
	for (int i = 0; i < 13; i++) {
		TableCard *card = new TableCard(NULL, deck);
		spades.add(*card);
		cardsPlayed_.at(SPADE).push_back(card);
	}

	hearts.set_homogeneous(true);
	hearts.set_spacing(10);
	playing_space.add(hearts);
	for (int i = 0; i < 13; i++) {
		TableCard *card = new TableCard(NULL, deck);
		hearts.add(*card);
		cardsPlayed_.at(HEART).push_back(card);
	}

	clubs.set_homogeneous(true);
	clubs.set_spacing(10);
	playing_space.add(clubs);
	for (int i = 0; i < 13; i++) {
		TableCard *card = new TableCard(NULL, deck);
		clubs.add(*card);
		cardsPlayed_.at(CLUB).push_back(card);
	}

	diamonds.set_homogeneous(true);
	diamonds.set_spacing(10);
	playing_space.add(diamonds);
	for (int i = 0; i < 13; i++) {
		TableCard *card = new TableCard(NULL, deck);
		diamonds.add(*card);
		cardsPlayed_.at(DIAMOND).push_back(card);
	}

    	set_title( "Straights" );

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	start_button.signal_clicked().connect( sigc::mem_fun( *this, &GameView::startButtonClicked ) );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &GameView::endButtonClicked ) );
	seed.signal_changed().connect( sigc::mem_fun( *this, &GameView::seedEntryChanged ) );
	for(int i=0; i < 13 ; i++){
		cards_.at(i)->signal_clicked().connect(sigc::bind( sigc::mem_fun(*this, &GameView::cardClicked), i) );
	}
	
	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

}

GameView::~GameView() {}


void GameView::update() {
	// gets correct player info frame (depending on which player's turn it is)
	playerInfoFrames.at(model_->currentPlayer()-1)->setPlayer(model_->getCurrentPlayer());
	// update players handFrame
	vector<Card*> newhand = model_->getHand();
	for (int i = 0; i < 13; i++) {
		if (i < newhand.size()){
			// updates the user's hand to have correct card images
			cards_.at(i)->setCardButton(newhand.at(i));
		}
		else {
			// if the user has less than 13 cards, blank cards are put in the remaining of the 13 spots
			cards_.at(i)->setCardButton(NULL);
		}
	}
	
	// update game board
	std::map<Suit, vector<Card*>* > cards = Player::playedCards();

	if(cards.at(CLUB)->size()==0 && cards.at(DIAMOND)->size()==0 && cards.at(HEART)->size()==0 && cards.at(SPADE)->size()==0){
		// the board needs to be cleared
		// sets all of the cards on the table to blank card images
		for(int i=0 ; i < cardsPlayed_.at(CLUB).size() ; i++){
			cardsPlayed_.at(CLUB).at(i)->updateFace(NULL);
		}
		for(int i=0 ; i < cardsPlayed_.at(DIAMOND).size() ; i++){
			cardsPlayed_.at(DIAMOND).at(i)->updateFace(NULL);
		}
		for(int i=0 ; i < cardsPlayed_.at(HEART).size() ; i++){
			cardsPlayed_.at(HEART).at(i)->updateFace(NULL);
		}
		for(int i=0 ; i < cardsPlayed_.at(SPADE).size() ; i++){
			cardsPlayed_.at(SPADE).at(i)->updateFace(NULL);
		}
	}
	else{
		// set all of the cards on the board with their correct images of played cards
		for(int i=0 ; i < cards.at(CLUB)->size() ; i++){
			cardsPlayed_.at(CLUB).at(cards.at(CLUB)->at(i)->getRank())->updateFace(cards.at(CLUB)->at(i));
		}
		for(int i=0 ; i < cards.at(DIAMOND)->size() ; i++){
			cardsPlayed_.at(DIAMOND).at(cards.at(DIAMOND)->at(i)->getRank())->updateFace(cards.at(DIAMOND)->at(i));
		}
		for(int i=0 ; i < cards.at(HEART)->size() ; i++){
			cardsPlayed_.at(HEART).at(cards.at(HEART)->at(i)->getRank())->updateFace(cards.at(HEART)->at(i));
		}
		for(int i=0 ; i < cards.at(SPADE)->size() ; i++){
			cardsPlayed_.at(SPADE).at(cards.at(SPADE)->at(i)->getRank())->updateFace(cards.at(SPADE)->at(i));
		}
	}

	//show pop ups at the end of a round
	if(model_->isRoundOver()) {
		RoundDialogBox dialog(*this, "Results for the round:", model_->players());
		dialog.set_border_width( 100 );
		dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
		dialog.show_all_children();
		dialog.run();
		end_button.set_sensitive(false);
		start_button.set_sensitive(true);
		for (int i = 0; i < 4; i++) {
			playerInfoFrames.at(i)->resetFrame();
		}
	}
	else if(model_->isGameOver()) {
		// if the game is over, display a dialog with the winner
		ostringstream s1;
		s1 << "Player " << model_->getWinningPlayer() << " wins!" << endl;
		string winner = s1.str();
		Gtk::Dialog dialog(winner, *this,true, true);
		dialog.set_border_width( 100 );
		dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
		dialog.show_all_children();
		dialog.run();
	}
}

// OnClick of the start button
void GameView::startButtonClicked() {
	// Sets players for the game
	vector<Player*> players;
	for (int i = 0; i < 4; i++) {
		GameDialogBox dialog( *this, "Is player " + convertInt(i+1) + " a human or a computer?" );
		if (dialog.getInput() == "h") {
			players.push_back(new HumanPlayer(i+1));
		}	
		else {
			players.push_back(new ComputerPlayer(i+1));
		}
	}

	model_->setPlayers(players);
	
	// sets the start button to unclickable and the end button to clickable
	start_button.set_sensitive(false);
	end_button.set_sensitive(true);

	// calls the controller's startButtonClicked()
  	controller_->startButtonClicked();
  	
	// sets the player info frames to the proper players
	for (int i = 0; i < 4; i++) {
  		playerInfoFrames.at(i)->setPlayer(players.at(i));
  	}
} 

// OnClick event for a card
void GameView::cardClicked(int i) {
	Card *card = cards_.at(i)->getCard();
	try {
		// attempts to play the card that was clicked
		controller_->cardClicked(card);
	} catch (HumanPlayer::IllegalDiscardException &e) {
		// if there is an exception with playing the card, show an Illegal Play dialog
		Gtk::Dialog dialog("Illegal play", *this,true, true);
		dialog.set_border_width( 100 );
		dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
		dialog.show_all_children();
		dialog.run();
	}
}

//OnClick event for the end button
void GameView::endButtonClicked() {
	// sets the start button to clickable
	start_button.set_sensitive(true);
	// calls the controller's endButtonClicked method
  	controller_->endButtonClicked();
	// sets the end button to unclickable
  	end_button.set_sensitive(false);
  	
	// resets all of the playerInfoFrames
	// for (int i = 0; i < 4; i++) {
 //  		playerInfoFrames.at(i)->resetFrame();
 //  	}
} 

// Changes the seed for the shuffling
void GameView::seedEntryChanged() {
	int s;
	s = atoi(seed.get_buffer()->get_text().c_str());
	model_->setSeed(s);
}
