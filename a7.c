#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   char *blkptr;
   long long bytesum, doublewsum, halfwsum, wordsum; int size;
   char *getmemblock(int size);
   void loadbytedata(char mem[], int size); void loadhalfwdata(char mem[], int size);
   void loadworddata(char mem[], int size); void loaddoublewdata(char mem[], int size);
   long long sumbytedata(char mem[], int size); long long sumhalfwdata(char mem[], int size);
   long long sumworddata(char mem[], int size); long long sumdoublewdata(char mem[], int size);
   void printresult(long long bytesum, long long hwsum, long long wordsum, long long dwsum);

   if(argc < 2)
   {
      void usage(char *progname); 
      char str[] = "a7", *strptr = str; 
      usage(strptr); 
   }

   size = strtol(argv[1], &blkptr, 10);

   if ((size & 7) != 0) {fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A MULTIPLE OF 8.\n"); exit(1);}
   else if (*blkptr != '\0') {fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A NUMBER.\n"); exit(1);}

   if (size <= 0) {void usage(char *progname); char str[] = "a7", *strptr = str; usage(strptr); } 
      
   if(!(blkptr = getmemblock(size))) {fprintf(stderr, "Memory Allocation Fail\n"); exit(1);}

   srand(1);
   loadbytedata(blkptr, size); bytesum = sumbytedata(blkptr, size);
   loadhalfwdata(blkptr, size); halfwsum = sumhalfwdata(blkptr, size);
   loadworddata(blkptr, size); wordsum = sumworddata(blkptr, size);
   loaddoublewdata(blkptr, size); doublewsum = sumdoublewdata(blkptr, size);

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
   int i;
   for (i = 0; i < size; i++)
   {
      *((char *) & mem[i]) = rand() & 0x7F; 
   }
   return;
}

void loadhalfwdata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i += 2)
   {
      *((short int *) & mem[i]) = rand() & 0x7FFF;    
   }
   return; 
}

void loadworddata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i += 4)
   {    
      *((int *) & mem[i]) = rand() & 0x7FFFFFFF;   
   }
   return; 
}

void loaddoublewdata (char mem[], int size)
{
   int i; 
   for (i = 0; i < size; i += 8)
   {
      *((long long *) & mem[i]) = ((long long) rand() << 31) | rand();   
   }
   return;
}

long long sumbytedata (char mem[], int size)
{
   long long sum = 0; 
   int i;
   for (i = 0; i < size; i++)
   {
      sum += *(char *) & mem[i];   
   }
   return sum;
}

long long sumhalfwdata (char mem[], int size)
{
   long long sum = 0;
   int i;
   for (i = 0; i < size; i += 2)
   {
      sum += *(short int*) & mem[i];   
   }
   return sum;
}

long long sumworddata (char mem[], int size)
{
   long long sum = 0;
   int i;
   for (i = 0; i < size; i += 4)
   {
      sum += *(int *) & mem[i];   
   }
   return sum;
}

long long sumdoublewdata(char mem[], int size)
{
   long long sum = 0;
   int i;
   for (i = 0; i < size; i += 8)
   {
      sum += *(long long *) & mem[i];   
   }
   return sum;
}

void printresult(long long bytesum, long long hwsum, long long wordsum, long long dwsum)
{
    fprintf(stderr, "\n%-20s : %-10lld\n", "Sum of bytes", bytesum);
    fprintf(stderr, "%-20s : %-10lld\n", "Sum of half-words", hwsum);
    fprintf(stderr, "%-20s : %-10lld\n", "Sum of words", wordsum);
    fprintf(stderr, "%-20s : %-10lld\n\n","Sum of double-words", dwsum);
    return;
}
