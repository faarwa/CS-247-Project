#include "GameDialogBox.h"
#include <gtkmm/stock.h>
#include <iostream>

// constructor for the dialog box used to initialize player types at the start of a game
GameDialogBox::GameDialogBox( Gtk::Window & parentWindow, string title) : Dialog( title, parentWindow, true, true ) {
	// options for the user to choose from
	vector<string> messages;
	messages.push_back( "Human" );
	messages.push_back( "Computer" );
	
	set_border_width( 150 );
	
	Gtk::VBox* contentArea = this->get_vbox();
	
	// add radio buttons for each option to the dialog box
	for ( int i = 0; i < messages.size(); i++ ) {
		buttons.push_back( Gtk::manage( new Gtk::RadioButton( group, messages[i] ) ) );
		contentArea->add( *buttons[i] );
	}
	
	// Make the first button the initial active choice.
	buttons[0]->set_active();
	
	// Add a standard "ok" button with the appropriate responses when clicked.
    Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();
	
    // Wait for a response from the dialog box.
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            for ( int i = 0; i < messages.size(); i++ ) {
				if ( buttons[i]->get_active() ) {
					// set the input value based on which radio button was selected
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

// destructor for the dialog box
GameDialogBox::~GameDialogBox() {
	for ( int i = 0; i < buttons.size(); i++ ) delete buttons[i];
	buttons.clear();
} 

// accessor for the input, used in Game to initialize players with the correct types
string GameDialogBox::getInput(){
	return input;
}
