#include "observer.h"
#include "PlayerInfoView.h"
#include "GameViewController.h"
#include "subject.h"
#include "GameDialogBox.h"
#include <iostream>
#include <string>

using namespace std;

// Creates buttons with labels. Sets vpanels elements to have the same size, 
// with 10 pixels between widgets
PlayerInfoView::PlayerInfoView(GameViewController *c, Game* g) : model_(g), controller_(c), vpanel(true,10), rage("Rage"),
	points("0 points") , discards("0 discards") {

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

	// Register view as observer of model

} // View::View

PlayerInfoView::~PlayerInfoView() {}

void PlayerInfoView::setPlayer(Player *player) {
	_player = player;
	update();
}


void PlayerInfoView::update() {
	int pointsNum = _player->score();
	int discardsNum = _player->discards();
	ostringstream s1;
	s1 << pointsNum << " points" << endl;
	ostringstream s2;
	s2 << discardsNum << " discards" << endl;

	points.set_label(s1.str());
	discards.set_label(s2.str());
	rage.set_sensitive(_player->canRage());
}

void PlayerInfoView::rageButtonClicked() {
	_player->unsubscribe(this);
	controller_->rageButtonClicked();
	_player = model_->players().at(model_->currentPlayer()-1);
	_player->subscribe(this);
	update();
}