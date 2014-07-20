#ifndef GAME_DIALOG_BOX_H
#define GAME_DIALOG_BOX_H
#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/radiobutton.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

// class declaration for the dialog box to be used for initializing the players at the start of a game
class GameDialogBox : Gtk::Dialog {
public:
	GameDialogBox( Gtk::Window & parentWindow, string title);	// Dialog box constructor
	virtual ~GameDialogBox();					// Dialog box destructor
	string getInput();						// Accessor for the input of the player type
	
private:
	Gtk::RadioButton::Group      group;          			// Options for user to select from in dialog box
	vector<Gtk::RadioButton *>   buttons;				// Vector of the radiobuttons to be added to the dialog box
	string input;							// string representation of the input the user gives for player type "h" or "c"
};
#endif
