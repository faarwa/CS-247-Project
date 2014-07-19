/*
 *
 * PlayerInfoView class.  Is responsible for displaying the frame of information
 * for each player with the option to rage quit
 *
 *  Created by Farwa Naqi on 16/07/14.
 *  Copyright 2014 Farwa Naqi. All rights reserved.
 *
 */


#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm.h>
#include "Game.h"

class GameViewController;
class Player;
class GameView;


class PlayerInfoView : public Gtk::Frame, public Observer {
public:
    PlayerInfoView( GameViewController*, Game*);
	virtual ~PlayerInfoView();
	virtual void update();	// Observer Pattern: concrete update() method
	void setPlayer(Player *player);
	void resetFrame();
private:
	// Observer Pattern: to access Model accessors without having to downcast subject
	Game *model_;
	Player *_player;
	
	// Strategy Pattern member (plus signal handlers)
	GameViewController *controller_;

	void rageButtonClicked();

	Gtk::VBox vpanel;
	Gtk::Button rage;
	Gtk::Label points;
	Gtk::Label discards;
}; 

#endif
