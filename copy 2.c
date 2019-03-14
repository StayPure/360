#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
   void usage (char *progname);
   void die (char *reason);
   int copyfiles (int argc, char *argv[]);
   int chkdst (/*int,*/ char **argv);

   if (argc < 3)
   {
      void usage(char *progname);
      char str[] = "copy", *strptr = str;
      usage(strptr);
   }
   else if (!chkdst(&argv[argc - 1]))
   {
      void die (char *reason);
      char str[] = "INVALID DESTINATION", *strptr = str;
      die(strptr);
   }

   copyfiles(argc, argv);

   exit(0);
}


void usage (char *progname)
{
   fprintf(stderr, "./%s file-path1 file-path2 ... dest-dir\n", progname); exit(1);
}


void die (char *reason)
{
   fprintf(stderr, "%s\nPROGRAM ENDED\n", reason); exit(1);
}

/*	Design a module that takes in a single arg, char **argv,
	that checks the sanity of the last arg passed to main()
	returns a 1 on success or 0 otherwise. A meaningful/usage
	error message will be printed out on failure.
	Takes a single pointer, *argv, and passes it to isdir() 
	to check if the directory exists. If isdir returns a 1 a 
	1 is returned from this module. Otherwise an error message
	is printed and a 0 is returned.
*/
int chkdst (/*int,*/ char **argv)
{
   int isdir (char *path);

   if(isdir(*argv)) return 1;
   fprintf(stderr, "INPUT DESTINATION DOES NOT EXIST\n");
   return 0;
}

/*	Design a module that takes in a single arg, char *path,
	checks whether it is a directory or not, and returns an
	int. 
	Uses the Stat struct to construct a struct, sbuf,
	and uses stat() to obtain information from the file and
	write it to sbuf. Uses S_ISDIR() on sbuf.st_mode to see 
	the mode of the file. A 1 is returned if the file is a 
	directory otherwise a 0 is returned.
*/
int isdir (char *path)
{
   struct stat sbuf;
   if(stat(path, &sbuf) != 0) return 0;
   return(S_ISDIR(sbuf.st_mode));
}


int isregular (char *path)
{
   struct stat sbuf;
   stat(path, &sbuf);
   return(S_ISREG(sbuf.st_mode));
}


int isvalid(char *path, char *dst)
{
   if (isdir(path))
   {
      fprintf(stderr, "%-5s: not a regular file\n", path);
      return 0;
   }
   else if (!isregular(path))
   {
      fprintf(stderr, "%-5s: no such file or dir\n", path);
      return 0;
   }
   else if (dst == NULL)
   {
      fprintf(stderr, "%-5s: dest creation error\n", path);
      return 0;
   }

   return 1;
}


int copyfiles (int argc, char *argv[])
{
   void buildpath (char *src, char *dst, char **dstpath);
   int makecp (char *srcpath, char *dstpath);

   int i = 1, copies = 0;
   for (i = 1; i < argc - 1; i++)
   {
      char *dstpath;
      buildpath(argv[i], argv[argc - 1], &dstpath);

      if(!isvalid(argv[i], dstpath)) continue;

      if (isregular(dstpath))
      {
         fprintf(stderr, "%-5s: exist at destination\n", argv[i]); continue;
      }

      if (!makecp(argv[i], dstpath)) continue;

      copies++;
   }

   if (!copies) return 1;      
   
   fprintf(stderr, "\n%d copies created successfully.\n", copies);
   return 0;
}


int makecp (char *srcpath, char *dstpath)
{
   int fd, rd, copy;  char bufs[64];
   copy = open(dstpath, O_CREAT | O_WRONLY, 0644);

   if ((fd = open(srcpath, O_RDONLY)) < 0) return 0;

   while((rd = read(fd, bufs, 64)) > 0)
   {
      if(write(copy, bufs, rd) != rd)
      {
         close(fd);
         return 0;
      }
   }

   close(fd);
   return 1;
}


void buildpath (char *src, char *dst, char **dstpath)
{
   char *ptr; int n;
   ptr = strrchr(src, '/');

   if(ptr)
      n = strlen(dst) + strlen(ptr) + 2;
   else
      n = strlen(dst) + strlen(src) + 2;

   *dstpath = malloc(n);

   if(!dstpath) return;

   if(ptr)
   {
      strcpy(*dstpath, dst); strcat(*dstpath, ptr);
   }
   else
   {
      strcpy(*dstpath, dst); strcat(*dstpath, "/"); strcat(*dstpath, src);
   }
}
