# Makefile for Maze Project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Target executable
TARGET = maze_game

# Default rule
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) -lSDL2 -lSDL2_image

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean object files and executable
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Clean all generated files including the executable
fclean: clean

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re

