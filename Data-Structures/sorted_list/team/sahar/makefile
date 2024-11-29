# Compiler to use
CC=gcc

# Compiler flags
CFLAGS=-g -pedantic-errors -Wall -Wextra -ansi

# Source file paths
HEADER_PATH=-I/home/sahar/git/ds/dsl/include

all: sorted_list.out clean

./bin/dll.o: ../dll/src/dll.c 
	$(CC) $(CFLAGS) -c -I/home/sahar/git/ds/dll/include ../dll/src/dll.c -o ./bin/dll.o
./bin/sorted_list.o: ./src/sorted_list.c 
	$(CC) $(CFLAGS) -c $(HEADER_PATH) ./src/sorted_list.c -o ./bin/sorted_list.o
./bin/sorted_list_test.o: ./test/sorted_list_test.c
	$(CC) $(CFLAGS) -c $(HEADER_PATH) ./test/sorted_list_test.c -o ./bin/sorted_list_test.o
	
sorted_list.out: ./bin/dll.o ./bin/sorted_list.o ./bin/sorted_list_test.o
	$(CC) ./bin/dll.o ./bin/sorted_list.o ./bin/sorted_list_test.o -o sorted_list.out

clean: 
	rm ./bin/*.o
