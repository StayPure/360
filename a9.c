#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

}


/* KEVIN */
void usage(char *progname)
{
   fprintf(stderr, "./%s <filepath> <start-address> <end-address>\n", progname); exit(1);
}


/* ANYONE */
void die(char *reason)
{

}

 
 /* THOMAS */
int getfilesize(char *path)
{

}


/* NICK */
int loadimage(char *path, unsigned char mem[], int size)
{

}


/* KEVIN */
void mdump(unsigned char mem[], int size, int first, int last)
{
   if (first < 0   ) first = 0; 
   if (last  > size) last  = size;

   printf("Address   Words in Hexadecimal                 ASCII characters\n");
   printf("--------  -----------------------------------  ----------------\n");
   int i = 0, j = 0;
   for (i = first; i < last * 16; i += 16)
   {
      printf("%08x ", i/16);  //Address
      for (j = i; j < i + 16; j++) //Words
      { 
         if (!(j & 3)) printf(" ");
         printf("%02x", mem[j]); 
      }
      printf("  ");
      for (j = i; j < i + 16; j++) //ASCII
      {
         if (mem[j] < 0x20 || mem[j] > 0x7e) printf(".");
         else printf("%c", mem[j]);
      }
      printf("\n");
   }
}
