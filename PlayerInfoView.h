#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

#include <gtkmm.h>
#include "Game.h"

class GameViewController;
class Player;
class GameView;

// class declaration for player info view
class PlayerInfoView : public Gtk::Frame, public Observer {
public:
    	PlayerInfoView( GameViewController*, Game*);		// constructor for the player info view
	virtual ~PlayerInfoView();				// destructor for the player info view
	virtual void update();					// Observer Pattern: concrete update() method
	void setPlayer(Player *player);				// mutator for the player of the player info view
	void resetFrame();					// resets the frame view to no points, discards, and makes the rage button unclickable
private:
	Game *model_;						// Observer Pattern: to access Model accessors without having to downcast subject
	Player *_player;					// private data member: the player for the player info view
	
	GameViewController *controller_;			// strategy pattern member

	void rageButtonClicked();				// OnClick for rage button

	// Views for the player info view
	Gtk::VBox vpanel;
	Gtk::Button rage;
	Gtk::Label points;
	Gtk::Label discards;
}; 

#endif
