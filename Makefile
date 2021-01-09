CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=Board.o Building.o commandInput.o Dice.o Exception.o Game.o NonProperty.o Player.o Property.o main.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=watopoly

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
