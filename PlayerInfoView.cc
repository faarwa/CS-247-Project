#include "observer.h"
#include "PlayerInfoView.h"
#include "GameViewController.h"
#include "subject.h"
#include "GameDialogBox.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor for the player info view
PlayerInfoView::PlayerInfoView(GameViewController *c, Game* g) : model_(g), controller_(c), vpanel(true,10), rage("Rage"),
	points("0 points") , discards("0 discards") {

	// Sets up the buttons and panels for the user info view
	rage.set_sensitive(false);
	vpanel.add(rage);
	vpanel.add(points);
	vpanel.add(discards);

	add(vpanel);

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	rage.signal_clicked().connect( sigc::mem_fun( *this, &PlayerInfoView::rageButtonClicked ) );	
	
	// The final step is to display the buttons (they display themselves)
	show_all();
	model_->subscribe(this);

	// Register view as observer of model game

}

// Destructor
PlayerInfoView::~PlayerInfoView() {}

// Mutator for the player that the view is displaying information on
void PlayerInfoView::setPlayer(Player *player) {
	_player = player;
	update();
}

// Resets the view to no points, discards, and sets the rage button to unclickable
void PlayerInfoView::resetFrame() {
	rage.set_sensitive(false);
	points.set_label("0 points");
	discards.set_label("0 points");
}

// update method to be called upon notify in the model (game)
void PlayerInfoView::update() {	
	// updates the player information displayed
	if (_player != NULL) {
		int pointsNum = _player->score();
		int discardsNum = _player->discards();
		ostringstream s1;
		s1 << pointsNum << " points" << endl;
		ostringstream s2;
		s2 << discardsNum << " discards" << endl;

		points.set_label(s1.str());
		discards.set_label(s2.str());
	}

	// updates the rage button sensitivity depending on the current player
	if (model_->getCurrentPlayer() == _player && _player->canRage()) {
		rage.set_sensitive(true);
	} else {
		rage.set_sensitive(false);
	}
}

// OnClick for the rage button
void PlayerInfoView::rageButtonClicked() {
	// calls the controller's rageButtonClicked
	controller_->rageButtonClicked();
	// sets the player to the current player
	_player = model_->players().at(model_->currentPlayer()-1);
}
