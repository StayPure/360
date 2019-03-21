#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   char *blkptr;
   long long bytesum, doublewsum, halfwsum, wordsum;
   int size;
   char *getmemblock(int size);
   void loadbytedata(char mem[], int size);
   void loadhalfwdata(char mem[], int size);
   void loadworddata(char mem[], int size);
   void loaddoublewdata(char mem[], int size);
   long long sumbytedata(char mem[], int size);
   long long sumhalfwdata(char mem[], int size);
   long long sumworddata(char mem[], int size);
   long long sumdoublewdata(char mem[], int size);
   void printresult(long long bytesum, long long hwsum, long long wordsum, long long dwsum);

   if(argc < 2)
   {
      void usage(char *progname); 
      char str[] = "a7", *strptr = str; 
      usage(strptr); 
   }
   size = strtol(argv[1], &blkptr, 10);
   if ((size & 7) != 0){ fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A MULTIPLE OF 8.\n"); exit(1);}
   else if (*blkptr != '\0') {fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A NUMBER.\n"); exit(1);}
  
   
   if (size <= 0) {void usage(char *progname); char str[] = "a7", *strptr = str; usage(strptr); } 
      
    blkptr = getmemblock(size);
    if(!blkptr) {fprintf(stderr, "Memory Allocation Fail\n"); exit(1);}
    srand(1);
    loadbytedata(blkptr, size);
    bytesum = sumbytedata(blkptr, size);
    loadhalfwdata(blkptr, size);
    halfwsum = sumhalfwdata(blkptr, size);
    loadworddata(blkptr, size);
    wordsum = sumworddata(blkptr, size);
    loaddoublewdata(blkptr, size);
    doublewsum = sumdoublewdata(blkptr, size);

    printresult(bytesum, halfwsum, wordsum, doublewsum);
    
    free(blkptr);
    exit(0);   
}

void usage (char *progname)
{
   fprintf(stderr, "./%s <blocksize>\n", progname); exit(1);
}

char *getmemblock (int size)
{
    char *str; 

    str = (char *) malloc(size);
    return str;
}

void loadbytedata (char mem[], int size)
{
   int a, i;
   /*a = rand();*/

   for (i = 0; i < size; i++)
   {
        a = rand();
        *((char *) & mem[0] + i) = a & 0x7F;   
   }

   return;
}

void loadhalfwdata (char mem[], int size)
{
   int i;
   for (i = 0; i < (size >> 1); i++)
   {
        *((unsigned short int *) & mem[0] + i) = rand() & 0x7FFF;   
   }

   return; 
}

void loadworddata (char mem[], int size)
{
   int a, i;
   for (i = 0; i < (size >> 2); i++)
   {    a = rand();
        *((int *) & mem[0] + i) = a & 0x7FFFFFFF;   
   }

   return; 
}

void loaddoublewdata (char mem[], int size)
{
   int a, b, i;
   long long r;
   a = rand();
   b = rand();
   r = (long long) a;
   r = (r << 31) | b;
 
   for (i = 0; i < size >> 3; i++)
   {
        *((long long *) & mem[0] + i) = (((long long) rand() << 31) &  0x7FFFFFFF)| rand();   
   }

   return;
}

long long sumbytedata (char mem[], int size)
{
    int sum = 0, i;
    for (i = 0; i < size; i++)
    {
        sum += *((char *) & mem[0] + i);   
    }
    return sum;
}

long long sumhalfwdata (char mem[], int size)
{
    int sum = 0, i;
    for (i = 0; i < size >> 1; i++)
    {
        sum += *(short *) & mem[0] + 1;   
    }
    return sum;
}

long long sumworddata (char mem[], int size)
{
    int sum = 0, i;
    for (i = 0; i < size >> 2; i++)
    {
        sum += *(int *) & mem[0] + i;   
    }
    return sum;
}

long long sumdoublewdata(char mem[], int size)
{
    int sum = 0, i;
    for (i = 0; i < size >> 3; i++)
    {
        sum += *(long long *) & mem[0] + i;   
    }
    return sum;
}

void printresult(long long bytesum, long long hwsum, long long wordsum, long long dwsum)
{
    printf("\n\nSum of bytes: %-25lld\n", bytesum);
    printf("\n\nSum of half-words: %11lld\n", hwsum);
    printf("\n\nSum of words: %11lld\n", wordsum);
    printf("\n\nSum of double-words: %11lld\n\n", dwsum);

    return;
}