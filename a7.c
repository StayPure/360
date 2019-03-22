/*
	Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 07
        Due: March 21, 2019                                          Started: March 19, 2019
        Credit: 10 points.
        KEVIN CONT.
*/        
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
      usage("a7"); 
   }
   size = strtol(argv[1], &blkptr, 10);
   if ((size & 7) != 0) {fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A MULTIPLE OF 8.\n"); exit(1);}
   else if (*blkptr != '\0') {fprintf(stderr, "ERROR: BLOCKSIZE MUST BE A NUMBER.\n"); exit(1);}

   if (size <= 0) {void usage(char *progname); usage("a7"); } 
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

/* THOMAS
*/
void usage (char *progname)
{
   fprintf(stderr, "./%s <blocksize>\n", progname); exit(1);
}

/* THOMAS
*/
char *getmemblock (int size)
{
   char *str;
   str = (char *) malloc(size);
   return str;
}

/* Design a module that takes in a char array and the size of that array then fills that array with
   7-bit, size int values, that uses a random number generator.
   Itterating through the array using a *(char *) to set the value using a random number generated in
   the for loop. Then using the bit-wise operator '&' with 0x7F in order to change the first bit to a 0.
   This continues until we go through the size of the array.
*/
void loadbytedata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i++)
   {
      *((char *) & mem[i]) = rand() & 0x7F; 
   }
   return;
}

/* Design a module that takes in a char array and the size of that array then fills that array with
   15-bit, size/2 int values, that uses a random number generator.
   Itterating through the array using a *(short in *) to set the value using a random number generated in
   the for loop. Then using the bit-wise operator '&' with 0x7FFF in order to change the first bit to a 0.
   This continues until we go through the size/2 of the array.
*/
void loadhalfwdata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i += 2)
   {
      *((short int *) & mem[i]) = rand() & 0x7FFF;    
   }
   return; 
}

/* KEVIN
*/
void loadworddata (char mem[], int size)
{
   int i;
   for (i = 0; i < size; i += 4)
   {    
      *((int *) & mem[i]) = rand() & 0x7FFFFFFF;   
   }
   return; 
}

/* KEVIN
*/
void loaddoublewdata (char mem[], int size)
{
   int i; 
   for (i = 0; i < size; i += 8)
   {
      *((long long *) & mem[i]) = ((long long) rand() << 31) | rand();   
   }
   return;
}

/* NICK
*/
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

/* NICK
*/
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
 
/* KEVIN
*/
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

/* KEVIN
*/
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

/* THOMAS
*/
void printresult(long long bytesum, long long hwsum, long long wordsum, long long dwsum)
{
    fprintf(stderr, "\n%-20s : %-10lld\n", "Sum of bytes", bytesum);
    fprintf(stderr, "%-20s : %-10lld\n", "Sum of half-words", hwsum);
    fprintf(stderr, "%-20s : %-10lld\n", "Sum of words", wordsum);
    fprintf(stderr, "%-20s : %-10lld\n\n","Sum of double-words", dwsum);
    return;
}
