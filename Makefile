CC=g++
BIN=game.exe
CXXFLAGS=-Wall -Werror -pedantic -std=c++17  -Wno-missing-braces
INC=-Iinclude
LIB=-L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

SRCDIR=src
SOURCES  = $(wildcard $(SRCDIR)/*.cc)

.PHONY: all clean

all: BIN

BIN: SRC
	$(CC) $(SOURCES) -o $(BIN) $(CXXFLAGS) $(INC) $(LIB)

# On Linux use rm instead of del
clean:
	del $(BIN)