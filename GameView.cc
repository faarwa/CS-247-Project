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
#include <iostream>
#include <string>

using namespace std;

std::string convertInt(int num){
	std::stringstream ss;
	ss << num;
	return ss.str();
}

// Creates buttons with labels. Sets butBox elements to have the same size, 
// with 10 pixels between widgets
GameView::GameView(GameViewController *c, Game *m) : model_(m), controller_(c), panels(true,10), butBox(true, 10), start_button( "Start new game with seed" ), end_button( "End current game" ) {

	vector<string> playerTypes;
	for(int i=0;i<4;i++){
		GameDialogBox dialog( *this, "Is player " + convertInt(i+1) + " a human or a computer?" );
		playerTypes.push_back(dialog.getInput());
	}
	m->setPlayers(playerTypes);

	// Sets some properties of the window.
    set_title( "Straights" );
	set_border_width( 300 );
	
	// Add panels to the window
	add(panels);

	// Add button box and card image to the panels
	panels.add( butBox );
	// panels.add( card );
	// card.set( deck.null() );

	// Add buttons to the box (a container). Buttons initially invisible
	butBox.add( start_button );
	butBox.add( end_button );


	// Associate button "clicked" events with local onButtonClicked() method defined below.
	start_button.signal_clicked().connect( sigc::mem_fun( *this, &GameView::nextButtonClicked ) );
	end_button.signal_clicked().connect( sigc::mem_fun( *this, &GameView::resetButtonClicked ) );
	
	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model
	model_->subscribe(this);

} // View::View

GameView::~GameView() {}


void GameView::update() {
  // Suits suit = model_->suit();
  // Faces face = model_->face();
  // if ( suit == NOSUIT ) 
  //   card.set( deck.null() );
  // else
  //   card.set( deck.image(face, suit) );

}

void GameView::nextButtonClicked() {
  controller_->nextButtonClicked();
} // View::nextButtonClicked

void GameView::resetButtonClicked() {
  controller_->resetButtonClicked();
} // View::resetButtonClicked
