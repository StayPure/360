#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
if (argc == 1) usage("copy");
   else if (argc > 1) copyfiles(argc, argv);
}

void usage (char *progname)
{

}

void die (char *reason)
{

}

int chkdst (int argc, char **argv)
{

}

int isdir (char *path) 
{

}

int isregular (char *path)
{

}

int copyfiles (int argc, char *argv[])
{        
   void buildpath (char *src, char *dst, char **dstpath);
   int makecp (char *srcpath, char *dstpath);

   int i = 1, copies = 0;
   for (i = 1; i < argc; i++)
   {
      if (!isregular(argv[i]) || !isdir(argv[i])) continue;

      char *dstpath;
      buildpath(argv[i], argv[argc - 1], &dstpath);

      if (!makecp(argv[i], dstpath)) continue;

      copies++;
   }

   if (!copies) return 1;

   return 0;
}

int makecp (char *srcpath, char *dstpath)
{
   int fd, rd; /*char buffs[64];*/

   if ((fd = open(srcpath, O_RDONLY)) < 0) return 0;

   while((rd = read(fd, dstpath, rd)) > 0)
   {
      if(write(1, dstpath, rd) != rd)
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

   printf("%s \n", *dstpath);
}