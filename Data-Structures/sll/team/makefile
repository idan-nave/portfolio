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

# Test Path
TPATH = ./test/

# Default target
.PHONY: valg clean

all: sll.out valg

$(BPATH)sll.o: $(SPATH)sll.c
	$(CC) -c $(SPATH)sll.c $(CFLAGS) $(HPATH) -o $(BPATH)sll.o
$(BPATH)sll_test.o: $(TPATH)sll_test.c
	$(CC) -c $(TPATH)sll_test.c $(CFLAGS) $(HPATH) -o $(BPATH)sll_test.o
sll.out: $(BPATH)sll.o $(BPATH)sll_test.o 
	$(CC) $(BPATH)sll.o $(BPATH)sll_test.o -o sll.out

$(BPATH)sll_adv.o: sll_adv.c
	$(CC) -c ./sll_adv.c $(CFLAGS) -o $(BPATH)sll_adv.o
sll_adv.out: $(BPATH)sll_adv.o
	$(CC) $(BPATH)sll_adv.o -o sll_adv.out

clear: 
	rm $(BPATH)*.o

run:
	./sll.out 

valg:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./sll.out
