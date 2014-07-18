/*
 * MVC example of GTKmm program
 *
 * View class.  Is responsible for buttons (that user clicks) and for displaying
 * the top card of the deck.
 *
 *  Created by Jo Atlee on 06/07/09.
 *  Copyright 2009 UW. All rights reserved.
 *
 */


#include "observer.h"
#include "GameView.h"
#include "GameViewController.h"
#include "Game.h"
#include "subject.h"
#include "GameDialogBox.h"
#include "CardButton.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
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
GameView::GameView(GameViewController *c, Game *m) : model_(m), controller_(c), vpanels(true,10), card(deck.null()),
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
		CardButton *cardbutton = new CardButton(NULL, deck);
		cards_.push_back(cardbutton);
		player_hand.add(*cardbutton);
	}

	spades.set_homogeneous(true);
	spades.set_spacing(10);
	playing_space.add(spades);
	for (int i = 0; i < 13; i++) {
		Gtk::Image *card = new Gtk::Image(Gdk::Pixbuf::create_from_file("img/nothing.png"));
		spades.add(*card);
	}

	hearts.set_homogeneous(true);
	hearts.set_spacing(10);
	playing_space.add(hearts);
	for (int i = 0; i < 13; i++) {
		Gtk::Image *card = new Gtk::Image(Gdk::Pixbuf::create_from_file("img/nothing.png"));
		hearts.add(*card);
	}

	clubs.set_homogeneous(true);
	clubs.set_spacing(10);
	playing_space.add(clubs);
	for (int i = 0; i < 13; i++) {
		Gtk::Image *card = new Gtk::Image(Gdk::Pixbuf::create_from_file("img/nothing.png"));
		clubs.add(*card);
	}

	diamonds.set_homogeneous(true);
	diamonds.set_spacing(10);
	playing_space.add(diamonds);
	for (int i = 0; i < 13; i++) {
		Gtk::Image *card = new Gtk::Image(Gdk::Pixbuf::create_from_file("img/nothing.png"));
		diamonds.add(*card);
	}

	// Sets some properties of the window.
    set_title( "Straights" );
	// // set_border_width( 300 );

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	start_button.signal_clicked().connect( sigc::mem_fun( *this, &GameView::startButtonClicked ) );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &GameView::endButtonClicked ) );
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
  //update players hand
	vector<Card*> newhand = model_->getHand();

	for (int i = 0; i < 13; i++){
		if (i < newhand.size()){
			cards_.at(i)->updateFace(newhand.at(i));
		}
		else {
			cards_.at(i)->updateFace(NULL);
		}
	}

}

void GameView::startButtonClicked() {
	// Sets players
	// vector<string> playerTypes;
	vector<Player*> players;
	for (int i = 0; i < 4; i++) {
		GameDialogBox dialog( *this, "Is player " + convertInt(i+1) + " a human or a computer?" );
		// playerTypes.push_back(dialog.getInput());
		if (dialog.getInput() == "h") {
			players.push_back(new HumanPlayer(i+1));
		}	
		else {
			players.push_back(new ComputerPlayer(i+1));
		}
		playerInfoFrames.at(i)->setPlayer(players.at(i));
	}

	model_->setPlayers(players);
	start_button.set_sensitive(false);
	end_button.set_sensitive(true);
  	controller_->startButtonClicked();
} 

void GameView::cardClicked(int i) {
	Card *card = cards_.at(i)->getCard();
	controller_->cardClicked(card);
}

void GameView::endButtonClicked() {
  	controller_->endButtonClicked();
} 