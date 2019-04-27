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
   Called by main().
*/
void usage(char *progname)
{
    fprintf(stderr, "./%s <algo> < <inputfile>\n", progname); exit(1);
}


void die(char *reason)
{
    fprintf(stderr, "%s\n", reason); exit(1);
}

void printrslts(char *policy)
{
  fprintf(stdout, "%s:\t%d references, %d misses\n", policy, reference, miss);  
}

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
