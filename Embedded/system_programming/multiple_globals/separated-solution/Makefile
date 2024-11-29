# vars
CC=gcc
# CFLAGS will be the options passed to the compiler. -pedantic-errors -Wall -Wextra -Werror -g
CFLAGS=-ansi -pedantic-errors -Wextra -Werror -g
#path of header

# Targets
all: file.o libfilelib.a mergedfoo.o mergedfoo2.o libfoo.so libfoo2.so dynamic.out static_dynamic.out

file.o: ./file.c  
	$(CC) -c -fpic file.c -o file.o	

# Static library	
libfilelib.a: ./file.o
	ar rcs libfilelib.a file.o
	
#stage 1+2	
mergedfoo.o: ./foo.c
	$(CC) -c -fpic foo.c -L. -lfilelib -o mergedfoo.o

#stage 1+2	
mergedfoo2.o: ./foo2.c
	$(CC) -c -fpic foo2.c -L. -lfilelib -o mergedfoo2.o
	
# Shared libraries		
libfoo.so : ./mergedfoo.o
	gcc -shared -o libfoo.so mergedfoo.o -L. -lfilelib 
	
libfoo2.so : ./mergedfoo2.o
	gcc -shared -o libfoo2.so mergedfoo2.o -L. -lfilelib

# Executables
dynamic.out : ./dynamic.c
	$(CC) dynamic.c -L. -Wl,-rpath=. -o dynamic.out -lfoo
		
static_dynamic.out: ./static_dynamic.c
	$(CC) static_dynamic.c -L. -o static_dynamic.out -lfilelib

clean:
	rm *.o *.a *.so *.out
