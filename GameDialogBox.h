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

class GameDialogBox : Gtk::Dialog {
public:
	GameDialogBox( Gtk::Window & parentWindow, string title);
	virtual ~GameDialogBox();
	string getInput();
	
private:
	Gtk::RadioButton::Group      group;          
	vector<Gtk::RadioButton *>   buttons;
	string input;
};
#endif
