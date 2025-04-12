# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Paths
SRC_DIR = src
OBJ_DIR = build
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/input_buffer.o \
       $(OBJ_DIR)/statement.o \
       $(OBJ_DIR)/meta_command.o \
       $(OBJ_DIR)/execute.o \
	   $(OBJ_DIR)/table.o

TARGET = db

.PHONY: all clean run test format

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each source file into build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the compiled binary with a test db
run: $(TARGET)
	./$(TARGET) mydb.db

# Remove compiled files and database
clean:
	rm -rf $(OBJ_DIR) $(TARGET) *.db

# Run tests (assuming you have RSpec configured)
test: $(TARGET)
	bundle exec rspec

# Format all C and header files using clang-format
format:
	clang-format -style=Google -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h
