CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -Iinclude
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/raytracer

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete"

# Full rebuild
rebuild: clean all

.PHONY: all run clean rebuild