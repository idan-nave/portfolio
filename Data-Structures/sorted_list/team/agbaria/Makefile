#compiler
CC = gcc 

#flags 
#FLAGS = -g -ansi -pedantic-errors -Wall -Wextra -Werror
FLAGS = -ansi

#Header path
VPATH = -I/home/ahmad_agbaria/git/ds/sorted_list/include
 

all: ./sorted_list.out
	
./bin/dll.o: ../dll/src/dll.c 
	$(CC) -c ../dll/src/dll.c $(FLAGS) $(VPATH) -o ./bin/dll.o

./bin/sorted_list.o: ./src/sorted_list.c 
	$(CC) -c ./src/sorted_list.c $(FLAGS) $(VPATH) -o ./bin/sorted_list.o

./bin/sorted_list_test.o: ./test/sorted_list_test.c 
	$(CC) -c ./test/sorted_list_test.c $(FLAGS) $(VPATH) -o ./bin/sorted_list_test.o
	
./sorted_list.out: ./bin/sorted_list.o ./bin/sorted_list_test.o ./bin/dll.o
	$(CC) ./bin/dll.o ./bin/sorted_list.o ./bin/sorted_list_test.o -o ./sorted_list.out
 
clean:
	rm -rf ./bin/*.o
