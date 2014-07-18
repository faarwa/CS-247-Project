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


#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "observer.h"
#include "DeckGUI.h"
#include "CardButton.h"
#include <vector>
#include "PlayerInfoView.h"

class GameViewController;
class Game;
class Player;

class GameView : public Gtk::Window, public Observer {
public:
    GameView( GameViewController*, Game* );
	virtual ~GameView();
	virtual void update();	// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Game *model_;
	
	// Strategy Pattern member (plus signal handlers)
	GameViewController *controller_;

	DeckGUI deck;

	// Member widgets:
	Gtk::HBox menu;
	Gtk::Frame menuFrame;
	Gtk::Frame cardsPlayedFrame;
	Gtk::Frame handFrame;
	Gtk::VBox playing_space;
	Gtk::HBox players_controls;
	Gtk::HButtonBox player_hand;
	Gtk::HBox hpanels;      // Main window divided into two horizontal panels
	Gtk::VBox vpanels;      // Vertical boxes for stacking buttons vertically
	Gtk::Button start_button;
	Gtk::Button end_button;
	Gtk::Entry seed;
	Gtk::Image card;

	Gtk::HBox spades;
	Gtk::HBox hearts;
	Gtk::HBox clubs;
	Gtk::HBox diamonds;

	vector <PlayerInfoView*> playerInfoFrames;

	// Signal handlers:
	void startButtonClicked();
	void endButtonClicked();
	void cardClicked(int i);

	vector<CardButton*> cards_;
}; // View

#endif
