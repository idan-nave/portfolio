/********************************** BitArray.c  ******************************/
/*
  Name: Idan Nave
  Project: Work Sheet - DATA Structures
  Reviewer: ???
  Date: 07/08/23
  Version: 1.0
*/
/******************************** Libraries  **********************************/

#include <assert.h> 		/* assert() */
#include <stdio.h>  		/* FILEs, stderr, stdin, stdout */
#include <string.h>             /* strcmp */ 
#include <stddef.h>             /* size_t, NULL */

#include "bit_array.h" 		

/******************************** Definitions  ********************************/

/* Lengths' Definition */	
#define NUM_OF_BITS_IN_WORD 64	 
#define NUM_OF_BITS_IN_NIBBLE 4	          
#define NIBBLE_RANGE 16                    
#define NUM_OF_NIBBLES_IN_WORD 16	  
#define TRUE 1	  
#define FALSE 0	  

/******************************************************************************/
/*************** API Implementation - Functions Definitions *******************/
/******************************************************************************/
 
/*Function that sets all the bits. 
  Arguments: array of 64 bits.
  Return value: It returns the set array.*/
bit_array_ty SetAll(bit_array_ty bit_arr)
{
    bit_arr = (size_t)0;
    return ~bit_arr;
}

/*Function that resets all the bits. 
  Arguments: array of 64 bits.
  Return value: It returns the reset array.*/
bit_array_ty ResetAll(bit_array_ty bit_arr)
{ 
      
    bit_arr = 0U;
    return bit_arr;
}

/*Function that sets the index bit. 
  Arguments: array of 64 bits, index.
  Return value: It returns the updated array.
  Undefined B.: if index > 63 return the origin array*/
bit_array_ty SetOn(bit_array_ty bit_arr, size_t index)
{
    size_t mask1 = 1U;
    return mask1 << index | bit_arr; 
    /* see precedence table (>> better t. |)*/
}
/*Function that resets the index bit. 
  Arguments: array of 64 bits, index.
  Return value: It returns the updated array.
  Undefined B.: if index > 63 return the origin array*/
bit_array_ty SetOff(bit_array_ty bit_arr, size_t index)
{
    size_t mask1 = 1U;
    mask1 = mask1 << index;

    return ~mask1 & bit_arr; 
    /* see precedence table( ~ > &)*/
}
/*Function that sets the index bit with bit_val. 
  Arguments: array of 64 bits, index, bit value.
  Return value: It returns the updated array.
  Undefined B.: if bit_val diff. from 0 or 1 return the origin array
                if index > 63 return the origin array*/
bit_array_ty SetBit(bit_array_ty bit_arr, size_t index, int bit_val)
{

    if(bit_val < 0 || bit_val > 1 || index > NUM_OF_BITS_IN_WORD - 1) 
    {
        return bit_arr;
    }
    
    if(1 == bit_val) 
    {
        return SetOn(bit_arr,index);
    }
    
    return SetOff(bit_arr,index);
    
}
/*Function that returns the index bit value. 
  Arguments: array of 64 bits, index.
  Return value: It returns the index bit value.
  Undefined B.: if index > 63 return the origin array*/
int GetVal(bit_array_ty bit_arr, size_t index)
{

    size_t mask1 = 1U;
    mask1 = mask1 << index;

    return !!(bit_arr & mask1);   
    /* first ! gives opposite of "is any num or zero", 2nd ! fix the negation*/
}

/*Function that flips the array. 
  Arguments: array of 64 bits.
  Return value: It returns the flipped array.*/
bit_array_ty Flip(bit_array_ty bit_arr)
{
    return ~bit_arr;
}


/*Function that mirrors the array. 
  Arguments: array of 64 bits.
  Return value: It returns the mirrored array.*/
bit_array_ty Mirror(bit_array_ty bit_arr)
{
    /* Swap the 32-bit nibbles using bit masking and shifting */ 
    bit_arr = ((bit_arr & 0xFFFFFFFF00000000) >> 32) 
        | ((bit_arr & 0x00000000FFFFFFFF) << 32);
    /* Swap the 16-bit bytes-sized using bit masking and shifting */
    bit_arr = ((bit_arr & 0xFFFF0000FFFF0000) >> 16) 
        | ((bit_arr & 0x0000FFFF0000FFFF) << 16);
    /* Swap the 8-bit bytes-sized using bit masking and shifting */
    bit_arr = ((bit_arr & 0xFF00FF00FF00FF00) >> 8)  
        | ((bit_arr & 0x00FF00FF00FF00FF) << 8);
    /* Swap the 4-bit nibbles using bit masking and shifting */
    bit_arr = ((bit_arr & 0xF0F0F0F0F0F0F0F0) >> 4)  
        | ((bit_arr & 0x0F0F0F0F0F0F0F0F) << 4);
    /* Swap the 2-bit groups using bit masking and shifting */
    bit_arr = ((bit_arr & 0xCCCCCCCCCCCCCCCC) >> 2)  
        | ((bit_arr & 0x3333333333333333) << 2);
    /* Swap adjacent bits using bit masking and shifting */
    bit_arr = ((bit_arr & 0xAAAAAAAAAAAAAAAA) >> 1)  
        | ((bit_arr & 0x5555555555555555) << 1);
    
    return bit_arr;
}

/*Function that rotates the array num_of_shifts times to the right. 
  Arguments: array of 64 bits, num_of_shifts.
  Return value: It returns the rotated array.*/
bit_array_ty RotateRight(bit_array_ty bit_arr, size_t num_of_shifts)
{
    /* Counter to store the number of set bits (1s) found */
    size_t mask1 = 1U;
    size_t lsb_holder = 0U;
    size_t shift_i = 0;
    
    /* Iterate through num_of_shifts */
    while (shift_i < num_of_shifts) 
    {
        /* hold Lsb bits in higher of "lsb_holder" */
        lsb_holder = lsb_holder & mask1;
        /* perform shift one time */
        bit_arr >>= 1;
        /* perform shift of holder twards msb */
        lsb_holder <<= (NUM_OF_BITS_IN_WORD - 1);
        /* append shifted & holder */
        bit_arr = bit_arr | lsb_holder;
        ++shift_i;
    }
    
    return bit_arr;
}

/*Function that rotates the array num_of_shifts times to the left. 
  Arguments: array of 64 bits, num_of_shifts.
  Return value: It returns the rotated array.*/
bit_array_ty RotateLeft(bit_array_ty bit_arr, size_t num_of_shifts)
{
    /* Counter to store the number of set bits (1s) found */
    size_t mask1 = 1U;
 
    size_t msb_holder = 0U;
    size_t shift_i = 0;
    /* Iterate through num_of_shifts */
    while (shift_i < num_of_shifts)
    {
      /* hold Msb bits in lower of "msb_holder" */
      msb_holder = (bit_arr >> (NUM_OF_BITS_IN_WORD - 1)) & mask1;
      /* perform shift one time */
      bit_arr <<= 1;
      /* append shifted & holder */
      bit_arr = bit_arr | msb_holder;
      ++shift_i;
    }
    
    return bit_arr;
}

/*Function that counts the set bits. 
  Arguments: array of 64 bits.
  Return value: It returns the count of the set bits.*/
size_t CountOn(bit_array_ty bit_arr)
{
    /* Counter to store the number of set bits (1s) found */
    unsigned int count = 0;
    size_t mask1 = 1U; 
    
    /* Iterate through the bits of the input integer */
    while (0 != bit_arr)
    {
        /* Increment the count if the LSB is 1 */
        count += bit_arr & mask1;
        /* Shift the integer to the right to check the next bit */
        bit_arr >>= 1;
    }
    
    /* Return the total count of set bits (1s) */
    return count;
}

/*Function that counts the unset bits. 
  Arguments: array of 64 bits.
  Return value: It returns the count of the unset bits.*/
size_t CountOff(bit_array_ty bit_arr)
{
    return NUM_OF_BITS_IN_WORD - CountOn(bit_arr);
}

/*Function that converts the array into a string. 
  Arguments: array of 65 bits, dest string.
  Return value: It returns the converted string.
  Undefined B.: if the dest is not large enough*/
char *ToString(bit_array_ty bit_arr, char *dest)
{    
    /* runner for writing string */
    size_t i = 0;
    /* char to write */
    char write_l_to_r = '0';
    
    assert(NULL != dest);
    /* arr is ready for shifting left into a string */
    while (i < NUM_OF_BITS_IN_WORD)
    {
        /*i-1 is the equivalent position in the mirror place of current i*/
        write_l_to_r = GetVal(bit_arr, NUM_OF_BITS_IN_WORD - 1 - i);
        dest[i] = '0' + write_l_to_r;
        ++i;
    }
    dest[i]='\0';
    return dest;
}

/*Function that mirrors the array. 
  Arguments: array of 64 bits.
  Return value: It returns the mirrored array.*/
bit_array_ty MirrorByLUT(bit_array_ty bit_arr)
{
    /* lut to map num of set bits in evey nibble image */
    static size_t mirror_nibble_lut[16];
    /* flag to determine if initialization of lut is needed */
    unsigned int is_lut_init = FALSE;
    /* Counter to store the number of set bits (1s) found */
    bit_array_ty mirrored_arr = 0;
    /* Counter to traverese arr num_of_nibbles - size */
    unsigned int nib_runner = 0;
    /* runner for initing lut */
    size_t i = 0;
    size_t mask_nibble = 0x000000000000000f;
    size_t curr_nibble = 0U;
    size_t access_idx = 0;
    
    
    /* init lut*/
    if(!is_lut_init)
    {
        while (i < NIBBLE_RANGE)
        {   /* write mirrored nibble (use Mirror() instead of hardcoded vals) */
            mirror_nibble_lut[i] = Mirror(i);
            ++i;    
        }
       is_lut_init = TRUE;
    }
    /* Iterate through the bits of the input integer */ 
    while (nib_runner < NUM_OF_NIBBLES_IN_WORD)
    {
        /* prepare current nibble*/
        curr_nibble = bit_arr & mask_nibble;
        /* access LUT in index of value given by current checked 
        nibble & update counter*/
        /* parse access index by shifting right back to 0-15 range */
        access_idx = curr_nibble >> ((nib_runner)*NUM_OF_BITS_IN_NIBBLE);
        /* access LUT in index of value given by current checked */
        mirrored_arr |= mirror_nibble_lut[access_idx] >>
                                  ((nib_runner)*NUM_OF_BITS_IN_NIBBLE);
        /* shift the mask to ready up next iteratoin*/
        mask_nibble <<= NUM_OF_BITS_IN_NIBBLE;
        ++nib_runner;
    } 
    
    return mirrored_arr;
}

size_t CountOnByLUT(bit_array_ty bit_arr)
{
    /* lut to map num of set bits in evey nibble image */
    static unsigned int set_count_in_nibble_lut[16];
    /* flag to determine if initialization of lut is needed */
    unsigned int is_lut_init = FALSE;
    /* Counter to store the number of set bits (1s) found */
    unsigned int count_ones = 0;
    /* Counter to traverese arr num_of_nibbles - size */
    unsigned int nib_runner = 0;
    /* runner for initing lut */
    size_t i = 0;
    size_t mask_nibble = 0x000000000000000f;
    size_t curr_nibble = 0U;
    size_t access_idx = 0;
    
    /* init lut*/
    if(!is_lut_init)
    {
        while (i < NIBBLE_RANGE)
        {   /* write { 0, 1, 1, 2, 1, 2, 2, 3} */
            set_count_in_nibble_lut[i] = CountOn(i);
            ++i;    
        }
        
        is_lut_init = TRUE;
    }
    
    /* Iterate through the bits of the input integer */
    while (nib_runner < NUM_OF_NIBBLES_IN_WORD)
    {
        /* prepare current nibble*/
        curr_nibble = bit_arr & mask_nibble;
        /* access LUT in index of value given by current checked 
        nibble & update counter*/
        /* parse access index by shifting right back to 0-15 range */
        access_idx = curr_nibble >> ((nib_runner)*NUM_OF_BITS_IN_NIBBLE);
        /* access LUT in index of value given by current checked */
        count_ones += set_count_in_nibble_lut[access_idx];
        /* shift the mask to ready up next iteratoin*/
        mask_nibble <<= NUM_OF_BITS_IN_NIBBLE;
        ++nib_runner;
    }

    return count_ones;
}
