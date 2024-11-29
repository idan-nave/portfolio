# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -pedantic-errors -Wall -Wextra -ansi

# Header Path
HPATH = -I ./header

# Bin Path
BPATH = ./bin/

# src Path
SPATH = ./src/

# test Path
TPATH = ./test/

# Default target
all: cbuff.out run

$(BPATH)cbuff.o: $(SPATH)cbuff.c
	$(CC) -c $(SPATH)cbuff.c $(CFLAGS) $(HPATH) -o $(BPATH)cbuff.o
$(BPATH)cbuff_test.o: $(TPATH)cbuff_test.c
	$(CC) -c $(TPATH)cbuff_test.c $(CFLAGS) $(HPATH) -o $(BPATH)cbuff_test.o
cbuff.out: $(BPATH)cbuff.o $(BPATH)cbuff_test.o
	$(CC) $(BPATH)cbuff.o $(BPATH)cbuff_test.o -o cbuff.out

clear: 
	rm $(BPATH)*.o

run:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./cbuff.out