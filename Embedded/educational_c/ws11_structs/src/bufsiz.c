#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define my_offsetof(type, member) ((size_t)(&(((type*)0)->member)) )

typedef struct address
{
   char name[50];
   char street[50];
   int phone;
}address_ty;
typedef struct address* st_ptr;


int offset_func()
{
   printf("name offset = %ld byte in address structure.\n",
   offsetof(struct address, name));

   printf("street offset = %ld byte in address structure.\n",
   offsetof(struct address, street));

   printf("phone offset = %ld byte in address structure.\n",
   offsetof(struct address, phone));

   return(0);
} 

int my_offset_func()
{
  address_ty my_address = {0};
    st_ptr ptr = &my_address;
   printf("name offset = %ld byte in address structure.\n",
   my_offsetof(struct address, name));

   printf("street offset = %ld byte in address structure.\n",
   my_offsetof(struct address, street));

   printf("phone offset = %ld byte in address structure.\n",
   my_offsetof(struct address, phone));

   printf("%pn",ptr);

   return(0);
} 


int main()
{

    char buffer[BUFSIZ];
    FILE* f = NULL;
    /* setup the buffer */
    setbuf(stdout,buffer);

    puts("Go!");
    /*getchar();*/    
    puts("Thank you.");

    fflush(stdout);
    strcpy(buffer, "helloooo");

    printf("The BUFSIZ buffer is set to %d bytes\n",BUFSIZ);
    fflush(stdout);
    /*
      strcpy(buffer, "helloooo");
      fputs(buffer, 5); tried with gets
      fflush(stdout);
      printf("with fgets\n");
      fflush(stdout);
    */
    /*    
      f = (FILE*)buffer;
      fflush(buffer);*/
    /*    
      strcpy(buffer, "helloooo");
      sprintf (buffer, "with sprintf = %5000s", stdout);
      fflush(stdout);
    */
    offset_func();
    my_offset_func();
    return(0);
}