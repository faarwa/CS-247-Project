#ifndef MVC_VIEW_H
#define MVC_VIEW_H

#include <gtkmm.h>
#include "observer.h"
#include "DeckGUI.h"
#include "CardButton.h"
#include "TableCard.h"
#include <vector>
#include "PlayerInfoView.h"

class GameViewController;
class Game;
class Player;

// class declaration for the main GameView
class GameView : public Gtk::Window, public Observer {
public:
    	GameView( GameViewController*, Game* );		// constructor
	virtual ~GameView();				// destructor
	virtual void update();				// Observer Pattern: concrete update() method

private:
	// Observer Pattern: to access Model accessors
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

	// Boxes for each suit on the table
	Gtk::HBox spades;
	Gtk::HBox hearts;
	Gtk::HBox clubs;
	Gtk::HBox diamonds;

	// vector of player info frames for each player
	vector <PlayerInfoView*> playerInfoFrames;

	// Signal handlers:
	void startButtonClicked();
	void endButtonClicked();
	void cardClicked(int i);
	void seedEntryChanged();
	
	vector<CardButton*> cards_;	// vector for the cards to show in player's hand
	std::map<Suit, vector<TableCard*> > cardsPlayed_;	// map of all of the cards played in the game
};

#endif
