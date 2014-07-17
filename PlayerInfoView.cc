#include "observer.h"
#include "PlayerInfoView.h"
#include "GameViewController.h"
#include "Game.h"
#include "subject.h"
#include "GameDialogBox.h"
#include <iostream>
#include <string>

using namespace std;

// Creates buttons with labels. Sets vpanels elements to have the same size, 
// with 10 pixels between widgets
PlayerInfoView::PlayerInfoView(GameViewController *c) : controller_(c), vpanel(true,10), rage("Rage"),
	points("0 points") , discards("0 discards") {

	rage.set_sensitive(false);
	vpanel.add(rage);
	vpanel.add(points);
	vpanel.add(discards);

	add(vpanel);

	// Associate button "clicked" events with local onButtonClicked() method defined below.
	// rage.signal_clicked().connect( sigc::mem_fun( *this, &GameView::rageButtonClicked ) );	
	
	// The final step is to display the buttons (they display themselves)
	show_all();

	// Register view as observer of model

} // View::View

PlayerInfoView::~PlayerInfoView() {}

void PlayerInfoView::setPlayer(Player *player) {
	model_ = player;
	player->subscribe(this);
	update();
}


void PlayerInfoView::update() {
	int pointsNum = model_->score();
	int discardsNum = model_->discards();
	ostringstream s1;
	s1 << pointsNum << " points" << endl;
	ostringstream s2;
	s2 << discardsNum << " discards" << endl;

	points.set_label(s1.str());
	discards.set_label(s2.str());
	rage.set_sensitive(model_->canRage());
}