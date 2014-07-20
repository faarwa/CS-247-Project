#include "RoundDialogBox.h"
#include <gtkmm/stock.h>
#include <gtkmm/label.h>
#include <iostream>

// Constructor for Dialog Box to finish each round
RoundDialogBox::RoundDialogBox(Gtk::Window & parentWindow, string title, vector<Player*> players) : Dialog(title, parentWindow, true, true){
	// Set text with player info
	string player = "PLAYER ";
	string discards = "Discards: ";
	string score = "Score: ";

	Gtk::VBox* contentArea = this->get_vbox();

	for (vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		ostringstream s1, s2, s3;

		// Output player text
		s1 << player << (*it)->playerNumber();
		Gtk::Label *label1 = Gtk::manage(new Gtk::Label);
		label1->set_label(s1.str());
		contentArea->add(*label1);

		// Output player's discards
		s2 << discards;
		vector<Card*> discardCards = (*it)->discardedCards();
		for (int i = 0; i < discardCards.size(); i++) {
			s2 << *discardCards.at(i) << " ";
		}
		Gtk::Label *label2 = Gtk::manage(new Gtk::Label);
		label2->set_label(s2.str());
		contentArea->add(*label2);

		// Output player's score
		s3 << score << (*it)->score() << endl;
		Gtk::Label *label3 = Gtk::manage(new Gtk::Label);
		label3->set_label(s3.str());
		contentArea->add(*label3);
	}

	show_all_children();
}
