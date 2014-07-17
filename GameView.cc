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
#include <iostream>
#include <string>

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

	vector<Player*> players = model_->players();
	for (int i = 0; i < 4; i++) {
		playerInfoFrames.push_back(new PlayerInfoView(controller_, players.at(i)));
	}

	set_resizable(false);

	set_size_request(1000,700);

	add(vpanels);

	start_button.set_label( "Start new game with seed" );
	end_button.set_label( "End current game" );

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
	
	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

GameView::~GameView() {}


void GameView::update() {
  //update players hand
	vector<Card*> newhand = model_->getHand();
	for(int i=0; i < 13; i++){
		if(i < newhand.size()){
			cards_.at(i)->updateFace(newhand.at(i));
		}
		else{
			cards_.at(i)->updateFace(NULL);
		}
	}
}

// Glib::RefPtr<Gdk::Pixbuf> null() {
// 	return Gdk::Pixbuf::create_from_file( "img/back_1.png" );
// } // DeckGUI::getNullCardImage

void GameView::startButtonClicked() {
	// Sets players
	vector<string> playerTypes;
	for(int i=0;i<4;i++){
		GameDialogBox dialog( *this, "Is player " + convertInt(i+1) + " a human or a computer?" );
		playerTypes.push_back(dialog.getInput());
	}
	model_->setPlayers(playerTypes);

  	controller_->startButtonClicked();
} 

void GameView::endButtonClicked() {
  controller_->endButtonClicked();
} 

void GameView::rageButtonClicked() {

}
