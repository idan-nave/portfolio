/* Generate and returns a random int in range [lower, upper] by given mode:
mode 0 (INT_FUNCS_IDX)	     generates int within range
mode 1 (FLOAT_FUNCS_IDX)     generates float within range
mode 2 (STRING_FUNCS_IDX)    generates ASCII string in abs(upper-lower) length\
returned data is given by a void* pointer and allocated each function call,
in order for the caller to be able to have different addresses each call. */

static int GiveRandomDataByType(int lower, int upper, size_t type, void* data)
{
    /* random-required pointers */
    int* rnd_int = NULL;
    float* rnd_float = NULL;
    char* rnd_str = NULL;
    /* numeric-required vars */
    int int_data = 0;        
    float float_data = 0.0;
    /* string-required vars */
    size_t i = 0;
    size_t rnd_str_len = 0;
    int slct_from_charset = 0;
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";      
    /* case selector for requested data-type */
    printf("************inside GiveRandomDataByType***********%ld\n", type);
    switch(type)
    {
      case INT_FUNCS_IDX:  /* Generate int */
        /* Data Generation Algo */
                printf("************before InitInt***********%d\n", *rnd_int);
        int_data = (rand() % (upper - lower + 1)) + lower;
                printf("************before InitInt***********%d\n", *rnd_int);
        /* allocate new address */
        rnd_int = (int*)malloc(sizeof(int)); 
          if (NULL == rnd_int) /* validate successful allocation */
          {
              fprintf(stderr, "GiveRandomDataByType Error: %s\n",
              info[MEMORY_ALLOCATION_ERROR].message);
              return MEMORY_ALLOCATION_ERROR;
          }             
        *rnd_int = int_data;                          /* assign random data */

        data = rnd_int;                    /* assignment to void pointer */
      break;
      
      case FLOAT_FUNCS_IDX: /* Generate float */
        /* Data Generation Algo */
        float_data = (((float)upper - (float)lower) 
                                          * ((float)rand() / RAND_MAX)) + lower;
        /* allocate new address */
        rnd_float = (float*)malloc(sizeof(float));
          if (NULL == rnd_float) /* validate successful allocation */
          {
              fprintf(stderr, "GiveRandomDataByType Error: %s\n",
              info[MEMORY_ALLOCATION_ERROR].message);
              return MEMORY_ALLOCATION_ERROR;
          }
        *rnd_float = float_data;                    /* assign random data */
        data = rnd_float;                    /* assignment to void pointer */
      break;
      
      case STRING_FUNCS_IDX:  /* Generate string using charset[] */

        /* Data Generation Algo */
        rnd_str_len = abs(upper - lower);
        /* validate random string is within limitations */
        if(rnd_str_len > MAX_STR_LEN-1)
        {
            fprintf(stderr, "GiveRandomDataByType Error: %s\n",
            info[INVALID_STRING_LEN].message);
            return INVALID_STRING_LEN;
        }
        /* allocate new address */
        rnd_str = (char*)malloc(sizeof(char)*rnd_str_len);
          if (NULL == rnd_str) /* validate successful allocation */
          {
              fprintf(stderr, "GiveRandomDataByType Error: %s\n",
              info[MEMORY_ALLOCATION_ERROR].message);
              return MEMORY_ALLOCATION_ERROR;
          }
        /* Placement of new string */
        while (i < rnd_str_len)
        {     /* mark random char from char-set */
              slct_from_charset = rand() % (int)(sizeof charset - 1);
              /* placement of marked char into random */
              rnd_str[i] = charset[slct_from_charset];
              ++i;
        }
        rnd_str[rnd_str_len] = '\0';
        data = rnd_str;                    /* assignment to void pointer */
      break;
      
      default:
      printf("************default of  GiveRandomDataByType***********%d\n", int_data);
      fprintf(stderr, "GiveRandomDataByType Error: %s\n",
      info[INVALID_ARGUMENT].message);
      return INVALID_ARGUMENT;
      break;
    }
    return NO_ERROR;printf("************end of GiveRandomDataByType***********%d\n", int_data);
}
