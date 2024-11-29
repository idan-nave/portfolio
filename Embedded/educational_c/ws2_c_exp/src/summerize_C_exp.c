#include <stdio.h>

void printExpressions()
{
    int a = 3;
    int foo();

    int aValue = a;  // Value of 'a'
    printf("'a' - Type: int, Value: %d, Side Effect Explanation: No side effect\n", aValue);

    int (*fooPtr)() = foo;  // Pointer to 'foo'
    int (*&fooRef)() = fooPtr;  // Reference to 'fooPtr'
    printf("'foo' - Type: int function(), Value: Undefined, Side Effect Explanation: No side effect\n");
    printf("'&foo' - Type: int (*)(), Value: Undefined, Side Effect Explanation: No side effect\n");

    int fooResult = foo();  // Result of calling 'foo'
    printf("'foo()' - Type: int, Value: Undefined, Side Effect Explanation: Calling an undefined function, undefined behavior\n");

    int aPlusFooResult = a + foo();  // Result of 'a + foo()'
    printf("'a+foo()' - Type: int, Value: Undefined, Side Effect Explanation: Calling an undefined function, undefined behavior\n");

    int *aAddress = &a;  // Address of 'a'
    printf("'&a' - Type: int*, Value: Address of 'a', Side Effect Explanation: No side effect\n");
}

// ###### return power of 10 ##########
int powerOfTen(int n)
{
    int result = 1;
    while (n > 0) {
        result *= 10;
        n--;
    }
    return result;
}
// ######## takes an integer and returns the reversed order of its digits. #########
int reverseDigits(int num)
{
    int reversedNum = 0;

    while (num != 0)
    {
        int remainder = num % 10;  // Get the last digit
        reversedNum = reversedNum * 10 + remainder;  // Add the digit to the reversed number
        num = num / 10;  // Remove the last digit from the original number
    }

    return reversedNum;
}

##########################both ways of swapping vars#######################
void swap_temp(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_xor(int *a, int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main()
{	
	// ###### Print Expression of a & foo ##########
	printf("Here is a description of the following code:/n int a = 3; int foo(); ");
	printExpressions();

	// ###### n^10 ##########
	int n = 3;
	int result = powerOfTen(n);
	printf("Here is 10^%d = %d\n", n, result);

	// ###### flipped int ##########
	int num = 12340;
	int reversedNum = reverseDigits(num);
		printf("Original Number: %d\n", num);
	printf("Reversed Number: %d\n", reversedNum);

	// ###### swap 2 variables ##########
	int num1 = 10;
	int num2 = 20;

	printf("Before swapping: num1 = %d, num2 = %d\n", num1, num2);

	// Swap using temporary variable
	swap_temp(&num1, &num2);
	printf("After swapping using temporary variable: num1 = %d, num2 = %d\n", num1, num2);

	// Swap using XOR operation
	swap_xor(&num1, &num2);
	printf("After swapping using XOR operation: num1 = %d, num2 = %d\n", num1, num2);

	return 0;
}

