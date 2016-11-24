CXX=g++
CXXFLAGS= -MMD -Wall

OBJECTS=main.o cell.o game.o controller.o view.o textdisplay.o gold.o dragonhoard.o potion.o character.o npc.o human.o dwarf.o elf.o orcs.o merchant.o dragon.o halfling.o status_effect.o atkboost.o atkwound.o defboost.o defwound.o pc.o drow.o goblin.o shade.o troll.o vampire.o generate.o posn.o

DEPENDS=${OBJECTS:.o=.d}

EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm *.o *.d cc3k
.PHONY: clean
