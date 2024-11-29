# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -pedantic-errors -Wall -Wextra -ansi

# Directories
SRC_DIR = ./src
TST_DIR = ./test
HDR_DIR = ./include
DBG_DIR = ./bin/debug
REL_DIR = ./bin/release
OBJ_DIR = ./obj
LIB_DIR = ./lib

# Dependencies
DEP_DIR = ../stack/lib # stack.a library is one directory above
DEP_LIB = stack
DEP_HDR = ../stack/include

# Binary name
BIN_NAME = min_stack.out
# Library name
LIB_NAME = libmin_stack.a

# Source file paths
SRC_FILES = $(TST_DIR)/min_stack_test.c $(SRC_DIR)/min_stack.c
# Header file paths
HDR_FILES = $(HDR_DIR)/min_stack.h
# Object file paths
OBJ_FILES = $(OBJ_DIR)/min_stack_test.o $(OBJ_DIR)/min_stack.o

# Specify phony targets (targets that are not files)
.PHONY: all clean run valg open run_ext_test archive

all: clean $(REL_DIR)/$(BIN_NAME) archive run

$(REL_DIR)/$(BIN_NAME): $(OBJ_FILES)
	@mkdir -p $(REL_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -L$(DEP_DIR) -l$(DEP_LIB) -o $@

$(OBJ_DIR)/%.o: $(TST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -I$(HDR_DIR) -I$(DEP_HDR) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -I$(HDR_DIR) -I$(DEP_HDR) -o $@


# Clean up object and binary directories
clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(REL_DIR)/*.out
	rm -rf $(DBG_DIR)/*.out
	rm -rf $(LIB_DIR)/*.a

archive: $(OBJ_DIR)/min_stack.o
	@mkdir -p $(LIB_DIR)
	ar rcs $(LIB_DIR)/$(LIB_NAME) $(OBJ_DIR)/min_stack.o

run:
	$(REL_DIR)/$(BIN_NAME)

valg:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes $(REL_DIR)/$(BIN_NAME)

open:
	open $(TST_DIR)/min_stack_test.c
	open $(SRC_DIR)/min_stack.c
	open $(HDR_DIR)/min_stack.h

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