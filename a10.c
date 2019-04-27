#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SETS 1024
#define LINES 4
struct cacheline{
    char valid; /* for valid/invalid entry */
    unsigned char age; /* for age of entry */
    int tag;
};
typedef struct cacheline cache;
cache l1[SETS * LINES];
int reference, miss; /* keep track of cache misses */

int main(int argc, char *argv[]) 
{
    void checkargs(int argc, char* argv[]);
    int isahit(unsigned ref);
    void initcache(void);
    void printrslts();
    void randomalgo(cache *line, unsigned ref);
    void fifoalgo(cache *line, unsigned ref);
    void processref(unsigned ref, cache *new);

    checkargs(argc, argv);
    int victimpicker;
    if(strcmp(argv[1], "fifo")) victimpicker = 1;
    else  victimpicker = 0;

    initcache();

    int nextref;
    while(scanf("%x", &nextref) != EOF)
    {
        reference++;
        if (!isahit(nextref))
        {
            miss++;
            cache new;
            processref(nextref, &new);
            
            if (victimpicker) randomalgo(&new, nextref);
            else fifoalgo(&new, nextref);
        }
    }
    printrslts();
    exit(0);
}

void checkargs(int argc, char* argv[])
{
    void die(char *reason);
    void usage(char *progname);

    if (argc != 2) usage("a10");
    else if (strcmp(argv[1],"fifo") && strcmp(argv[1],"random")) die("Polciy was incorrect, choices are: \"fifo\" or \"random\"");

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

int isahit(unsigned ref){
    int indx = ((ref >> 6) & 0x3ff) << 2;
    int tag = (ref >> 16) & 0xffff;
    int i;

    for(i=0; i<4; i++) if(l1[indx+i].valid && l1[indx+i].tag == tag) break;
    
    if(i == 4) return 0;
    return 1;
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

void printrslts()
{
  fprintf(stdout, "REFERNCES %d, MISSES: %d\n", reference, miss);  
}

void processref(unsigned ref, cache *new)
{
    int tag = (ref >> 16) & 0xffff;

    new->tag = tag;
    new->age = 0;
}


void randomalgo(cache *line, unsigned ref)
{
    int indx = ((ref >> 6) & 0x3ff) << 2;

    int r = (rand() % (3 + 1));
    line->valid = 1;
    l1[indx + r] = *line;
}

void fifoalgo(cache *line, unsigned ref)
{
    int indx = ((ref >> 6) & 0x3ff) << 2, i = 0;
    int max = 0, maxindx = 0;
    for (i = indx; i < indx+4; i++)
    {
        if (l1[i].age > max) 
        {
            max = l1[i].age; maxindx = i;
        }
    }
    for (i = indx; i < indx+4; i++)
    {
        if (i == maxindx) continue;
        else l1[i].age++;
    }
    line->valid = 1;
    l1[maxindx] = *line;
}
