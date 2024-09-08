# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -Iinc
LDFLAGS = -lSDL2 -lSDL2_image -lm  # Added -lm for math library

# Source and object files
SRCS = src/game.c src/graphics.c src/input.c src/main.c src/map.c src/player.c src/ray.c src/texture.c src/window.c
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = maze_game

# Build target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Rule for building object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

