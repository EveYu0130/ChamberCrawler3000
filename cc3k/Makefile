CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k
OBJECTS = main.o cell.o textdisplay.o character.o dragon.o drow.o dwarf.o elf.o enemy.o goblin.o halfling.o human.o item.o merchant.o orcs.o player.o potatk.o potdef.o pothp.o potion.o shade.o treasure.o troll.o vampire.o floor.o doorway.o floortile.o hwall.o passage.o stair.o vwall.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
