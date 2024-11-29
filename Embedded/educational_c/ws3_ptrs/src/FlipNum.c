#include <stdio.h>

int flip(int num)
{
    int flip = 0;
    while(num != 0)
    {
        flip *= 10;
        flip += (num%10);
        printf("%ddflip \n",flip);
            printf("%ddig \n",(num%10));

        num /= 10;
            printf("%dnum \n",num);

    }
    return flip;
}

int main()
{
    int num = -111111;
    printf("%d\n",flip(num));
    return 0;   
}