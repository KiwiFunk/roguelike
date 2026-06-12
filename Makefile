# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/roguelike

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(BUILDDIR)/main.o $(BUILDDIR)/game.o
	$(CC) $(CFLAGS) $^ -o $@

# Compile main.c
$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile game.c
$(BUILDDIR)/game.o: $(SRCDIR)/game.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
