CC=g++

OPTS=-std=c++11 

SYSLIBS= -L/usr/local/lib -L/usr/X11R6/lib \
	 -lGL -lGLU -lglut -lSOIL -lpthread

test:Battleship_test.cpp
	$(CC) Battleship_test.cpp -o battleship_test $(OPTS) $(SYSLIBS)

all: test
	
clean: 
	-rm -f battleship_test
