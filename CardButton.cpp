#include "CardButton.h"
#include "DeckGUI.h"
#include <iostream>


CardButton::CardButton(Card *card, DeckGUI deck){
	deck_ = deck;
	card_ = card;
	setCardButton(card);
}

CardButton::~CardButton(){}

void CardButton::updateFace(Card *card){
	card_ = card;
	setCardButton(card);
}

void CardButton::setCardButton(Card *card){
	Gtk::Image *image;
	if(card == NULL){
		image = new Gtk::Image(Gdk::Pixbuf::create_from_file("img/nothing.png"));
		set_sensitive(false);
	}
	else{
		image = new Gtk::Image(deck_.image(card->getRank(), card->getSuit()));
		set_sensitive(true);
	}

	this->set_image(*image);
}

Card* CardButton::getCard(){
	return card_;
}
