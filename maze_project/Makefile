# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# Linker flags
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_image

# Directories
SRC_DIR = src
INC_DIR = inc

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Executable
EXEC = maze_game

# Build target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Remove all generated files
fclean: clean

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re

