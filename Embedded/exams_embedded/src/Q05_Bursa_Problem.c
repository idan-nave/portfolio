#include <stdio.h>
#define ARR_LEN 10

int findBestProfit(int prices[], int n, int *buyIndex, int *sellIndex)
{
    int maxProfit = 0;
    int local_p = prices[1] - prices[0];
    int chk = 0;
    int i = 1;
    *buyIndex = 0;
    *sellIndex = 1;

    while ( chk < n-1 )
    {
    printf("chk: %d: , index: %d: , ", chk, i);
        local_p = prices[i] - prices[chk];
        if( (local_p > maxProfit) )
        {
            maxProfit = local_p;
            *sellIndex = i;
            *buyIndex = chk;
            --chk;
        }        
        else
        {
        	++chk;
        }
        if( i < n-1)
        {
        	++i;
        }
    printf("local Profit: %d, ", maxProfit);
    printf("Best Profit: %d\n", maxProfit);
    }
    return maxProfit;
 }

int main()
{
    int prices[ARR_LEN] = {6, 12, 3, 50, 1, 4, 9, 2, 20, 40};
    int maxProfit = 0;
    int buyIndex = 0;
    int sellIndex = 0;

    maxProfit = findBestProfit(prices, ARR_LEN, &buyIndex, &sellIndex);
    printf("Stock hours:   ");
    for (int i = 0; i < ARR_LEN; i++)
    {
        printf("%d ", i);
    }
    printf("\nStock Prices: ");
    for (int i = 0; i < ARR_LEN; i++)
    {
        printf("%d ", prices[i]);
    }
    printf("Best Profit: %d\n", maxProfit);
    printf("Buy Index: %d, Sell Index: %d\n", buyIndex, sellIndex);

    return 0;
}
