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
all: queue.out valg

$(BPATH)queue.o: $(SPATH)queue.c
	$(CC) -c $(SPATH)queue.c $(CFLAGS) $(HPATH) -o $(BPATH)queue.o
$(BPATH)sll.o: $(SPATH)sll.c
	$(CC) -c $(SPATH)sll.c $(CFLAGS) $(HPATH) -o $(BPATH)sll.o
$(BPATH)queue_test.o: $(TPATH)queue_test.c
	$(CC) -c $(TPATH)queue_test.c $(CFLAGS) $(HPATH) -o $(BPATH)queue_test.o
queue.out: $(BPATH)queue.o $(BPATH)queue_test.o $(BPATH)sll.o
	$(CC) $(BPATH)queue.o $(BPATH)queue_test.o $(BPATH)sll.o -o queue.out

clear: 
	rm $(BPATH)*.o

run:
	./queue.out

valg:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./queue.out
