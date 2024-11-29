/* Function to calculate POW with negative nums */

#include <stdio.h>
#include <math.h>

/* Calculate x raised to the power of y */
double POW(double x, int y)
{
    if (y == 0)
    {
        return 1.0; /* x^0 is always 1
    }

    if (y < 0)
    {
        x = 1.0 / x; /* Invert x for negative exponents*/
        y = -y;      /* Make y positive for easier calculation*/
    }

    double result = 1.0;
    while (y > 0)
    {
        if (y % 2 == 1)
        {
            result *= x;
        }
        x *= x;
        y /= 2;
    }

    return result;
}

/* Function to find the square-root of N*/
double SQRTwithPOW(double N)
{ 
    return pow(2, 0.5 * log2(N));
}

/*    Let d be our answer for input number N, then  
    d = N^{1/2}
    Apply log2() both sides 
    log2(d) = log2(N^{1/2)
    log2(d) = {1/2}*log2(N)
    d = 2^{1/2}*log2(N)}
    Therefore, 
    d = pow(2, 0.5*log2(n)) */

/* Function to find the square-root of N*/
double SQRTwithGuess(double num)
{
    double guess = 1.0;
    double epsilon = 0.00001;  // Tolerance for accuracy
    int maxIterations = 100;  // Maximum number of iterations

    for (int i = 0; i < maxIterations; i++)
    {
        double newGuess = 0.5 * (guess + num / guess);
        if (newGuess * newGuess - num < epsilon)
        {
            return newGuess;
        }
        guess = newGuess;
    }
    return guess;  // Return the best guess even if tolerance is not met
}
 

int main(void)
{
    /* POW*/
    double x = 2.0;
    int y = -3;
    double result = POW(x, y);
    printf("%f\n", result);

    /*SQRT*/
    int N = 12;
    printf("%f ", SQRTwithPOW(N));

    /*SQRT*/
    double n = 16.0;
    double result = SQRTwithGuess(n);

    printf("Square root of %lf is approximately %lf\n", number, result);

    return 0;
}
