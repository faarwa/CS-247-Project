#include "GameDialogBox.h"
#include <gtkmm/stock.h>
#include <iostream>

GameDialogBox::GameDialogBox( Gtk::Window & parentWindow, string title) : Dialog( title, parentWindow, true, true ) {
	vector<string> messages;
	messages.push_back( "Human" );
	messages.push_back( "Computer" );
	
	set_border_width( 150 );
	
	Gtk::VBox* contentArea = this->get_vbox();
	
	for ( int i = 0; i < messages.size(); i++ ) {
		buttons.push_back( Gtk::manage( new Gtk::RadioButton( group, messages[i] ) ) );
		contentArea->add( *buttons[i] );
	}
	
	// Make the first button the initial active choice.
	buttons[0]->set_active();
	
	// Add a standard "ok" buttons with the appropriate responses when clicked.
    Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();
	
    // Wait for a response from the dialog box.
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            for ( int i = 0; i < messages.size(); i++ ) {
				if ( buttons[i]->get_active() ) {
					//std::cout << "chose '" << messages[i] << "'" << std::endl;
					if(messages[i] == "Human"){
						input = "h";
					}
					else{
						input = "c";
					}
					break;
				}
			} 
            break;
    }  	
} 

GameDialogBox::~GameDialogBox() {
	for ( int i = 0; i < buttons.size(); i++ ) delete buttons[i];
	buttons.clear();
} 

string GameDialogBox::getInput(){
	return input;
}
