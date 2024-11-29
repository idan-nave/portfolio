#include <stdlib.h>
#include  <stdio.h>
#include  <assert.h>

void print_arr (int *arr_to_prnt, int size)
{
	int i =0;
	for(; i<size; i++)
	{
		printf("%d,", arr_to_prnt[i]);
	}
	printf("\n");
}

void swap (int *a, int *b)
{
	int z=*a;
	*a=*b;
	*b=z;
}	

void swap_two_size_t (size_t *s_t_1, size_t *s_t_2)
{
	size_t z=*s_t_1;
	*s_t_1=*s_t_2;
	*s_t_2=z;
}

void swap_two_size_t_ptrs (size_t **s_t_1, size_t **s_t_2)
{
	size_t *z_ptr = *s_t_1;
	*s_t_1 = *s_t_2;
	*s_t_2 = z_ptr;
}

void del_arr (int *arr_to_del)
{
	free(arr_to_del);
	arr_to_del=NULL;
}

int * cp_arr (int *arr, int size)
{
	int* alloc_ptr;
	int i=0;
	alloc_ptr = (int*) malloc(size * sizeof(int));
	
	for(; i<size; i++)
	{
		alloc_ptr[i]=arr[i];
	}
	return alloc_ptr;
}	


int main ()
{
	//##########code to swap ints#########
	int x=1, y=4;
	printf("x initally was: %d, y initially was: %d\n", x,y);
	swap(&x,&y);	
	printf("x now: %d, y now: %d\n", x,y);
	
	//##########code to cp arr#########
	int arr[]={1,2,3,4,5};
	int* holder_copied_arr;
	holder_copied_arr = cp_arr(arr,5);
	
	printf("array was initially:\n");
	print_arr(arr,5);
	printf("copied array is:\n");
	print_arr(holder_copied_arr,5);
	
	del_arr(holder_copied_arr);
	
	
	//##########code to swap size_ts#########
	printf("#swap of size_ts by ref:#\n\n");
	size_t s1=1,s2=4;
	printf("s1 initally was: %zu, s2 initially was: %zu\n", s1,s2);
	swap_two_size_t(&s1,&s2);	
	printf("s1 now: %zu, s2 now: %zu\n", s1,s2);
	
	//##########code to swap size_ts-ptrs#########
	printf("swap of size_ts pointers only (no change of size_t should occur):#\n\n");
	size_t *s1_ptr = &s1 ,*s2_ptr = &s2;
	printf("s1_ptr initally was: %p, s2_ptr initially was: %p\n", s1_ptr,s2_ptr);
	swap_two_size_t_ptrs(&s1_ptr,&s2_ptr);	
	printf("s1_ptr  now: %p, s2_ptr  now: %p\n", s1_ptr,s2_ptr);
	printf("implications: s1 now: %zu, s2 now: %zu\n", s1,s2);
	
	//##########code to swap size_ts BY swap size_ts-ptrs Func#########
	printf("#swap of size_ts by swap size_ts-ptrs_Func:#\n\n");
	printf("s1_ptr initally was: %p, s2_ptr initially was: %p\n", s1_ptr,s2_ptr);
	swap_two_size_t(s1_ptr,s2_ptr);	
	printf("s1_ptr  now: %p, s2_ptr  now: %p\n", s1_ptr,s2_ptr);
	printf("implications: s1 now: %zu, s2 now: %zu\n", s1,s2);
	printf("#IT DID NOT WORKED BECAUSE THE ARGUMENTS PASSED TO THE 1ST SWAP FUNC ARE NOW ONE DEREFENENCD LEVEL IN (*)OF THE ORIGINAL S VARS#\n\n");
	
	//##########code to swap INTs with swap_size_ts#########
	printf("#swap INTs with swap_size_ts:#\n\n");
	printf("x initally was: %d, y initially was: %d\n", x,y);
	size_t casted_x=(size_t)(x); 
	size_t casted_y=(size_t)(y); 
	swap_two_size_t( &casted_x,&casted_y) 	;	
	//ERROR COMPILATION//swap_two_size_t( &X, &y) 	;	
	printf("x now: %zu, y now: %zu\n", casted_x,casted_y);
	
	return 0;
	
}
