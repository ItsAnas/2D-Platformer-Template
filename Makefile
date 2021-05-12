CC=g++
BIN=game.exe
CXXFLAGS=-Wall -Werror -pedantic -std=c++17  -Wno-missing-braces
INC=-Iinclude
LIB=-L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

SOURCES= src/main.cc \
		src/player/player.cc \
		src/player/subplayer/subplayer.cc

.PHONY: all clean

all: BIN

BIN: SRC
	$(CC) $(SOURCES) -o $(BIN) $(CXXFLAGS) $(INC) $(LIB)

# On Linux use rm instead of del
clean:
	del $(BIN)