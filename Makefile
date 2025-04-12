# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Paths
SRC_DIR = src
OBJ_DIR = build

# Object files
OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/input_buffer.o \
       $(OBJ_DIR)/statement.o \
       $(OBJ_DIR)/meta_command.o \
       $(OBJ_DIR)/execute.o \
       $(OBJ_DIR)/table.o \
       $(OBJ_DIR)/cursor.o

TARGET = db

.PHONY: all clean run test format

# Default target
all: $(TARGET)

# Final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Recompile .o files if .c or .h files they depend on change
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c \
                   $(SRC_DIR)/input_buffer.h \
                   $(SRC_DIR)/statement.h \
                   $(SRC_DIR)/meta_command.h \
                   $(SRC_DIR)/execute.h \
                   $(SRC_DIR)/table.h \
                   $(SRC_DIR)/common.h \
                   $(SRC_DIR)/cursor.h

$(OBJ_DIR)/input_buffer.o: $(SRC_DIR)/input_buffer.c $(SRC_DIR)/input_buffer.h
$(OBJ_DIR)/statement.o:    $(SRC_DIR)/statement.c $(SRC_DIR)/statement.h $(SRC_DIR)/common.h
$(OBJ_DIR)/meta_command.o: $(SRC_DIR)/meta_command.c $(SRC_DIR)/meta_command.h $(SRC_DIR)/input_buffer.h
$(OBJ_DIR)/execute.o:      $(SRC_DIR)/execute.c $(SRC_DIR)/execute.h $(SRC_DIR)/common.h $(SRC_DIR)/table.h
$(OBJ_DIR)/table.o:        $(SRC_DIR)/table.c $(SRC_DIR)/table.h $(SRC_DIR)/common.h
$(OBJ_DIR)/cursor.o:       $(SRC_DIR)/cursor.c $(SRC_DIR)/cursor.h $(SRC_DIR)/table.h


# Generic compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the compiled binary with a test db
run: $(TARGET)
	./$(TARGET) mydb.db

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET) *.db

# Run tests (RSpec)
test: $(TARGET)
	bundle exec rspec

# Format source files
format:
	clang-format -style=Google -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h
