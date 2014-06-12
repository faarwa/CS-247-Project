CXX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = Card.o Command.o Deck.o Game.o Player.o HumanPlayer.o ComputerPlayer.o CardHand.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}	# reads the .d files and reruns dependencies