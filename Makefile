CXX = g++
CXXFLAGS = -g -Wall -MMD `pkg-config gtkmm-2.4 --cflags`
LDFLAGS = `pkg-config gtkmm-2.4 --libs`
OBJECTS = Card.o Command.o Deck.o Game.o Player.o HumanPlayer.o ComputerPlayer.o CardHand.o GameView.o DeckGUI.o GameViewController.o subject.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} ${LDFLAGS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies
