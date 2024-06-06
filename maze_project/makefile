# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Output executable
TARGET = raycasting_game

# Libraries
SDL_LIB = -lSDL2 -lSDL2_image

# Make sure the obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Main target
all: $(OBJ_DIR) $(TARGET)

# Compile the target
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(SDL_LIB)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)

# Rebuild
rebuild: clean all

# Phony targets
.PHONY: all clean rebuild

