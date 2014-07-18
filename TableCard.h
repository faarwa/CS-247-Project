#ifndef TABLE_CARD_H
#define TABLE_CARD_H
#include <gtkmm/image.h>
#include "Card.h"
#include "DeckGUI.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class TableCard : public Gtk::Image {
public:
	TableCard(Card *card, DeckGUI deck);
	virtual ~TableCard();
	void updateFace(Card *card);
	void setTableCard(Card *card);
	Card* getCard();
	
private:
	DeckGUI deck_;
	Card *card_;
};
#endif
