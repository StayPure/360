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


/*Design a module that prints the reason of termination and terminates the program.
  This module takes in a cahr *reason then uses printf() to format the char* with a
  meaningful termination message. Fianlly the program is terminated using exit(1)
*/
void die(char *reason)
{
   printf("Reason for termination: %s\n", reason); exit(1);
}

 
 /* THOMAS */
int getfilesize(char *path)
{

}


/*Design a module that loads an array mem[] with the contents of a executable file using system calls
  open(), read(), and close(). Returns a 1 on success and a 0 otherwise. This method takes in a char
  *path that is the intended file to be read in and stored in the unsigned char mem[] that is int size.
  Using fd, file descriptor, to store the value returned by open(), if fd < 0 the method returns a 0 
  stating no such file was opened. If open returns a non-zero integer the file descriptor is passed into
  read() along with the mem[] to store too and the size of the array. The number of bits successfully read
  in by read() is then stored to sz where it is used to add the terminating char to mem[]. Finally the fd 
  is passed to close() and a 1 is returned.
*/
int loadimage(char *path, unsigned char mem[], int size)
{
   int sz, fd;
   
   fd = open(path, O_RDONLY);
   if (fd < 0) {return 0;}
   else{
      sz = read(fd, mem, size);
      mem[sz] = '\0';
      close(fd);
   }
   
   return 1;
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
