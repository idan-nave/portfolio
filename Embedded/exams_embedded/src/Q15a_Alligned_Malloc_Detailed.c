/* `aligned_malloc` and `aligned_free` functions that allocate memory with a specified alignment.
*/

#include <stdio.h>
#include <stdlib.h>  // Include stdlib for malloc and free
#include <stdint.h>  // Include stdint for uintptr_t

#define WORD_SIZE 8

typedef struct
{
    void* ptr;
    size_t align;
} align_ptr;

void* aligned_malloc(size_t size, size_t align)
{
    size_t total_size = size + align + sizeof(align_ptr);
    /* Allocate memory with extra space for alignment and metadata  */    
    void* raw_ptr = malloc(total_size);
    if (raw_ptr == NULL)
    {
        return NULL; // Allocation failed
    }

    if (align == 0 || (align & (align - 1)) != 0)
    {
        // Alignment must be a power of 2
        return NULL;
    }

    uintptr_t aligned_ptr = (uintptr_t)(raw_ptr) + sizeof(align_ptr) + align;
    aligned_ptr &= ~(align - 1); // Align the pointer

    align_ptr* meta_ptr =
            (align_ptr*)((uintptr_t)(aligned_ptr) - sizeof(align_ptr));
    meta_ptr->ptr = (void*)aligned_ptr;
    meta_ptr->align = align;

    return (void*)aligned_ptr;
}

void aligned_free(void* ptr)
{
    if (ptr == NULL)
    {
        return; // Nothing to free
    }

    align_ptr* meta_ptr = (align_ptr*)((uintptr_t)(ptr) - sizeof(align_ptr));
    free(meta_ptr->ptr); // Free the raw memory
}

int main()
{
    int int_tester = 42;
    char c_tester = 'A';

    int* aligned_ptr = aligned_malloc(sizeof(int), WORD_SIZE);
    char* offby4_ptr = aligned_malloc(sizeof(char), 4);

    *aligned_ptr = int_tester;
    *offby4_ptr = c_tester;

    printf("inside %p you can find %d\n", (void*)aligned_ptr, *aligned_ptr);
    printf("inside %p you can find %c\n", (void*)offby4_ptr, *offby4_ptr);

    aligned_free(aligned_ptr);
    aligned_free(offby4_ptr);

    return 0;
}

/*
. Checked if the alignment is a power of 2 before proceeding with `aligned_malloc`.

. Aligned the pointer by masking off the lower bits.

. `aligned_free` function to frees the raw memory allocated by `aligned_malloc`*/