#include "Deck.h"

Deck::Deck() {
	string ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	string suits[] = {"C", "S", "D", "H"};

	for (int i = 0; i < ranks.length(); i++) {
		for (int j = 0; j < suits.length(); j++) {
			string card = ranks[i].append(" ".append(suits[j]));
			_cards.push_back(card);
		}
	}
}