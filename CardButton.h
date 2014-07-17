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

class CardButton : public Gtk::Button {
public:
	CardButton(Card *card, DeckGUI deck);
	virtual ~CardButton();
	void updateFace(Card *card);
	void setCardButton(Card *card);
	
private:
	DeckGUI deck_;
	Card *card_;
};
#endif
