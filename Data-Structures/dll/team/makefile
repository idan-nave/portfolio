# Compiler to use
CC=gcc

# Compiler flags
CFLAGS=-g -pedantic-errors -Wall -Wextra -ansi

# Source file paths
HEADER_PATH=-I/home/sahar/git/ds/dll/include

all: dll.out clean

./bin/dll.o: ./src/dll.c 
	$(CC) $(CFLAGS) -c $(HEADER_PATH) ./src/dll.c -o ./bin/dll.o
	
./bin/dll_test.o: ./test/dll_test.c
	$(CC) $(CFLAGS) -c $(HEADER_PATH) ./test/dll_test.c -o ./bin/dll_test.o
	
dll.out: ./bin/dll.o ./bin/dll_test.o
	$(CC) ./bin/dll.o ./bin/dll_test.o -o dll.out

clean: 
	rm ./bin/*.o
