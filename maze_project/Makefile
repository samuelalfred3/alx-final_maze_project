CC := gcc
CFLAGS := -Wall -Wextra -Iinc -I/usr/include/SDL2
LDFLAGS := -lSDL2 -lSDL2_image -lm

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET := $(BINDIR)/maze

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

