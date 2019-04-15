CXX = g++
CXXFLAGS = -g -Wall -pedantic -std=c++17

Yahtzee: game.o yahtzee.o factory.o ruletypes.o scoresheet.o rule.o diceroll.o
	${CXX} ${CXXFLAGS} -o Yahtzee game.o yahtzee.o factory.o ruletypes.o scoresheet.o rule.o diceroll.o

game.o:

yahtzee.o:

factory.o:

ruletypes.o:

scoresheet.o:

rule.o:

diceroll.o:
