# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -pedantic-errors -Wall -Wextra -ansi

# Targets
all: disable_ASLR pic_objects libmemory_mapping.so implicit_linkage.out enable_ASLR

disable_ASLR:
	echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

# Dynamic library - debug flag is important fot mapping
pic_objects: ../memory_mapping.c ../memory_mapping_more_code.c
	$(CC) $(CFLAGS) -c -fpic ../memory_mapping.c -L. -o memory_mapping.o
	$(CC) $(CFLAGS) -c -fpic ../memory_mapping_more_code.c -L. -o memory_mapping_more_code.o
	
# Shared library		
libmemory_mapping.so: ./memory_mapping.o ./memory_mapping_more_code.o
	gcc -shared -o libmemory_mapping.so memory_mapping.o memory_mapping_more_code.o

# Executable - no-pie flag is important for mapping
implicit_linkage.out: ./implicit.c
	$(CC) $(CFLAGS) -no-pie implicit.c -L. -Wl,-rpath=. -o implicit_linkage.out -lmemory_mapping

enable_ASLR:
	echo 2 | sudo tee /proc/sys/kernel/randomize_va_space

clean:
	rm *.o *.a *.so *.out
