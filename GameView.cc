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


std::string convertInt(int num){
	std::stringstream ss;
	ss << num;
	return ss.str();
}

// Creates buttons with labels. Sets vpanels elements to have the same size, 
// with 10 pixels between widgets
GameView::GameView(GameViewController *c, Game *m) : model_(m), controller_(c), vpanels(false,10), card(deck.null()),
	cardsPlayedFrame("Cards on the table"), handFrame("Your hand") {


	set_default_size(1000,700);

	for (int i = 0; i < 4; i++) {
		playerInfoFrames.push_back(new PlayerInfoView(controller_, model_));
	}

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
	// cardsPlayedFrame.set_label("Cards on the table");
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

	// Sets some properties of the window.
    set_title( "Straights" );
	// // set_border_width( 300 );

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

} // View::View

GameView::~GameView() {}


void GameView::update() {
	playerInfoFrames.at(model_->currentPlayer()-1)->setPlayer(model_->getCurrentPlayer());
	//update players handFrame
	vector<Card*> newhand = model_->getHand();
	for (int i = 0; i < 13; i++) {
		if (i < newhand.size()){
			cards_.at(i)->setCardButton(newhand.at(i));
		}
		else {
			cards_.at(i)->setCardButton(NULL);
		}
	}
	
	//update game board
	std::map<Suit, vector<Card*>* > cards = Player::playedCards();

	if(cards.at(CLUB)->size()==0 && cards.at(DIAMOND)->size()==0 && cards.at(HEART)->size()==0 && cards.at(SPADE)->size()==0){
		//the board needs to be cleared
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
	if(model_->isGameOver()){
		ostringstream s1;
		s1 << "Player " << model_->getWinningPlayer() << " wins!" << endl;
		string winner = s1.str();
		cout <<"GAMEOVER"<<endl;
		Gtk::Dialog dialog(winner, *this,true, true);
		dialog.set_border_width( 100 );
		dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
		dialog.show_all_children();
		dialog.run();
	}
	else if(model_->isRoundOver()){
		cout << "SHOW DIALOG" << endl;
		RoundDialogBox dialog(*this, "Results for the round:", model_->players());
		dialog.set_border_width( 100 );
		dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
		dialog.show_all_children();
		dialog.run();
	}
}

void GameView::startButtonClicked() {
	// Sets players
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
	start_button.set_sensitive(false);
	end_button.set_sensitive(true);
  	controller_->startButtonClicked();
  	for (int i = 0; i < 4; i++) {
  		playerInfoFrames.at(i)->setPlayer(players.at(i));
  	}

  	if (!model_->getCurrentPlayer()->canRage()) {
  		controller_->computerPlay();
  	}
} 

void GameView::cardClicked(int i) {
	Card *card = cards_.at(i)->getCard();
	try {
		controller_->cardClicked(card);
	} catch (HumanPlayer::IllegalDiscardException &e) {
		Gtk::Dialog dialog("Illegal play", *this,true, true);
		dialog.set_border_width( 100 );
		dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
		dialog.show_all_children();
		dialog.run();
	}
}

void GameView::endButtonClicked() {
	start_button.set_sensitive(true);
  	controller_->endButtonClicked();
  	end_button.set_sensitive(false);
  	for (int i = 0; i < 4; i++) {
  		playerInfoFrames.at(i)->resetFrame();
  	}
} 

void GameView::seedEntryChanged() {
	int s;
	s = atoi(seed.get_buffer()->get_text().c_str());
	model_->setSeed(s);
}
