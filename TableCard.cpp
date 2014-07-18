#include "TableCard.h"
#include "DeckGUI.h"
#include <iostream>


TableCard::TableCard(Card *card, DeckGUI deck){
	deck_ = deck;
	card_ = card;
	setTableCard(card);
}

TableCard::~TableCard(){}

void TableCard::updateFace(Card *card){
	card_ = card;
	setTableCard(card);
}

void TableCard::setTableCard(Card *card){
	if(card==NULL){
		this->set(deck_.null());
	}
	else{
		this->set(deck_.image(card->getRank(), card->getSuit()));
	}
}

Card* TableCard::getCard(){
	return card_;
}
