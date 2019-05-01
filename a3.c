/*
	Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 03
        Due: February 1, 2019                                           Started: January 30, 2019
        Credit: 10 points.

        Problem: Write a program that uses a linked list data structure to create a random list of odd numbers
        and a list of even numbers. For each list node (lnode) it has a value and a pointer to the next
        node. The program will take an integer argument to determine how many integers are to be generated.
	afterward the odds list and the evens list is printed.

	Solution: Both lists is started at null with the first entry in each list replacing that with its node.
	each number is generated by nextnum() that is selected within the defined RANGE and then checked to be
	even or odd with a bitwise operator (&) then stored in its respective list. When a new node is created
	it has memory allocated to it with malloc() then it is added to the front of the list iff it is not already
	in the list using the insertinlist() function. This is then looped the specified amount of time given by the
	argument with both final list being printed using the printlist() function on their own separate lines.

	Data-structure used: A singly linked list for the odds and evens list and the array of arguments

	Accessing functions for the data structure: The most notable functions used for the linked list was malloc(),
	free(), rand(), and srand();

	Errors handled: Stops the program if there are not enough arguments to continue or if the argument was <= 0.
	Stops the program if delfromlist() or insertinlist() could not be complete.

	Limitations: This program only generates numbers between 0-4 and this can be changed by changing the RANGE.
	Also, the highest recorded number of repeats this program can do is 100,000,000, anything above that will cause
	linux to kill the program before it can finish.
*/

#include <stdio.h>
#include <stdlib.h>

#define RANGE 5

struct lnode
{
   int value; struct lnode *next;
};
typedef struct lnode lnode;

/* Contains the main loop of the program and
   repeats the specified number of times. It
   calls insertinlist() to add them to their
   respective list.
   calls nextnum() to get the next number,
   calls printlist() to print out the specified list  */
int main(int argc, char *argv[])
{
   if (argc < 2 || strtol(argv[1], NULL, 10) <= 0)
   {
      void usage(char *progname);
      char str[] = "a3";
      char *strptr = str;
      usage(strptr);
   }

   void freelist(lnode **list);
   int insertinlist(lnode **list, int x);
   int nextnum();
   void printlist(lnode *list);
   int repeat = strtol(argv[1], NULL, 10);

   lnode *lodds = NULL;
   lnode *levens = NULL;

   int i = 0;
   for(i = 0; i < repeat; i++){
      int newnum = nextnum();

      if(newnum & 1)
      {
         if(!insertinlist(&lodds, newnum)) exit(0);
      }
      else
      {
         if(!insertinlist(&levens, newnum)) exit(0);
      }
   }

   printf("odd-list:");  printlist(lodds);
   printf("even-list:"); printlist(levens);

   freelist(&lodds);
   freelist(&levens);

   return 1;
}

/* Prints usage to stderr and terminates */
void usage(char *progname)
{
   fprintf(stderr, "./%s <rep-count>\n", progname); exit(1);
}

/* Generates the next number */
int nextnum()
{
   return (rand() % RANGE);
}

/* Gets a node for list using malloc(). The caller should check
   for call failure */
void getnode(lnode **ptr)
{
   *ptr = malloc(sizeof(lnode));
}

/* Returns node storage to system using free(). */
void freenode(lnode **ptr)
{
   if(*ptr) free(*ptr);
   *ptr = NULL;
}

/* Searches list for node containing x, if found crnt is
   defined and pred points to crnt’s predecessor node.
   Crnt is undefined otherwise and pred has no meaning. */
void search(lnode *list, lnode **crnt, lnode **pred, int x)
{
   *crnt = list;
   *pred = NULL;
   while(*crnt)
   {
       if((*crnt)->value == x) return;
       *pred = *crnt;
       *crnt = (*crnt)->next;
   }
}

/* Inserts x at the front of list if found in list, deletes it
   from the list otherwise. Returns 1 on success, 0 otherwise,
   calls search() */
int insertinlist(lnode **list, int x)
{
   int delfromlist(lnode **list, lnode *after);

   lnode *crnt = NULL, *pred = NULL;
   lnode *ptr; getnode(&ptr); ptr->value = x;

   search(*list, &crnt, &pred, x);

   if(crnt)
   {
       if(!delfromlist(list, pred)) exit(0);
       return 1;

   }
   else
   {
      if(!*list) 
      {
         *list = ptr;
         (*list)->next = NULL;
         return 1;
      }
      else
      {
         ptr->next = *list;
         *list = ptr;
         return 1;
      }
   }

   return 0;
}

/* Deletes the node from list that is successor of the node
   pointed by after. Returns 1 on success, 0 otherwise. */
int delfromlist(lnode **list, lnode *after)
{
   if(!after) return 1;
   lnode *crnt = *list;
   while(crnt)
   {
      if(crnt == after)
      {
         crnt->next = after->next->next;
         after = NULL;
         freenode(&after);
         return 1;
      }

      crnt = crnt->next;
   }

   return 0;
}

/* Prints the contents of given list (on one line on stdout) */
void printlist(lnode *list)
{
   lnode *crnt = list;

   if(!crnt) printf(" empty");

   while (crnt)
   {
      printf(" %d", crnt->value);
      crnt = crnt->next;
   }

   printf("\n");
}

/* Returns the node storage to system for nodes in the list, one
   node at a time. Calls freenode(). Returns empty list to caller. */
void freelist(lnode **list)
{
   lnode *ptr, *tp;
   ptr = *list;
   while(ptr)
   {
      tp = ptr;
      ptr = ptr->next;
      freenode(&tp);
   }
   *list = NULL;
}