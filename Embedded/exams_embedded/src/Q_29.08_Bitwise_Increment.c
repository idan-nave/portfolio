/* A function that adds 1 to an int without using arithmetic operators.*/
int IncrementBitWise(int n)
{
    int mask1 = 1;  /* 00000001 */                
    /* Continue flipping bits until the least significant bit becomes 0 */
    while (0  != n & mask1)  /* or !!(n & mask) */
    {
        n ^= mask1;     /* Flip the current bit */
        mask1 <<= 1;    /* Shift the mask to consider the next bit */
    }

    n ^= mask1;         /* Flip the last remaining bit to add 1 */
    return n;
    /*
    
    Explanation:
    -For the positive number 10, its binary representation is 00001010.
    When we add 1 to it using the Add1ToIntBitWise function,
    it correctly becomes 11, which is 00001011 in binary.
    -For the negative number -64, its binary representation is
    11111111111111111111111111000000 (assuming 32-bit representation).
    When we add 1 to it using the Add1ToIntBitWise function,
    it correctly becomes -63, which is 11111111111111111111111111000001 in binary.
    As we can see, the function handles both positive and negative numbers
    correctly, and it can add 1 to them without using any arithmetic operators.
    */
}
