/*
        Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 10
        Due: April 24, 2019                                             Started: April 20, 2019
        Credit: 10 points.

        Problem: Design a program that implements a 4 way associative cache with a total of 4096
        cache lines with each cache line coming from a given address thats 32 bits long. Each data
        block is 64 bytes or 16 32 bit words. The program will need to have two options for
        choosing a victim, these two options will be the random option and the first in first out
        option (FIFO). Random policy of choosing a victim is done by randomly selecting a cache
        line in a full set and replacing it with the new cache line. First in first out policy of
        choosing a victim is done by selecting the oldest cache line in the set and replacing it with
        the new cache line while also incrementing the ages of all the other cache lines in the set
        by 1.

        Solution: The program starts by checking the arguments given making sure they are correct if
        it is not correct the program will end giving the reason its did or just the usage of the
        program. Once the arguments are checked the program initiates the cache and sets the victim
        picking policy. Once all this is done, the program process through each reference in the given
        file and it places it into the cache choosing victims when necessary using the policy specified
        on start. After all the references have been added print the number of references cached and
        the number of misses all alongside the policy selected.

        Data-structure used: A struct, cache line which had elements age, valid, tag and an Array of
        cache lines called l1 that acts as the overall cache.

        Accessing functions for the data structure: Standard C functions for accessing arrays.

        Errors handled: Checks the arguments for the correct amount, if it was either random or fifo.

        Limitations: The program has a limited number of sets and cache lines, so anything above that
        would result in things being lost.

        Acknowledgment: We wrote the program together but we had a lot of help from our classmates
        throughout the making of it.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SETS 1024
#define LINES 4
struct cacheline
{
   char valid;
   unsigned char age;
   int tag;
};
typedef struct cacheline cache;
cache l1[SETS * LINES];
int reference, miss;


int main(int argc, char *argv[])
{
   void checkargs(int argc, char *argv[]);
   void initcache(void);
   void printrslts(char *policy);
   void processreffile(int policy);

   checkargs(argc, argv);
   initcache();
   srand(time(NULL));
   int victimpicker;
   if (strcmp(argv[1], "fifo"))
      victimpicker = 1;
   else
      victimpicker = 0;

   processreffile(victimpicker);

   printrslts(victimpicker ? "Random" : "FIFO");
   exit(0);
}


/* Design a module that checks the arguments passed in by the user.
   This module checks to see if the number of args passed in is equal
   to two. If the number of args is not equal to two, it is passed to
   usage() ending the program. It also checks to see if the args passed
   in are both "fifo" and "random", if so it is passed to die() and the
   program is terminated.
   Called by main().
*/
void checkargs(int argc, char *argv[])
{
   void die(char *reason);
   void usage(char *progname);

   if (argc != 2)
      usage("a10");
   else if (strcmp(argv[1], "fifo") && strcmp(argv[1], "random"))
      die("Polciy was incorrect, choices are: \"fifo\" or \"random\"");
}


/* Design a module that prints out the correct way to use the program
   using the progname to get the name of the program ending the program
   afterwards.
   Takes progname and print out the correct usage of the program to
   stderr then exits the program with a failure.
   Called by main().
*/
void usage(char *progname)
{
   fprintf(stderr, "./%s <algo> < <inputfile>\n", progname);
   exit(1);
}


/* Design a module that prints out the reason for why the program was
   terminated and then terminates the program.
   Takes in a char reason and then prints out that reason to stderr
   then exits the program.
   Called by checkargs().
*/
void die(char *reason)
{
   fprintf(stderr, "%s\n", reason);
   exit(1);
}


/* Design a module that prints out the results of the executed program.
   Takes in a single parameter, char policy, and prints out the policy
   with the number of references and misses executed during the program
   to stdout.
   Called by main().
*/
void printrslts(char *policy)
{
   fprintf(stdout, "%s:\t%d references, %d misses\n", policy, reference, miss);
}


/* Design a module that finds out if the given reference is a hit in
   the cache.
   Takes in a single parameter, a unsigned ref, and gets the index
   and tag. It then checks the cache index calculated from the reference
   and checks the cache to see if the tag is located. If the tag is
   located and is valid a 1 is returned otherwise a 0 is returned.
   Called by processreffile().
*/
int isahit(unsigned ref)
{
   int indx = ((ref >> 6) & 0x3ff) << 2, tag = (ref >> 16) & 0xffff, i;

   for (i = 0; i < 4; i++)
      if (l1[indx + i].valid && l1[indx + i].tag == tag)
         return 1;
   return 0;
}


/* Design a module that initiates the cache array full of empty cache
   lines.
   Goes through each index in the main cache array and adds a cache
   line with 0 age, a 0 tag, and mark it as non-valid. The main purpose
   of this module is so when checking for a hit or miss you actually
   have something to check.
   Called by main().
*/
void initcache(void)
{
   int i = 0;
   for (i = 0; i < SETS * LINES; i++)
   {
      cache new;
      new.age = 0;
      new.tag = 0;
      new.valid = 0;
      l1[i] = new;
   }
}


/* Design a module that processes a references and stores it into the
   cache.
   This module takes in 2 parameters, a unsigned ref and cache new which
   is a cache line. It obtains a tag from the ref and assigns it to the
   cache that was passed to it.
   Called by processreffile().
*/
void processref(unsigned ref, cache *new)
{
   int tag = (ref >> 16) & 0xffff;

   new->tag = tag;
   new->age = 0;
}


/* Design a module that checks for empty cache lines in a set and
   replaces them with a given cache line.
   Goes through each cache line in the specified set checking for empty
   slots if there are no empty slots it returns a 0 if it has a empty
   it fills it with the given cache line and return 1 indicating it was
   filled.
   Called by randomalgo() and fifoalgo().
*/
int emptyfiller(int indx, cache *line)
{
   int i;
   for (i = indx; i < indx + 4; i++)
   {
      if (!l1[i].valid)
      {
         l1[i] = *line;
         return 1;
      }
   }
   return 0;
}


/* Design a module that random picks a victim to be replaced for a new
   specified line.
   The given reference is parsed to find the set index the set is
   checked for empties and if there is it will occupy that space if not
   however then a victim will be chosen by random and the input
   reference takes that spot.
   Called by processreffile().
*/
void randomalgo(cache *line, unsigned ref)
{
   int indx = ((ref >> 6) & 0x3ff) << 2;

   line->valid = 1;
   if (emptyfiller(indx, line))
      return;

   int r = (rand() % (3 + 1));
   l1[indx + r] = *line;
}


/* Design a module that finds the oldest cache line in the set and
   replace it with the new cache line and incrementing all of the other
   cache line's ages by one.
   The given reference is parsed to find the set index the set is
   checked for empties and if there is it will occupy that space if
   not however then a victim will be chosen by first finding the
   oldest cache line and replace with the new line and increment the
   ages for all the other cache lines in the set.
   Called by processreffile().
*/
void fifoalgo(cache *line, unsigned ref)
{
   int indx = ((ref >> 6) & 0x3ff) << 2, i = 0;
   int max = 0, maxindx = 0;
   line->valid = 1;
   if (emptyfiller(indx, line))
      return;

   for (i = indx; i < (indx) + 4; i++)
   {
      if (l1[i].age > max)
      {
         max = l1[i].age;
         maxindx = i;
      }
   }

   for (i = indx; i < (indx) + 4; i++)
   {
      if (i == maxindx)
         continue;
      else
         l1[i].age++;
   }

   l1[maxindx] = *line;
}


/* Design a module that goes the each reference in a given file and
   put it into the cache and if the set is full use the specified victim
   policy to select a victim and replace it with the new cache line.
   An integer for the next references is created and is used to hold
   the next reference and is put through scanf() to check if there is
   a next reference and if so use it. For each reference the counter
   reference is incremented then it checks if it is a hit. if not the
   miss counter is incremented and the reference is processed then put
   through the specified policy.
   Called by main().
*/
void processreffile(int policy)
{
   int nextref;
   while (scanf("%x", &nextref) != EOF)
   {
      reference++;
      if (!isahit(nextref))
      {
         miss++;
         cache new;
         processref(nextref, &new);

         if (policy)
            randomalgo(&new, nextref);
         else
            fifoalgo(&new, nextref);
      }
   }
}
