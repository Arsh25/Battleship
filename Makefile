COMPILER=g++

DIRS=-I/usr/local/include -L/usr/local/lib

SOIL_DIR=SOIL
SOIL=$(SOIL_DIR)/stb_image_aug.c $(SOIL_DIR)/SOIL.c

ifeq ($(shell uname),Darwin)
	OS_GL=-framework OpenGL -lGLEW -framework GLUT
else
	OS_GL=-lGL -lGLU -lglut -lGLEW
endif

PTHREAD=-lpthread

LIB= $(PTHREAD) $(OS_GL)

CFLAGS=-O0 -Wall -Wno-deprecated-declarations -Wno-unused-variable -std=c++11 -ggdb -Wl,--as-needed

all: battleship

battleship: Battleship_test.cpp Cell.cpp Board.cpp $(SOIL)
	$(COMPILER) $^ $(LIB) $(CFLAGS) $(DIRS) -o $@

clean:
	rm -f battleship battleship.exe
