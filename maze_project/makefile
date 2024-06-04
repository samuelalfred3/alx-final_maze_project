CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
LIBS = -lSDL2 -lSDL2_image -lm

SRCS = src/game.c src/input.c src/main.c src/map.c src/graphics.c src/textures.c
OBJS = $(SRCS:.c=.o)

INC_DIRS = -I inc -I /usr/include/SDL2

Maze: $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIRS) $(OBJS) -o $@ $(LIBS)

clean:
	rm -f $(OBJS) Maze

