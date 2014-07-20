#include "CardButton.h"
#include "DeckGUI.h"
#include <iostream>

// Construct a card button 
CardButton::CardButton(Card *card){
	card_ = card;
	setCardButton(card);
}

// Destruct card button; delete card from memory
CardButton::~CardButton() {
	delete card_;
}

// Mutator for card button
void CardButton::setCardButton(Card *card){
	card_ = card;

	// Set the image of the card using the deck GUI
	Gtk::Image *image;
	if (card == NULL) {
		image = new Gtk::Image(Gdk::Pixbuf::create_from_file("img/nothing.png"));
		set_sensitive(false);		// If there is no card, then make button unclickable
	} 
	else {
		image = new Gtk::Image(deck_.image(card->getRank(), card->getSuit()));
		set_sensitive(true);
	}

	this->set_image(*image);
}
