# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -pedantic-errors -Wall -Wextra -ansi

# Targets
all: print.o libprintlib.a shared1.o shared2.o libfoo.so libfoo2.so implicit_linkage.out explicit_linkage.out

print.o: ./print.c  
	$(CC) -c -fpic print.c -o print.o	

# Static library	
libprintlib.a: ./print.o
	ar rcs libprintlib.a print.o
	
#stage 1+2	
shared1.o: ./foo.c
	$(CC) -c -fpic foo.c -L. -lprintlib -o shared1.o

#stage 1+2	
shared2.o: ./foo2.c
	$(CC) -c -fpic foo2.c -L. -lprintlib -o shared2.o
	
# Shared libraries		
libfoo.so: ./shared1.o
	gcc -shared -o libfoo.so shared1.o -L. -lprintlib 
	
libfoo2.so: ./shared2.o
	gcc -shared -o libfoo2.so shared2.o -L. -lprintlib

# Executables
implicit_linkage.out: ./implicit.c
	$(CC) $(CFLAGS) implicit.c -L. -Wl,-rpath=. -o implicit_linkage.out -lfoo -lfoo2

explicit_linkage.out: ./explicit.c
	$(CC) $(CFLAGS) explicit.c -L. -o explicit_linkage.out -lprintlib

clean:
	rm *.o *.a *.so *.out
