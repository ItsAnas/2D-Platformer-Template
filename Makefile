CC=g++
BIN=game.exe
SRC=main.cc
CXXFLAGS=-Wall -Werror -pedantic -std=c++17  -Wno-missing-braces
INC=-Iinclude
LIB=-L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

all: BIN

BIN:
	$(CC) $(SRC) -o $(BIN) $(CXXFLAGS) $(INC) $(LIB)


# On Linux use rm instead of del
clean:
	del $(BIN)