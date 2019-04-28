/*
        Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 10
        Due: April 24, 2019                                             Started: April 20, 2019
        Credit: 10 points.
        Problem: Design a program that implements a 4 way associative cache.
        Solution: 
        Data-structure used: A struct, cacheline which had elements age, valid, tag. Another struct cache 
        which is an array size set * lines.
        Accessing functions for the data structure: Basic array indexing.
        Errors handled: Checks the arguments for the correct amount, if it was either random or fifo.
        Limitations: 
        Acknowledgment: We wrote the program together but we had a lot of help from our classmates
        throughout the making of it.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SETS 1024
#define LINES 4
struct cacheline{
    char valid; 
    unsigned char age; 
    int tag;
};
typedef struct cacheline cache;
cache l1[SETS * LINES];
int reference, miss; 


int main(int argc, char *argv[]) 
{
    void checkargs(int argc, char* argv[]);
    void initcache(void);
    void printrslts(char *policy);
    void processreffile (int policy);
    
    checkargs(argc, argv);
    initcache();
    srand(time(NULL));
    int victimpicker;
    if(strcmp(argv[1], "fifo")) victimpicker = 1;
    else  victimpicker = 0;

    processreffile(victimpicker);

    printrslts(victimpicker ? "Random" : "FIFO");
    exit(0);
}

/* Design a module that checks the arguments passed in by the user. 
   This module checks to see if the number of args passed in is equal
   to two. If the number of args is not equal to two, it is passed to 
   usage() ending the program. It also checks to see if the args passed in
   are both "fifo" and "random", if so it is passed to die() and the program is
   terminated.
*/
void checkargs(int argc, char* argv[])
{
    void die(char *reason);
    void usage(char *progname);

    if (argc != 2) usage("a10");
    else if (strcmp(argv[1],"fifo") && strcmp(argv[1],"random")) 
        die("Polciy was incorrect, choices are: \"fifo\" or \"random\"");
}


/* Design a module that prints out the correct way to use the
   program using the progname to get the name of the program
   ending the program afterwards.
   Takes progname and print out the correct usage of the program
   to stderr then exits the program with a failure.
   Called by checkargs().
*/
void usage(char *progname)
{
    fprintf(stderr, "./%s <algo> < <inputfile>\n", progname); exit(1);
}

/* Design a module that prints out the reason for why the program was terminated
   and then terminates the program. 
   Takes in a char reason and then prints out that reason to stderr then exits the 
   program.
   Called by checkargs().
*/
void die(char *reason)
{
    fprintf(stderr, "%s\n", reason); exit(1);
}

/* Design a module that prints out the results of the executed program.
   Takes in a single parameter, char policy, and prints out the policy with
   the number of references and misses executed during the program to stdout.
   Called by main().
*/
void printrslts(char *policy)
{
  fprintf(stdout, "%s:\t%d references, %d misses\n", policy, reference, miss);  
}

/* Design a module that finds out if the given reference is a hit in the cache.
   Takes in a single perameter, a unsigned ref, and gets the index and tag. It 
   then checks the cache index calculated from the reference and checks the cache
   to see if the tag is located. If the tag is located and is valid a 1 is returned
   otherwise a 0 is returned.
   Called by processreffile().
*/
int isahit(unsigned ref){
    int indx = ((ref >> 6) & 0x3ff) << 2
        ,tag = (ref >> 16) & 0xffff
        ,i;

    for(i=0; i<4; i++) if(l1[indx+i].valid && l1[indx+i].tag == tag) return 1;
    return 0;
}


void initcache(void)
{   
    int i = 0;
    for (i = 0; i < SETS*LINES; i++)
    {
        cache new;
        new.age = 0; new.tag = 0; new.valid = 0;
        l1[i] = new;
    }
}

/* Design a module that processes a references and stores it into the cache.
   This module takes in 2 parameters, a unsigned ref and cache new which is a cacheline.
   It obtains a tag from the ref and assigns it to the cache that was passed to it.
   Called by processreffile().
*/
void processref(unsigned ref, cache *new)
{
    int tag = (ref >> 16) & 0xffff;

    new->tag = tag;
    new->age = 0;
}


int emptyfiller (int indx, cache *line)
{
    int i;
    for (i = indx; i < indx+4; i++) 
    {
        if (!l1[i].valid) 
        {
            l1[i] = *line;
            return 1;
        }
    }
    return 0;
}


void randomalgo(cache *line, unsigned ref)
{
    int indx = ((ref >> 6) & 0x3ff) << 2;

    line->valid = 1;
    if (emptyfiller(indx, line)) return;

    int r = (rand() % (3 + 1));
    l1[indx + r] = *line;
}


void fifoalgo(cache *line, unsigned ref)
{
    int indx = ((ref >> 6) & 0x3ff) << 2, i = 0;
    int max = 0, maxindx = 0;
    line->valid = 1;
    if (emptyfiller(indx, line)) return;

    for (i = indx; i < (indx)+4; i++)
    {
        if (l1[i].age > max) 
        {
            max = l1[i].age; maxindx = i;
        }
    }

    for (i = indx; i < (indx)+4; i++)
    {
        if (i == maxindx) continue;
        else l1[i].age++;
    }

    l1[maxindx] = *line;
}

void processreffile (int policy)
{
    int nextref;
    while(scanf("%x", &nextref) != EOF)
    {
        reference++;
        if (!isahit(nextref))
        {
            miss++; cache new;
            processref(nextref, &new);
            
            if (policy) randomalgo(&new, nextref);
            else fifoalgo(&new, nextref);
        }
    }
}
