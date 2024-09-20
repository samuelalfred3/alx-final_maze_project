CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic `sdl2-config --cflags`
LDFLAGS = -lm `sdl2-config --libs`
SRC = $(wildcard ./src/*.c)
OUTPUT = maze_game

.PHONY: build run clean

build:
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OUTPUT)

run: build
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)

