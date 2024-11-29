# Idan Nave, HRD32
# A Generic makefile to manage the project's build process
PROJ_NAME = $(notdir $(shell pwd))

###############################################################################
####################### Project Dirs, Files, Dependencies #####################
###############################################################################

# Proj dependencies lists (PROJ_DEPS is read from a file)
PROJ_DEPS 	:= $(shell cat ./lib/lib_dep)
DEP_DIRS 	= $(foreach Proj,$(PROJ_DEPS),../$(Proj))
DEP_MAKES	= $(foreach Dir,$(DEP_DIRS), $(Dir)/Makefile)
DEP_LIBS	= $(foreach Dir,$(DEP_DIRS), $(wildcard $(Dir)/lib/*.so))
DEP_INCS 	= $(foreach Dir,$(DEP_DIRS), $(Dir)/include)

# Proj Directories
TREE = $(INC_DIRS) $(SRC_DIRS) $(OBJ_DIR) $(LIB_DIR) $(TST_DIR) $(DBG_DIR) $(REL_DIR)
INC_DIRS 	=  $(API_INC_DIR) $(DEP_INCS)
API_INC_DIR = ./include
API_SRC_DIR = ./src
TST_SRC_DIR = ./test
SRC_DIRS 	=  $(API_SRC_DIR) $(TST_SRC_DIR)
OBJ_DIR 	= ./obj
LIB_DIR 	= ./lib
BIN_DIR		= ./bin
DBG_DIR 	= $(BIN_DIR)/debug
REL_DIR 	= $(BIN_DIR)/release

# Proj Files (auto listing using wildcards)
API_SRCS 	= $(foreach C,$(API_SRC_DIR),$(wildcard $(C)/*.c))
TST_SRCS 	= $(foreach C,$(TST_SRC_DIR),$(wildcard $(C)/*.c))
SRCS 		= $(API_SRCS) $(TST_SRCS)
INCS 		= $(foreach Dir,$(INC_DIRS),$(wildcard $(Dir)/*.h))

# Pattern substitution on a list of SRCS
API_OBJS 	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(API_SRCS)))
TST_OBJS 	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(TST_SRCS)))
OBJS 		= $(API_OBJS) $(TST_OBJS)
LIB 		= $(LIB_DIR)/lib$(PROJ_NAME).so
BIN 		= $(REL_DIR)/$(PROJ_NAME).out
TST_BIN 	= $(DBG_DIR)/$(PROJ_NAME)_dbg.out

# Transformation applied to the $(OBJS) lists. It means "replace the .o extension with .d for each item in the $(OBJS) lists."
DEPS 		= $(API_OBJS:.o=.d) $(TST_OBJS:.o=.d) 

###############################################################################
########################## Project Building Parameters ########################
###############################################################################

# compilation params
CC 				= gcc
ERR_FLAGS 		= -pedantic-errors -Wall -Wextra -ansi
#enable debug info
DBG_COMP_FLAGS 	= -g
#disable debugging info & asserts
REL_COMP_FLAGS 	= -DNDEBUG
# encode make rules for the .h dependencies with -MMD	
INC_FLAGS 		= $(foreach Dir,$(INC_DIRS),-I$(Dir)) -MMD

# linking params
DEP_LDFLAGS 	= $(foreach Lib,$(DEP_LIBS),-L$(dir $(Lib)) -l$(patsubst lib%.so,%,$(notdir $(Lib))) -Wl,-rpath,$(dir $(Lib)))
API_LDFLAGS 	= -L$(dir $(LIB)) -l$(PROJ_NAME) -Wl,-rpath,$(dir $(LIB))

# Final Build Flags
DBG_CFLAGS 		= $(DBG_COMP_FLAGS) $(ERR_FLAGS) $(INC_FLAGS)
TST_CFLAGS 		= $(DBG_COMP_FLAGS) $(ERR_FLAGS) -I$(API_INC_DIR) -MMD
REL_CFLAGS 		= $(REL_COMP_FLAGS) $(ERR_FLAGS) $(INC_FLAGS)
#no optimization, non-PIE executable
DBG_LDFLAGS 	= -no-pie -O0
#Max optimization for release
REL_LDFLAGS 	= -O3

###############################################################################
############################ Buildig Process Targets ##########################
###############################################################################
all: clean build_deps validate_deps build_objs build_shared_lib build_bin #test distribute #enable_ASLR
############################## Dependencies Targets ###########################

# Run make for each dependency Makefile
build_deps: $(DEP_MAKES)
	@echo "inside $(DEP_DIRS) Building $(words $(DEP_DIRS)) Dependency directories: $(DEP_DIRS)"
	@for Makefile in $(DEP_MAKES); do \
		echo "Building $$Makefile"; \
		$(MAKE) -C $$(dirname $$Makefile); \
	done

# Validate that all dependencies are built
validate_deps: build_deps
	@for lib in $(DEP_LIBS); do \
		if [ ! -e "$$lib" ]; then \
			echo "Error: $$lib not found. No Dependencies built!"; \
			exit 1; \
		fi; \
		done
-include $(DEPS)

################################# Project Targets #############################

build_objs: $(OBJS)
./obj/$(PROJ_NAME).o: ./src/$(PROJ_NAME).c
	@echo "Building: $@"
	$(CC) -c -fpic $(DBG_CFLAGS) -o $@ $< $(DEP_LDFLAGS)
./obj/$(PROJ_NAME)_test.o: ./test/$(PROJ_NAME)_test.c
	@echo "Building: $@"
	$(CC) -c -fpic $(TST_CFLAGS) -o $@ $<
# ./obj/dll.o: ./src/dll.c
# ./obj/dll_test.o: ./test/dll_test.c
# $(OBJ_DIR)/%.o: $(API_SRC_DIR)/%.c
# $(OBJ_DIR)/%.o: $(TST_SRC_DIR)/%.c

build_shared_lib: $(LIB)
$(LIB): $(API_OBJS)
	@echo "Building: $@"
	$(CC) -shared -o $@ $^ $(DEP_LDFLAGS)

build_bin: $(TST_BIN) $(BIN) 
$(TST_BIN): $(TST_OBJS) $(LIB)
	@echo "Building: $@"
	$(CC) $(DBG_CFLAGS) $(DBG_LDFLAGS) -o $@ $< $(API_LDFLAGS)
$(BIN): $(TST_OBJS) $(LIB)
	@echo "Building: $@"
	$(CC) $(REL_CFLAGS) $(REL_LDFLAGS) -o $@ $< $(API_LDFLAGS)

test: $(TST_BIN)
	@echo "Running: $@"
	$(TST_BIN)

# non-targetfile rules
.PHONY: all clean distribute diff

# perform valgrind analysis
valg:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes $(TST_BIN)

# Clean up makable files
clean: tree
	rm -rf $(OBJ_DIR)/*.o
# .d files will be kept for optimized future build	
	rm -rf $(REL_DIR)/*.out
	rm -rf $(DBG_DIR)/*.out
	rm -rf $(LIB_DIR)/*.a
	rm -rf $(LIB_DIR)/*.so

# Gen. directories tree
tree:
	@mkdir -p $(TREE)
# -p flag ensures that directories are created as needed, without causing an error if they already exist.

# View code files
view:
	@for File in $(SRCS) $(INCS); do \
	    echo "Opening $$File"; \
	    open "$$File"; \
	done 
# $$File tells Make to pass the value of the File variable to the shell without interpreting it as a Makefile variable

disable_ASLR:
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
enable_ASLR:
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space


# prepare an archive of source code
distribute:
	rm -rf ./*.tgz
	tar zcvf $(PROJ_NAME)_dist.tgz $(API_INC_DIR) $(API_SRC_DIR) $(TST_SRC_DIR) $(LIB_DIR) $(BIN_DIR)

# prints git's changelog (@ silences printing if needed)
changelog:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	git diff --stat