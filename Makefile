CC=g++

OPTS= -ansi -pedantic -Wall -Wextra -Wno-reorder -Wno-comment -Wno-unused-variable  -Wno-unused-parameter -Wno-unused-but-set-variable -std=c++11 

SYSLIBS= -L/usr/local/lib -L/usr/X11R6/lib \
	 -lGL -lGLU -lglut -lSOIL -lpthread

test:Battleship_test.cpp Cell.cpp Board.cpp 
	$(CC) Battleship_test.cpp Cell.cpp Board.cpp  -o battleship_test $(OPTS) $(SYSLIBS)

all: test
	
clean: 
	-rm -f battleship_test
