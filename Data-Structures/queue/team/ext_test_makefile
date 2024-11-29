# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -pedantic-errors -Wall -Wextra -ansi

# Directories
SRC_DIR = ./src
EXT_TST_DIR = ./team/test
EXT_SRC_DIR = ./team/src
HDR_DIR = ./include
DBG_DIR = ./bin/debug
REL_DIR = ./bin/release
OBJ_DIR = ./obj

# Binary name
BIN_NAME = stack.out
DBG_NAME = stack_debug.out

# Source file paths
SRC_FILES = $(EXT_TST_DIR)/stack_test.c $(SRC_DIR)/stack.c
# Header file paths
HDR_FILES = $(HDR_DIR)/stack.h
# Object file paths
OBJ_FILES = $(OBJ_DIR)/stack_test.o $(OBJ_DIR)/stack.o

# Specify phony targets (targets that are not files)
.PHONY: all clean run_ext_test valg open

# Test using a Teamate test file:
all: clean $(DBG_DIR)/$(DBG_NAME) run_ext_test

$(DBG_DIR)/$(DBG_NAME): $(OBJ_FILES)
	@mkdir -p $(DBG_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

$(OBJ_DIR)/%.o: $(EXT_TST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -I$(HDR_DIR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -I$(HDR_DIR) -o $@

# Clean up object and binary directories
clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(REL_DIR)/*.out
	rm -rf $(DBG_DIR)/*.out

run_ext_test:
	$(DBG_DIR)/$(DBG_NAME)

valg:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes $(DBG_DIR)/$(DBG_NAME)

open:
	open $(EXT_TST_DIR)/stack_test.c
	open $(EXT_SRC_DIR)/stack.c
	open $(SRC_DIR)/stack.c
	open $(HDR_DIR)/stack.h

################# makefile - description ################
# $(OBJ_DIR)/%.o: This is the target pattern. It specifies that any object file in the OBJ_DIR directory can be generated using this rule. The % is a wildcard that matches any string.

# $(SRC_DIR)/%.c: This is the prerequisite pattern. It specifies that the corresponding source file (with the same name but .c extension) in the SRC_DIR directory is needed to build the target.

# $(CC) -c $(CFLAGS) $< -I$(HDR_DIR) -o $@: This is the recipe that defines how to build the target from the prerequisite. Here's what each part does:

# $(CC): Expands to the compiler (gcc in this case).
# -c: Indicates that the compiler should only compile and not link.
# $(CFLAGS): Compiler flags specified earlier.
# $<: Automatic variable representing the first prerequisite (source file).
# -I$(HDR_DIR): Specifies the include directory.
# -o $@: Automatic variable representing the target file (object file).