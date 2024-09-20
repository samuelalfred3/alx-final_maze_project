CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lm
SRC = ./src/*.c
HEADERS = ./headers/*.h
OUTPUT = maze_game

build: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OUTPUT)

run: build
	./$(OUTPUT)

clean:
	rm -f $(OUTPUT)

.PHONY: build run clean

