/******************************* ws14_atoi_itoa.c  ***************************/
/*
  Name: Idan Nave
  Project: Work Sheet 14 - atoi/itoa
  Reviewer: Aya
  Date: 07/08/23
  Version: 1.0
*/
/******************************** Libraries  **********************************/

#include <assert.h> 		        /* assert() */
#include <stdio.h>  		        /* FILEs, stderr, stdin, stdout */
#include <stdlib.h> 		        /* malloc(), free() */
#include <string.h>                 /* string manipulation */
#include <errno.h>                  /* errno global */
#include <time.h>                   /* strftime, localtime, difftime */
#include <stddef.h>                 /* size_t, NULL */

#include "ws14_atoi_itoa.h" 		

/******************************* Definitions  ********************************/

#define ASCII_NUMERIC_OFFSET 48
#define ASCII_SMALL_ALPHA_OFFSET 97
#define ASCII_LARGE_ALPHA_OFFSET 65

/* Length of types */
#define ASCII_BASE_OFFSET 7	  
#define NUM_OF_ALPHAS 26	  
#define NUM_OF_NUMERICS 9	 
#define BASE10 10	         
#define BASE_MAX 36          
#define BASE_MIN 2  
#define NUM_OF_NIBBLES_IN_OUTPUT 8   

/*****************************************************************************/
/*************** Forward Declarations of Static Functions ********************/
/*****************************************************************************/

/* Function that counts the number of digits in an integer number */
static int CountIntDigits(int num, size_t base);
/* Function that validates a given symbol is allowed within base*/
static int IsValidSymbolOfBase(size_t symbol,size_t base); /*symbol_ascii_idx*/
/* Function that clears leading spaces & signs
return value: 1: positive int, -1: negative int, 1: no sign specified*/
static int PrepareAndDetermineSign(char** num_to_prep);
/* Function that returns a decimal int value of a given valid symbol & base*/
static int SymbolToDecimal(size_t symbol_ascii_idx);
/* Function that returns a symbol value of a given decimal_dig*/
static int DecimalToSymbol(int decimal_dig, size_t base);
/* Function that streches all chars in string into the max symbol of the base*/
static void MaxOutToBase(char* int_str, size_t base);
/*Function that mirrors a given string */
static int MirrorString(char *str);

  /****************************** Parsing Functions *************************/

/* Helper function to parse int into string */
int StringToInt(int *num, const char* int_str, size_t base)
{
    size_t i = 0;                        /* Runner for digits  */
    size_t num_of_digs = 0;              /* num of digits  */
    int res_num = 0;                     /* final parsed result  */
    int sign = 1;                        /* sign of result */
    int lsb_dig = 0;                     /* current lsb digit */
    int lsb_sym = 0;                     /* current lsb symbol of asci table */
    char* preped_str = (char*)int_str;   /* preprocessed string */
    errno = 0;

    /* validate not-null passed string  */
    if(NULL == int_str) 
    {
        errno = EINVAL;
        fprintf(stderr, "NULL string encountered: %s\n", strerror(errno));
        return errno;
    }

    /* validate base input  */
    if(base < BASE_MIN || base > BASE_MAX) 
    {
        errno = EINVAL;
        fprintf(stderr, "invalid base request: %s\n", strerror(errno));
        return errno;
    }
    
    /* preprocesssed string - clear of leading spaces & signs */
    sign = PrepareAndDetermineSign(&preped_str);

    /* update number of symbols in numeric str  */
    num_of_digs = strlen(preped_str);
    if(0 == num_of_digs) 
    {
        errno = EINVAL;
        fprintf(stderr, "empty input encountered: %s\n", strerror(errno));
        return errno;
    }

    /* Disassemble string into symbols */
    while(i < num_of_digs)
    {   
        lsb_sym = (int)preped_str[i];
        if(FALSE == IsValidSymbolOfBase(lsb_sym, base))
        {
            errno = EINVAL;
            fprintf(stderr, "invalid digit %c in place %ld\n: %s", 
                                preped_str[i], i, strerror(errno));
            return errno;
        }
        lsb_dig = SymbolToDecimal(lsb_sym);

        /* build the base from lsb with its base weight (multiples of 10) 
        at the first multiply res_num is zero!*/
        res_num = lsb_dig + (res_num)*base;
        ++i;
    }

    /* sign handeling */
    *num = res_num*sign ;
    return errno;
}

/* Helper function to parse int into string */
int IntToString(int num, char* int_str, size_t base)
{
    size_t i = 0;                        /* Runner for digits  */
    size_t num_of_digs = 0;              /* num of digits  */
    char lsb_dig = 0;                    /* current lsb symbol of asci table */
    int sign = 1;                        /* sign of result */
    errno = 0;

    /* validate base input  */
    if(base < BASE_MIN || base > BASE_MAX) 
    {
        errno = EINVAL;
        fprintf(stderr, "invalid base request: %s\n", strerror(errno));
        return errno;
    }
      
    /* sign storing */
    if(num < 0)
    {
        sign = -1;
        num *= sign;
    }

    /* update number of symbols in numeric str  */
    num_of_digs = CountIntDigits(num, BASE10);

    /* Disassemble int into symbols */
    while(i < num_of_digs)
    {   
        lsb_dig = num % (int)base;
        num /= (int)base;
        /* build the base from lsb */
        int_str[i] = (char)(DecimalToSymbol(lsb_dig, base));
        ++i;
    }

    /* sign handeling */
    if(sign < 0)
    {
        if(BASE10 == base)
        {
            int_str[i] = '-';
            ++i;
        }
        else /*if number is from base>10 number contains max_base_symbols */
        {
            char max_symbol = (char)(DecimalToSymbol((int)(base-1), base));
            MaxOutToBase(int_str, base);
            i = 0;
            while(i < num_of_digs)
            {   
                int_str[i] = max_symbol - int_str[i];
                ++i;
            }
        }
    }
    /*add termination char*/
    int_str[i] = '\0';

    /*mirror the final string*/
    MirrorString(int_str); 

    /* leading zeroes removal */
        i = 0;
        while (int_str[i] == '0') 
        {
            ++i;
        }
        /* update num_to_prep to start from a sinificant symbol*/
        int_str += i;
    return errno;
}

/* Function that counts the number of digits in an integer number */
static int CountIntDigits(int num, size_t base)
{
    size_t count_digs = 0;

    /* Handle the case of 0 separately*/
    if (num == 0)
    {
        return 1;
    }

    /* For negative numbers, remove the sign and count the digits*/
    if (num < 0)
    {
        num = -num;
    }

    while (num != 0)
    {
        num = num/(int)base;
        ++count_digs;
    }

    return count_digs;
}

/* Function that clears leading spaces & signs
return value: 1: positive int, -1: negative int, 1: no sign specified*/
static int PrepareAndDetermineSign(char** num_to_prep)
{
    size_t i = 0;            /* Runner for string num_to_prep  */

    /* store leading spaces offset */
    while (*(num_to_prep[i]) == ' ') 
    {
        ++i;
    }
    
    /* update num_to_prep to start from a sinificant symbol*/
    *(num_to_prep) += i;
    if(*(num_to_prep[0]) == '+')
    {    
        /* update sign and skip it*/
        *(num_to_prep) += 1;                   
        return 1;
    }
    if(*(num_to_prep[0]) == '-')
    {    
        /* update sign and skip it*/
        *(num_to_prep) += 1; 
        return -1;
    }
    
    /* update num_to_prep to start from a sinificant symbol*/
    return 1;
}

/* Function that validates a given symbol is allowed within base*/
static int IsValidSymbolOfBase(size_t symbol, size_t base)
{
    size_t min_range_numerics = ASCII_NUMERIC_OFFSET;
    size_t max_range_numerics = ASCII_NUMERIC_OFFSET + NUM_OF_NUMERICS;
    size_t min_range_larges = ASCII_SMALL_ALPHA_OFFSET;
    /*size_t max_range_larges = ASCII_SMALL_ALPHA_OFFSET + NUM_OF_ALPHAS;*/
    size_t min_range_smalls = ASCII_LARGE_ALPHA_OFFSET;
    /*size_t max_range_smalls = ASCII_LARGE_ALPHA_OFFSET + NUM_OF_ALPHAS;*/

    size_t custom_cieling = 0;
    size_t is_valid = FALSE;

    /* for any base - numerics allowed*/
    is_valid += (symbol <= max_range_numerics)&&(symbol >= min_range_numerics);

    /* for bases over 10*/
    if (base > BASE10)
    {
        custom_cieling = min_range_larges + base - BASE10;
        is_valid += (symbol <= custom_cieling) && (symbol >= min_range_larges);
        custom_cieling = min_range_smalls + base - BASE10;
        is_valid += (symbol <= custom_cieling) && (symbol >= min_range_smalls);
    }
   
    /* is_valid var should have accumulated a value > 0 if symbol is allowed*/
    return is_valid;
}

/* Function that returns a decimal int value of a given valid symbol & base*/
static int SymbolToDecimal(size_t symbol_ascii_idx)
{
    /* symbol is numeric */
    if (symbol_ascii_idx < ASCII_LARGE_ALPHA_OFFSET)
    {
        return symbol_ascii_idx - ASCII_NUMERIC_OFFSET;
    }
    /* symbol is LARGE_ALPHA */
    else if (symbol_ascii_idx < ASCII_SMALL_ALPHA_OFFSET)
    {
        return symbol_ascii_idx - ASCII_LARGE_ALPHA_OFFSET + BASE10;
    }
    return symbol_ascii_idx - ASCII_SMALL_ALPHA_OFFSET + BASE10;
}

/* Function that returns a symbol value of a given decimal_dig*/
static int DecimalToSymbol(int decimal_dig, size_t base)
{
    /* symbol is numeric */
    if ((int)base <= BASE10 || decimal_dig <= BASE10)
    {    
        return ASCII_NUMERIC_OFFSET + decimal_dig;
    }
    /* symbol is ALPHA */    
    return ASCII_SMALL_ALPHA_OFFSET + decimal_dig - BASE10;
}

/* Function that streches all chars in string into the max symbol of the base*/
static void MaxOutToBase(char* int_str, size_t base)
{
    size_t i = 0;
    while(i < NUM_OF_NIBBLES_IN_OUTPUT)
    {   
        int_str[i] = (char)(DecimalToSymbol((int)(base-1), base));
        ++i;
    }
}

static int MirrorString(char *str)
{
    size_t len = strlen(str);
    size_t i = 0;

    /* validate not-null passed string  */
    if(NULL == str) 
    {
        errno = EINVAL;
        fprintf(stderr, "NULL string encountered: %s\n", strerror(errno));
        return errno;
    }

    for (; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return PASS;
}

/*****************************************************************************/
/*Function to Print Letters Appearing in Both Two Arrays but Not in the 3rd:*/
/*****************************************************************************/

void PrintUniqueLettersInTwoOFThreeArrays
                    (const char arr1[], const char arr2[], const char arr3[])
{
    int char_count[128] = {0}; /* hold indexed fot all ASCII characters */
    char *p = NULL;            /*shared pointer for insex incrementation*/
    size_t count_occ = 0;      /* counter of TwoOFThree condition */
    
    p = (char*)arr1;
    /* Traverse arr1 and arr2 to mark the occurrences of each letter */
    while (*p != '\0') 
    {
        char_count[(int)*p] = 1;
        ++p;
    }
    p = (char*)arr2;
    while (*p != '\0') 
    {
        char_count[(int)*p]++;
        ++p;
    }
    p = (char*)arr3;
    /* Traverse arr3 to decrease the occurrences of each letter */
    while (*p != '\0') 
    {
        char_count[(int)*p] = 0;
        ++p;
    }

    /* Print the letters that appear in both arr1 and arr2 but not in arr3 */
    printf("Letters in both arr1 and arr2, but not in arr3: ");
    while ( count_occ < 128)
    {
        if (char_count[count_occ] >= 2) 
        {
            printf("%c, ", (char)count_occ);
        }
        ++count_occ;
    }
    printf("\n");
}

/*****************************************************************************/
/********************Function to Check System Endianness:*********************/
/*****************************************************************************/

int IsLittleEndian()
{
    int help_var = 1;
    char* ptr = (char*)&help_var;
    /* If the least significant byte is 1, the system is little-endian */
    return (*ptr == 1); 
}


/*****************************************************************************/
/**********************************ASCII TABLE********************************/
/*****************************************************************************/
/*Binary    Oct     Dec Hex Sym
011 0000    060     48  30  0
011 0001    061     49  31  1
011 0010    062     50  32  2
011 0011    063     51  33  3
011 0100    064     52  34  4
011 0101    065     53  35  5
011 0110    066     54  36  6
011 0111    067     55  37  7
011 1000    070     56  38  8
011 1001    071     57  39  9

100 0001    101     65  41  A
100 0010    102     66  42  B
100 0011    103     67  43  C
100 0100    104     68  44  D
100 0101    105     69  45  E
100 0110    106     70  46  F
100 0111    107     71  47  G
100 1000    110     72  48  H
100 1001    111     73  49  I
100 1010    112     74  4A  J
100 1011    113     75  4B  K
100 1100    114     76  4C  L
100 1101    115     77  4D  M
100 1110    116     78  4E  N
100 1111    117     79  4F  O
101 0000    120     80  50  P
101 0001    121     81  51  Q
101 0010    122     82  52  R
101 0011    123     83  53  S
101 0100    124     84  54  T
101 0101    125     85  55  U
101 0110    126     86  56  V
101 0111    127     87  57  W
101 1000    130     88  58  X
101 1001    131     89  59  Y
101 1010    132     90  5A  Z

110 0001    141     97      61      a
110 0010    142     98      62      b
110 0011    143     99      63      c
110 0100    144     100     64      d
110 0101    145     101     65      e
110 0110    146     102     66      f
110 0111    147     103     67      g
110 1000    150     104     68      h
110 1001    151     105     69      i
110 1010    152     106     6A      j
110 1011    153     107     6B      k
110 1100    154     108     6C      l
110 1101    155     109     6D      m
110 1110    156     110     6E      n
110 1111    157     111     6F      o
111 0000    160     112     70      p
111 0001    161     113     71      q
111 0010    162     114     72      r
111 0011    163     115     73      s
111 0100    164     116     74      t
111 0101    165     117     75      u
111 0110    166     118     76      v
111 0111    167     119     77      w
111 1000    170     120     78      x
111 1001    171     121     79      y
111 1010    172     122     7A      z

*/