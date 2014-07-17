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
		image = new Gtk::Image(deck_.null());
	}
	else{
		//image = new Gtk::Image(deck_.image(card->getRank(), card->getSuit()));
		image = new Gtk::Image(deck_.image(TWO, SPADE));
	}

	std::cout << "HI" << std::endl;
	this->set_image(*image);
}


