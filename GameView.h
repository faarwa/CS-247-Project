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
#include "Game.h"

class GameViewController;
class Game;


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

	// Member widgets:
	Gtk::HBox panels;      // Main window divided into two horizontal panels
	Gtk::VBox butBox;      // Vertical boxes for stacking buttons vertically
	Gtk::Button start_button;
	Gtk::Button end_button;
	Gtk::Image card;

	// Signal handlers:
	void nextButtonClicked();
	void resetButtonClicked();

}; // View

#endif
