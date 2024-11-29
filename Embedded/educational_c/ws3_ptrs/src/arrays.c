#include <stdlib.h>
#include  <stdio.h>
#include  <assert.h>

void ex7 ()
{
	int *p = (int*)17;
	printf("%d\n", (int)(long)(p+8));
}

void ex8 ()
{
	
	const char * str1 = NULL;
	char const * str2;
	char* const str3 = NULL;
	char* str4 = NULL;
	char* const str5;
	
	str1 = str2;
	str2 = str3;
	str4 = str3;
	str3 = str4;
	str2 = str4;
	str4 = str2;
	str5 = str4;
	
	//printf("%d\n", (int)(long)(p+8));
}

void print_arr_char (int *arr_to_prnt, int size)
{
	int i =0;
	for(; i<size; i++)
	{
		printf("%d,", arr_to_prnt[i]);
	}
	printf("\n");
}



int main ()
{
	//##########code to swap ints#########
	int x=1, y=4;
	printf("x initally was: %d, y initially was: %d\n", x,y);
	ex7 ();
	ex8 ();
}
