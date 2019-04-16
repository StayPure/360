/*
        Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 09
        Due: April 16, 2019                                             Started: April 11, 2019
        Credit: 10 points.
        
        Problem: Write a well documented, complete C-program to produce a dump of a memory block in
        base-16 digits and in ASCII. The program will load an executable-image into memory (simulated
        by a dynamically allocated array of chars using malloc() and free()). It will produce a dump
        of memory locations from start-address to end-address. The file, start-address, and end-address
        are specified on the command line. If the end-address is larger than the last memory location 
        address, it will be adjusted to last location address. 

        Solution: The program begins by checking if you have enough arguments if not end with a 
        EXIT_FAILURE and tells you how to use the program (usage()) else it takes each of the starting
        arguments and checks each one to make sure they correspond to what each are supposed to be,
        i.e. the first argument check if it is a file and third and second check if it is a number.
        if these checks are not passed the program ends with an EXIT_FAILURE and letting the end user
        know why it stopped (die()). After the checks are passed it then makes sure that the file is
        not empty (getfilesize()) and that it can be load on to the simulated memory (loadimage())
        either failing ends the program with an EXIT_FAILURE. If everything works up until this point
        then the program dumps the memory from the specified start point and stops at the specified 
        endpoints, then it frees the actual memory used for the simulated memory then exiting the 
        program with an EXIT_SUCCESS. 

        Data-structure used: A one-dimensional array for the command line arguments and for the memory
        block.

        Accessing functions for the data structure: Standard C functions for accessing arrays and 
        malloc() and free () to handle the memory for the simulated memory array.

        Errors handled: Checks the arguments for the correct amount, if it was in the correct format,
        and if it had a file and numbers. Also, checks if the file is empty or if the file could not
        be load onto the memory. Lastly, realigns the start and end points if they are out of bounds. 

        Limitations: None?

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
   free(mem);

   exit(0);
}


/* Design a module that prints out the correct way to use the
   program using the progname to get the name of the program
   ending the program afterwards.
   Takes progname and print out the correct usage of the program
   to stderr then exits the program with a failure.
   Called by main().
*/
void usage(char *progname)
{
   fprintf(stderr, "./%s <filepath> <start-address> <end-address>\n", progname); exit(1);
}


/* Design a module that prints the reason of termination and 
   terminates the program. 
   This module takes in a cahr *reason then uses printf() to format
   the char* with a meaningful termination message. Fianlly the 
   program is terminated using exit(1).
   Called by main().
*/
void die(char *reason)
{
   fprintf(stderr, "Reason for termination: %s\n", reason); exit(1);
}


/*Design a module that obtains the size
 of the file in which you are given a path
 to find.
 This module takes in a char *path of which it
 then proceeds to find the size of the file
 using the stat function. Upon finding the size
 the module checks if the size is 0 if so it
 returns 0 if not however, it returns the size.
*/
int getfilesize(char *path)
{
        long long size = stat1.st_size;
        if(size == 0)
        {
                return 0;
        }
        else
        {
        return size;
        }
}


/* Design a module that loads an array mem[] with the contents of a
   executable file using system calls open(), read(), and close(). 
   Returns a 1 on success and a 0 otherwise. 
   This method takes in a char *path that is the intended file to be 
   read in and stored in the unsigned char mem[] that is int size.
   Using fd, file descriptor, to store the value returned by open(),
   if fd < 0 the method returns a 0 stating no such file was opened.
   If open returns a non-zero integer the file descriptor is passed 
   into read() along with the mem[] to store too and the size of the
   array. The number of bits successfully read in by read() is then 
   stored to sz where it is used to add the terminating char to mem[].
   Finally the fd is passed to close() and a 1 is returned.
   Called by main().
*/
int loadimage(char *path, unsigned char mem[], int size)
{
   int sz, fd;
   
   fd = open(path, O_RDONLY);
   if (fd < 0) return 0;
   else 
   {
      sz = read(fd, mem, size);
      mem[sz] = '\0';
      close(fd);
   }
   
   return 1;
}


/* Design a module that dumps the contents of the mem[] array in a 
   specified format starting at the given first word address all the
   way to the last word address while also accounting for out of
   bounds entries.
   The module starts by checking the first and last integers given 
   checking if they are in bounds if not set them to 0 and size of
   the array respectively. The header of the output is then printed
   and the words are then cycled through first printing their address
   then their contents in hexadecimal then in ASCII characters. Note:
   This module also makes the necessary distinction between printable
   and non-printable ASCII characters printing a '.' when it is 
   non-printable.
   Called by main().
*/
void mdump(unsigned char mem[], int size, int first, int last)
{
   if (first < 0 || first > last) first = 0; 
   if (last > size || last < first) last = size / 16;

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
