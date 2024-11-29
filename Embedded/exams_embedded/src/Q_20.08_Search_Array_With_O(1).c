/*QUIZ 18 - ATTEMPT TO LOCATE AN INT INSIDE A GIVEN INT ARRAY IN O(1)*/

/*the idea is to use xor operation with (num, arr[i]):
If you XOR an integer with a bitmask where all the bits are 0 except for the bit you want to clear (which is set to 1), it will effectively clear the specified bit.
so xoring a number with itself will result in 0.

*/

#include <stddef.h> /*size_t*/
#include <stdio.h> /*size_t*/

int FindNumInArrayEfficiently (size_t num, size_t *arr, size_t len)
{
	size_t i = 0;
	size_t is_found = 0xFFFFFFFFFFFFFFFF;
	while(i < len)
	{
		is_found *= (arr[i] ^ num);
		++i;
	}
	return !is_found; /*if 1 - found, else - not found*/
}

int main()
{
	size_t num_to_find = 12;
	size_t arr[10] = {1,2,3,4,5,6,7,8,9,10};
	size_t is_found = FindNumInArrayEfficiently (num_to_find, arr, 10);
	if(is_found)
	{
		printf("num %ld is found\n", num_to_find);
		return 0;
	}
	printf("num %ld is not found\n", num_to_find);
	return 0;
}
