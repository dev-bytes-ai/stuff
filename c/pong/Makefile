# Makefile for Pong game

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -lncurses

# Output executable
TARGET = pong

# Source file
SRC = pong.c

# Default target
all: $(TARGET)

# Rule to build the game
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

# Clean up the build
clean:
	rm -f $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

