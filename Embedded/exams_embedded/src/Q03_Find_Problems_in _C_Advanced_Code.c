1. **Explain Problems in the Code:**
   
   There are several issues in the provided code. Lets go through them step by step:

   #include <stdio.h>
   #include <stdlib.h>
   #include <ctype.h>
   
int main()
{
    char *str1 = "hello";
    char str2[strlen(str1)];
    char *str3 = (char*)malloc(strlen(str1) + 1); // Issue: Should be strlen(str1) + 1
    
    while (*str1)
    {
        *str3 = *str1;
        ++str3;
        ++str1;

        strcpy(str2, str1); // Issue: This will result in an incorrect copy of the string

        if (islower(*str1))
        {
            *str1 = toupper(*str1); // Issue: Attempting to modify constant data
        }

        free(str3); // Issue: Freeing str3 inside the loop
        str3 = NULL;
    }

    return 0;
}
Issue 1: Inside the loop, you're using strcpy to copy the string pointed to by str1 to str2. However, this will result in incorrect behavior because the loop increments str1 before copying.

Issue 2: Inside the loop, you're attempting to modify the character pointed to by str1, which is a string literal. String literals are constants and should not be modified.

Issue 3: You're freeing str3 inside the loop, which will result in freeing the memory repeatedly, leading to undefined behavior.


2. 4 people arrive at an old rickety bridge at night. The bridge is weak and can only carry the weight of two of them at a time. They have one flashlight, necessary for each crossing. The flashlight's battery will run out in exactly 12 min, but because of their different fitness levels and some minor injuries they can only cross at different speeds. When two people cross the bridge together, they must move at the slower person's pace. Person A can cross the bridge in 1 minute, B in 2 minutes, C in 4 minutes, and D in 5 minutes.
   Can they all get safely across the bridge before the battery runs out? How?

2. **Crossing the Bridge:**

   Yes, they can all safely cross the bridge before the battery runs out. The key is to minimize the number of trips that the slowest members make while ensuring that the flashlight is used efficiently.

   Here's a step-by-step breakdown:

   - A and B cross together (2 minutes).
   - A returns with the flashlight (1 minute).
   - C and D cross together (5 minutes).
   - B returns with the flashlight (2 minutes).
   - A and B cross together (2 minutes).

   In total, it takes 2 + 1 + 5 + 2 + 2 = 12 minutes. All four people have crossed the bridge.

3. You are given 3 identical ropes and a lighter. Each rope burns out in exactly 1 hour, yet the burning rate varies over the different parts of the rope. Using the lighter and the ropes only, how would you measure 1 hour and 15 min?

 **Measuring 1 Hour and 15 Minutes:**

   - Light the first rope from both ends. It will burn in 30 minutes (since the burning rate varies).
   - Light the second rope from only one end. It will burn in 60 minutes.
   - When the second rope has burned completely (after 60 minutes), light the third rope from both ends. It will burn in 15 more minutes, totaling 75 minutes.

   This way, you've measured 1 hour and 15 minutes using the three ropes.