CC=g++
BIN=game.exe
CXXFLAGS=-Wall -Werror -pedantic -std=c++17  -Wno-missing-braces
INC=-Iinclude -Isrc
LIB=-L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

SOURCES=$(wildcard src/*.cc)

.PHONY: all clean

all: BIN

BIN:
	$(CC) $(SOURCES) -o $(BIN) $(CXXFLAGS) $(INC) $(LIB)

# On Linux use rm instead of del
clean:
	del $(BIN)