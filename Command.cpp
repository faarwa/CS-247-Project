#include "Command.h"
#include "Deck.h"
#include <cassert>
#include <sstream>
using namespace std;

void handleCommand(Type type) {
	if (type == QUIT) {
		exit(0);
	} else if (type == DECK) {
		Deck deck = Deck();
		deck.print();
	}
}

istream &operator>>(istream &in, Command &c){
	c.type = BAD_COMMAND;
	
	string cmd;
	in >> cmd;
	
	if (cmd == "play") {
		c.type = PLAY;
		in >> c.card;
	} else if (cmd == "discard") {
		c.type = DISCARD;
		in >> c.card;
	} else if (cmd == "deck") {
		c.type = DECK;
	} else if (cmd == "quit") {
		c.type = QUIT;
	} else if (cmd == "ragequit") {
		c.type = RAGEQUIT;
	}
	
	assert(!in.fail() && c.type != BAD_COMMAND);

	handleCommand(c.type);
	
	return in;
}