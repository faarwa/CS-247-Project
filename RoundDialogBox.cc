#include "RoundDialogBox.h"
#include <gtkmm/stock.h>
#include <gtkmm/label.h>
#include <iostream>

RoundDialogBox::RoundDialogBox(Gtk::Window & parentWindow, string title, vector<Player*> players) : Dialog(title, parentWindow, true, true){
	//set text with player info
	string discards="Discards: ";


	Gtk::VBox* contentArea = this->get_vbox();
	Gtk::Label* label1a = Gtk::manage(new Gtk::Label);
	label1a->set_label("Player 1:");
	Gtk::Label* label1b = Gtk::manage(new Gtk::Label);
	label1b->set_label("Discards:");
	Gtk::Label* label1c = Gtk::manage(new Gtk::Label);
	label1c->set_label("Score:");

	Gtk::Label* label2a = Gtk::manage(new Gtk::Label);
	label2a->set_label("Player 2:");
	Gtk::Label* label2b = Gtk::manage(new Gtk::Label);
	label2b->set_label("Discards:");
	Gtk::Label* label2c = Gtk::manage(new Gtk::Label);
	label2c->set_label("Score:");

	Gtk::Label* label3a = Gtk::manage(new Gtk::Label);
	label1a->set_label("Player 3:");
	Gtk::Label* label3b = Gtk::manage(new Gtk::Label);
	label3b->set_label("Discards:");
	Gtk::Label* label3c = Gtk::manage(new Gtk::Label);
	label3c->set_label("Score:");

	Gtk::Label* label4a = Gtk::manage(new Gtk::Label);
	label4a->set_label("Player 4:");
	Gtk::Label* label4b = Gtk::manage(new Gtk::Label);
	label4b->set_label("Discards:");
	Gtk::Label* label4c = Gtk::manage(new Gtk::Label);
	label4c->set_label("Score:");

	contentArea->add(*label1a);
	contentArea->add(*label1b);
	contentArea->add(*label1c);
	contentArea->add(*label2a);
	contentArea->add(*label2b);
	contentArea->add(*label2c);
	contentArea->add(*label3a);
	contentArea->add(*label3b);
	contentArea->add(*label3c);
	contentArea->add(*label4a);
	contentArea->add(*label4b);
	contentArea->add(*label4c);

	show_all_children();
}

RoundDialogBox::~RoundDialogBox(){
}
