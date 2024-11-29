/* Bingo Function to generate random numbers from 1 to 100 without repeating the same number until after every 100 calls.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 100

/* Shuffle an array using the Fisher-Yates algorithm */
int Bingo100(void)
{
	static int init = 1;
	size_t i = 0;
	size_t ret_num = 0;
	size_t rnd_idx = MAX_NUM - 1;;
	static int bingo_LUT[MAX_NUM] = {0};
	static size_t reset_idx = MAX_NUM - 1;

	/*only if LUT needs reset: */
	if (reset_idx == 0 || init)
	{
		init = 0;
		i = 0;
	    while( i < MAX_NUM )
	    {
	        bingo_LUT[i] = i + 1;
	        ++i;
	    }
	    reset_idx = MAX_NUM - 1;
	}
/*        printf("at end %d\n", reset_idx);
*/
    /* generate num */
    rnd_idx = rand() % (reset_idx + 1);
	/*rnd_idx =
	(size_t)((double)rand()/((double)RAND_MAX + 1) * reset_idx);*/
    ret_num = bingo_LUT[rnd_idx];

    /* swap used num with unused num*/
    bingo_LUT[rnd_idx] = bingo_LUT[reset_idx];
    bingo_LUT[reset_idx] = ret_num;
    --reset_idx;
/*        printf("at end %d\n", reset_idx);
*/
    return ret_num;
}

int main()
{
	size_t i = 0;
    srand(time(NULL)); /* Seed the random number generator */ 
    while( i < MAX_NUM)
    {
        printf("%d\n", Bingo100());
        ++i;
    }
    return 0;
}
