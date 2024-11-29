# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -pedantic-errors -Wall -Wextra -ansi

#Header path
HEADER_PATH = /home/dimerda/Desktop/git/ds/sorted_list/include
sorted_list_C_PATH = /home/dimerda/Desktop/git/ds/sorted_list/src

DLL_H_PATH = /home/dimerda/Desktop/git/ds/dll/include
DLL_C_PATH = /home/dimerda/Desktop/git/ds/dll/src


.PHONY: all clean


all: SORTED_LIST.out

SORTED_LIST.out: sorted_list.o sorted_list_test.o dll.o
	$(CC) $(CFLAGS) sorted_list.o sorted_list_test.o dll.o -o SORTED_LIST.out

sorted_list.o: ./src/sorted_list.c ./include/sorted_list.h $(DLL_H_PATH)/dll.h
	$(CC) $(CFLAGS) -I$(HEADER_PATH) -I$(DLL_H_PATH) -c ./src/sorted_list.c -o sorted_list.o

sorted_list_test.o: ./test/sorted_list_test.c ./include/sorted_list.h $(DLL_H_PATH)/dll.h
	$(CC) $(CFLAGS) -I$(HEADER_PATH) -I$(DLL_H_PATH) -c ./test/sorted_list_test.c -o sorted_list_test.o
	
dll.o: $(DLL_C_PATH)/dll.c
	$(CC) $(CFLAGS) -I$(DLL_H_PATH) -c $(DLL_C_PATH)/dll.c -o dll.o
	
clean:
	rm ./*.o
