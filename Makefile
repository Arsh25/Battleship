 CC=g++

OPTS= -ansi -pedantic -Wall -Wextra -Wno-comment -Wno-unused-variable  -Wno-unused-parameter -Wno-unused-but-set-variable -std=c++11 
DEBUG= -g -v -da -Q 

SYSLIBS= -L/usr/local/lib -L/usr/X11R6/lib \
	  -lSOIL -lglut -lGLU -lGL -lpthread -lm

#SYSLIBS= -L/usr/local/lib  \
#	 -lpthread -lGL -lGLU -lglut -lSOIL


test:Battleship_test.cpp Cell.cpp Board.cpp 

	$(CC) Battleship_test.cpp Cell.cpp Board.cpp  -O -o battleship_test $(OPTS) $(SYSLIBS)

all: test
	
clean: 
	-rm -f battleship_test
