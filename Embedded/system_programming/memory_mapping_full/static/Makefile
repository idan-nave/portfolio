# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -pedantic-errors -Wall -Wextra -ansi

# Targets
all: disable_ASLR non_pic_objects libmapping.a static.out enable_ASLR

disable_ASLR:
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

non_pic_objects: ../memory_mapping.c ../memory_mapping_more_code.c
	$(CC) -c -fpic ../memory_mapping.c -o memory_mapping.o	
	$(CC) -c -fpic ../memory_mapping_more_code.c -o memory_mapping_more_code.o	

# Static library	
libmapping.a: ./memory_mapping.o ./memory_mapping_more_code.o
	ar rcs libmapping.a memory_mapping.o memory_mapping_more_code.o

static.out: ./static.c
	$(CC) $(CFLAGS) static.c -L. -o static.out -lmapping

enable_ASLR:
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space

clean:
	rm *.o *.a *.so *.out
