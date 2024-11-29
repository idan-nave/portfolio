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
all: vector.out run

$(BPATH)vector.o: $(SPATH)vector.c
	$(CC) -c $(SPATH)vector.c $(CFLAGS) $(HPATH) -o $(BPATH)vector.o
$(BPATH)vector_test.o: $(TPATH)vector_test.c
	$(CC) -c $(TPATH)vector_test.c $(CFLAGS) $(HPATH) -o $(BPATH)vector_test.o
vector.out: $(BPATH)vector.o $(BPATH)vector_test.o 
	$(CC) $(BPATH)vector.o $(BPATH)vector_test.o -o vector.out

clear: 
	rm $(BPATH)*.o

run:
	./vector.out
