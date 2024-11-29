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
DEP_DIR = ../uid/lib # uid.a library is one directory above
DEP_LIB = uid
DEP_HDR = ../uid/include

# Binary name
BIN_NAME = fsa.out
# Library name
LIB_NAME = libfsa.a

# Source file paths
SRC_FILES = $(TST_DIR)/fsa_test.c $(SRC_DIR)/fsa.c
# Header file paths
HDR_FILES = $(HDR_DIR)/fsa.h
# Object file paths
OBJ_FILES = $(OBJ_DIR)/fsa_test.o $(OBJ_DIR)/fsa.o

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

archive: $(OBJ_DIR)/fsa.o
	@mkdir -p $(LIB_DIR)
	ar rcs $(LIB_DIR)/$(LIB_NAME) $(OBJ_DIR)/fsa.o

run:
	$(REL_DIR)/$(BIN_NAME)

valg:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes $(REL_DIR)/$(BIN_NAME)

open:
	open $(TST_DIR)/fsa_test.c
	open $(SRC_DIR)/fsa.c
	open $(HDR_DIR)/fsa.h

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