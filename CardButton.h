#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include "Card.h"
#include "DeckGUI.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// CardButton widget class that displays a card image and can be clicked
class CardButton : public Gtk::Button {
public:
	// Constructor and destructor
	CardButton(Card *card);
	virtual ~CardButton();

	// Mutator for card button; sets the card to be displayed on the button
	void setCardButton(Card *card);

	// Accessor for card displayed by the card button
	Card* getCard() { return card_; }
	
private:
	// Default constructor prohibited
	CardButton() {}

	// Private instance variables
	DeckGUI deck_;
	Card *card_;
};
#endif
