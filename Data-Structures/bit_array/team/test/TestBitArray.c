#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <string.h> /*strcmp*/

#include "BitArray.h"


void TestSetAll();
void TestResetAll();
void TestSetOn();
void TestSetOff();
void TestSetBit();
void TestGetVal();
void TestFlip();
void TestMirror();
void TestRotateRight();
void TestRotateLeft();
void TestCountOn();
void TestCountOff();
void TestToString();
void TestCountOnLUT();
void TestMirrorLUT();

/******************************************************************************/

int main()
{
	TestSetAll();
	TestResetAll();
	TestSetOn();
	TestSetOff();
	TestSetBit();
	TestGetVal();
	TestFlip();
	TestMirror();
	TestRotateRight();
	TestRotateLeft();
	TestCountOn();
	TestCountOff();
	TestToString();
	TestCountOnLUT();
	TestMirrorLUT();
	
	return 0;
}

/******************************************************************************/

void TestSetAll()
{
	bit_array_ty test_arr[10] = {13, 1233,3213214,321312,3215423,643,5466,53262
	,5423654,543534524352};
	size_t i = 0;
	
	while(10 < i)
	{	
		if((size_t)-1 != SetAll(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("SetAll checked\n");
}

/******************************************************************************/

void TestResetAll()
{
	bit_array_ty test_arr[10] = {13, 1233,3213214,321312,3215423,643,5466,53262
	,5423654,543534524352};
	size_t i = 0;
	
	while(10 < i)
	{
		if(0 != ResetAll(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("ResetAll checked\n");
}

/******************************************************************************/

void TestSetOn()
{
	bit_array_ty test_arr[10] = {13, 1233, 3213214, 321312,3215423,643,5466,53262
	,5423654,543534524352};
	
	size_t test_arr_indexes[10] = {13, 17, 22, 0, 31, 60, 15, 25, 18, 48};
	
	bit_array_ty res_arr[10] = {8205, 132305, 7407518, 321313, 2150699071,
	0x1000000000000283,38234,33607694,5685798,0x1007E8D2EA7C0};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != SetOn(test_arr[i], test_arr_indexes[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("SetOn checked\n");
}

/******************************************************************************/

void TestSetOff()
{
	bit_array_ty test_arr[10] = {8205, 132305, 7407518, 321313, 2150699071,
	0x1000000000000283,38234,33607694,5685798,0x1007E8D2EA7C0};
	
	size_t test_arr_indexes[10] = {13, 17, 22, 0, 31, 60, 15, 25, 18, 48};
	
	bit_array_ty res_arr[10] = {13, 1233, 3213214, 321312,3215423,643,5466,53262
	,5423654,543534524352};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != SetOff(test_arr[i], test_arr_indexes[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("SetOff checked\n");
}

/******************************************************************************/

void TestSetBit()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	643 ,38234,33607694,5685798,543534524352};
	
	size_t test_arr_indexes[10] = {13, 17, 22, 0, 31, 60, 15, 25, 18, 48};
	int test_arr_set[10] = {0, 1, 1, 0, 0, 0, 1, 1, 1, 0};
	bit_array_ty res_arr[10] = {8205, 1233, 3213214,321313 ,2150699071 ,0x1000000000000283,5466,53262
	,5423654,0x1007E8D2EA7C0};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != SetBit(test_arr[i],test_arr_indexes[i], test_arr_set[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("SetBit checked\n");
}

/******************************************************************************/

void TestGetVal()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	643 ,38234,33607694,5685798,543534524352};
	
	size_t test_arr_indexes[10] = {13, 10, 16, 0, 31, 60, 15, 25, 18, 48};
	int res_arr[10] = {0, 1, 1,0 ,0 ,0,1,0	,1,0};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != GetVal(test_arr[i],test_arr_indexes[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("GetVal checked\n");
}

/******************************************************************************/

void TestFlip()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	64365464984 ,38234,32321333607694,5685798,543534524352};
	
	bit_array_ty res_arr[10] = {0xFFFFFFFFFFFFFFF2, 0xFFFFFFFFFFFDFB2E, 0xFFFFFFFFFF8EF861
	,0xFFFFFFFFFFFB18DF ,0xFFFFFFFFFFCEEFC0 ,0xFFFFFFF10384F267,0xFFFFFFFFFFFF6AA5
	,0xFFFFE29A9A6442F1,0xFFFFFFFFFFA93DD9,0xFFFFFF8172D1583F};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != Flip(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("Flip checked\n");
}

/******************************************************************************/

void TestMirror()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	643654649 ,38234,32321333607694,5685798,543534524352};
	
	bit_array_ty res_arr[10] = {0xB000000000000000, 0x8B20400000020400, 0x79E08E0000000000
	,0x4E7200000000000 ,0xFC088C0000000000 ,0x9FC6BA6400000000,0x5AA9000000000000
	,0x70BDD9A6A6B80000,0x64436A0000000000,0x3E574B17E000000};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != Mirror(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("Mirror checked\n");
}

/******************************************************************************/

void TestRotateRight()
{
	bit_array_ty test_arr[5] = {13, 132305, 7407518, 321312, 3215423};
	
	size_t test_arr_rotates[5] = {13, 10, 16, 0, 20};
	
	bit_array_ty res_arr[5] = {0xD000000000000, 0x45810000000000, 0x79E08E0000000000
	,3215423 ,0xFC088C00000 };
	
	size_t i = 0;
	
	while(5 < i)
	{
		if(res_arr[i] != RotateRight(test_arr[i], test_arr_rotates[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("RotateRight checked\n");
}

/******************************************************************************/

void TestRotateLeft()
{
	bit_array_ty res_arr[5] = {13, 132305, 7407518, 321312, 3215423};
	
	size_t test_arr_rotates[5] = {13, 10, 16, 0, 20};
	
	bit_array_ty test_arr[5] = {0xD000000000000, 0x45810000000000, 0x79E08E0000000000
	,3215423 ,0xFC088C00000 };
	
	size_t i = 0;
	
	while(5 < i)
	{
		if(res_arr[i] != RotateLeft(test_arr[i], test_arr_rotates[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("RotateLeft checked\n");
}

/******************************************************************************/

void TestCountOn()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	643654649 ,38234,32321333607694,5685798,543534524352};
	
	bit_array_ty res_arr[10] = {3, 6, 12, 8,10 ,18, 8,26, 10,21};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != CountOn(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("CountOn checked\n");
}

/******************************************************************************/

void TestCountOff()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	643654649 ,38234,32321333607694,5685798,543534524352};
	
	bit_array_ty res_arr[10] = {61, 58, 52, 56,54 ,46, 56,38, 54,43};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != CountOff(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("CountOff checked\n");
}

/******************************************************************************/

void TestToString()
{
	bit_array_ty test_arr[3] = {32321333607694,5685798,543534524352};
	char *dest = (char*)malloc(sizeof(char)*65);
	char *res_arr[3] = {"0000000000000000000111010110010101100101100110111011110100001110"
	, "0000000000000000000000000000000000000000010101101100001000100110"
	,"000000000000000000000111111010001101001011101010011111000000"};
	
	size_t i = 0;
	
	while(3 < i)
	{
		if(strcmp(res_arr[i],ToString(test_arr[i] ,dest)) != 0)
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("ToString checked\n");
}

/******************************************************************************/

void TestCountOnLUT()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	643654649 ,38234,32321333607694,5685798,543534524352};
	
	bit_array_ty res_arr[10] = {3, 6, 12, 8,10 ,18, 8,26, 10,21};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != CountOnLUT(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("CountOnLUT checked\n");
}

/******************************************************************************/

void TestMirrorLUT()
{
	bit_array_ty test_arr[10] = {13, 132305, 7407518, 321312, 3215423,
	643654649 ,38234,32321333607694,5685798,543534524352};
	
	bit_array_ty res_arr[10] = {0xB000000000000000, 0x8B20400000020400, 0x79E08E0000000000
	,0x4E7200000000000 ,0xFC088C0000000000 ,0x9FC6BA6400000000,0x5AA9000000000000
	,0x70BDD9A6A6B80000,0x64436A0000000000,0x3E574B17E000000};
	
	size_t i = 0;
	
	while(10 < i)
	{
		if(res_arr[i] != MirrorLUT(test_arr[i]))
		{
			printf("test failed on i = %lu\n", i);
		}
		++i;
	}
	printf("MirrorLUT checked\n");
}
