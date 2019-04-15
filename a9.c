/*
        Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 09
        Due: April 16, 2019                                             Started: April 11, 2019
        Credit: 10 points.
        
        Problem: Write a well documented, complete C-program to produce a dump of a memory block in base-16 digits and in ASCII.
        The program will load an executable-image into memory (simulated by dynamically allocated array of chars). It will produce
        dump of memory locations from start-address to end-address. The file, start-address and end-address are specified on command
        line. If the end-address is larger than the last memory location address, it will be adjusted to last location address.
        Solution: 
        Data-structure used: A one dimensional char arr mem[] used to store the contents of the executable-image.
        Accessing functions for the data structure: 
        Errors handled: 
        Limitations: 
        Acknowledgment: We wrote the program together but we had a lot of help from our classmates 
        throughout the making of it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   void die(char *reason);
   int getfilesize(char *path);
   int loadimage(char *path, unsigned char mem[], int size);
   void mdump(unsigned char mem[], int size, int first, int last);
   void usage(char *progname);

   struct stat sbuf;
   char *scheck = NULL, *echeck = NULL;
   int end = strtol(argv[3], &echeck, 16), start = strtol(argv[2], &scheck, 16), size = 0;

   if (argc < 4) usage("a9");
   else if (stat(argv[1], &sbuf)) die("INPUT IS NOT A FILE!");
   else if (scheck == argv[2]) die("START INDEX IS NOT A NUMBER");
   else if (echeck == argv[3]) die("END INDEX IS NOT A NUMBER");
   else if (!(size = getfilesize(argv[1]))) die("FILE IS EMPTY");

   unsigned char *mem = (unsigned char*) malloc(size);
   if (!loadimage(argv[1], mem, size)) die ("COULDN'T LOAD IMAGE"); 
   mdump(mem, size, start, end);
   
   exit(0);
}


/* KEVIN  */
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
   fprintf(stderr, "Reason for termination: %s\n", reason); exit(1);
}

 
 /* THOMAS  */
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
   if (first < 0) first = 0; 
   if (last > size) last = size / 16;

   printf("Address   Words in Hexadecimal                 ASCII characters\n");
   printf("--------  -----------------------------------  ----------------\n");
   int i = 0, j = 0;
   for (i = first; i < last * 16; i += 16)
   {
      printf("%08x ", i / 16);  
      for (j = i; j < i + 16; j++) 
      { 
         if (!(j & 3)) printf(" ");
         printf("%02x", mem[j]); 
      }
      printf("  ");
      for (j = i; j < i + 16; j++)
      {
         if (mem[j] < 0x20 || mem[j] > 0x7e) printf(".");
         else printf("%c", mem[j]);
      }
      printf("\n");
   }
}
