#ifndef ROUND_DIALOG_BOX_H
#define ROUND_DIALOG_BOX_H
#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <string>
#include <vector>
#include "Player.h"
using std::string;
using std::vector;

// class for dialog box to show player information at the end of each round
class RoundDialogBox : public Gtk::Dialog {
public:
	RoundDialogBox (Gtk::Window & parentWindow, string title, vector<Player*> players);
	~RoundDialogBox() {}		
};
#endif
