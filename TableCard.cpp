#include "TableCard.h"
#include "DeckGUI.h"
#include <iostream>

// Constructor for a table card
TableCard::TableCard(Card *card, DeckGUI deck){
	deck_ = deck;
	card_ = card;
	setTableCard(card);
}

// Destructor
TableCard::~TableCard(){}

// method to update the image on a card on the table
void TableCard::updateFace(Card *card){
	card_ = card;
	setTableCard(card);
}

// sets the image of the table card based on a given card
void TableCard::setTableCard(Card *card){
	if(card==NULL){
		this->set(Gdk::Pixbuf::create_from_file("img/nothing.png"));
	}
	else{
		this->set(deck_.image(card->getRank(), card->getSuit()));
	}
}

// accessor for the card of the table card
Card* TableCard::getCard(){
	return card_;
}
