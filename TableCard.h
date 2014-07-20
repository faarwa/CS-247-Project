#ifndef TABLE_CARD_H
#define TABLE_CARD_H
#include <gtkmm/image.h>
#include "Card.h"
#include "DeckGUI.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

// class declaration for a table card
class TableCard : public Gtk::Image {
public:
	TableCard(Card *card, DeckGUI deck);	// Constructor for a table card
	virtual ~TableCard();			// destructor
	void updateFace(Card *card);		// method to update the image on a table card
	void setTableCard(Card *card);		// mutator for the card of a table card
	Card* getCard();			// accessor for the card of the table card
	
private:
	DeckGUI deck_;				// private data member deck gui used to set the image
	Card *card_;				// private data member card of the table card
};
#endif
