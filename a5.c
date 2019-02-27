/*
	Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 05
        Due: February 26, 2019                                          Started: February 23, 2019
        Credit: 10 points.

	Problem: Write a program that simulates different combination circuits using only bitwise
	operations. The different circuits will have inputs that comes from command line arguments
	which comes in base-16. The program will not use any control-flow (if-then-else, for/while).
	The three main categories that the different circuits this program simulates is adders, parity,
	multiplexers. The adders have half, full, ripple-carry, and look-ahead. The parity have even
	parity 3-bit generator and odd parity 4-bit checker. The multiplexer has 2x1 multiplexer and
	4x1 multiplexer. The output of this program will be the binary of the different numbers that
	these different circuits will output.

	Solution: Each circuit need it different logic gates that were created using the different
	bitwise operators. Some circuits also works by using the other circuits in the program. The
	main example that really shows this is ripple-carry adder which uses 4 full adders to instead
	of only adding 1 bit it now adds 4 bits. The program reads in hexadecimal numbers from the
	command-line then does then sends the appropriate numbers through the adders then all the other
	operations.

	Data-Structure used: None.

	Accessing functions for the data structure: None.

	Errors handled: The program will not run unless the you have more than 4 arguments, if you do
	the program tells you the correct usage and ends program.

	Limitations: The program takes the argument 1, 2, and 3 to find the main inputs, However, if these
	are incorrect inputs then it stops the program from doing the operations correctly.

	Acknowledgment: We wrote the program together but we had a lot of help from I our classmates
	throughout the making of it.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   if (argc < 4)
   {
      void usage(char *progname);
      char str[] = "a3", *strptr = str;
      usage(strptr);
   }

   int a = strtol(argv[1], NULL, 16);
   int b = strtol(argv[2], NULL, 16);
   int c = strtol(argv[3], NULL, 16);
   void doadders(int a, int b, int c);
   void doextraops(int a, int b);

   doadders(a, b, c);
   doextraops(a, b);

   return 0;
}


/* Prints usage/hint to stderr, terminates execution using exit() */
void usage(char *progname)
{
   fprintf(stderr, "./%s <arg-a> <arg-b> <arg-c>\n", progname); exit(1);
}


/* Do all the add operations, this includes halfadder, fulladder,
ripple-carry adder, and look-ahead adder. Afterwards the result
is printed with printresult() */
void doadders(int a, int b, int c)
{
   void fulladdr(int a, int b, int incary, int *sum, int *outcary);
   void halfaddr(int a, int b, int *sum, int *outcary);
   void lacadd4(int a, int b, int incary, int *sum, int *outcary);
   void printresult(char *label, int a);
   void rcadd4(int a, int b, int incary, int *sum, int *outcary);
   int sum, outcary, *s = &sum, *o = &outcary;

   printf("%s\n", "halfadder:");
   halfaddr(a, b, s, o);
   printresult("sum:", sum); printresult("outcary:", outcary); putchar('\n');

   printf("%s\n", "fulladder:");
   fulladdr(a, b, c, s, o);
   printresult("sum:", sum); printresult("outcary:", outcary); putchar('\n');

   printf("%s\n", "racadd4 (4-bit-adder):");
   rcadd4(a, b, c, s, o);
   printresult("sum:", sum); printresult("outcary:", outcary); putchar('\n');

   printf("%s\n", "lacadd4 (4-bit-adder):");
   lacadd4(a, b, c, s, o);
   printresult("sum:", sum); printresult("outcary:", outcary); putchar('\n');
}


/* Do all the extra operations, this includes even parity 3-bit generator,
odd parity 4-bit check, modulus of a 4-bit number, multiplexer 2x1 and 4x1.
Afterwards the result is printed with printresult() */
void doextraops(int a, int b)
{
   int ans, *ptrans = &ans;
   void evenparity3gen(int a, int *paritybit);
   void modulus4bit(int a, int *rslt);
   void mux2by1(int a, int b, int *yout);
   void mux4by1(int a, int b, int *yout);
   void oddparity4chk(int a, int *checkbit);
   void printresult(char *label, int a);

   evenparity3gen(a, ptrans);
   printf("%s\n", "evenparity3gen:"); printresult("paritybit:", ans); putchar('\n');

   oddparity4chk(a, ptrans);
   printf("%s\n", "oddparity4chk:"); printresult("checkbit:", ans); putchar('\n');

   modulus4bit(a, ptrans);
   printf("%s\n", "modulus4bit"); printresult("rslt:", ans); putchar('\n');

   mux2by1(a, b, ptrans);
   printf("%s\n", "mux2x1"); printresult("yout:", ans); putchar('\n');

   mux4by1(a, b, ptrans);
   printf("%s\n", "mux4x1"); printresult("yout:", ans); putchar('\n');
}


/*  Simulates a half adder using bitwise operators on our inputs a and b that results in our
  outcarry and sum variables. */
void halfaddr(int a, int b, int *sum, int *outcary)
{
   *outcary = (a & 1) & (b & 1);
   *sum = (a & 1) ^ (b & 1);
}


/* Simulates a full adder. We take the two inputs and get the last bit and apply
  boolean algebra in-order to get the sum and outcarry. */
void fulladdr(int a, int b, int incary, int *sum, int *outcary)
{
   int a0, b0, ci;
   a0 = a & 1; b0 = b & 1; ci = incary & 1;
   *sum = a0 ^ b0 ^ ci;
   *outcary = (a0 & b0) | (ci & (a0 | b0));
}


/* Simulates a ripple carry adder. This is done by splitting our inputs, a and b, bits and doing one
  full adder at a time. The outcarry from one full adder is then applied as the incarry for the next
  full adder and this continues for the next two full adders. */
void rcadd4(int a, int b, int incary, int *sum, int *outcary)
{

   int sum1, sum2, sum3, sum4;
   int *s1 = &sum1, *s2 = &sum2, *s3 = &sum3, *s4 = &sum4;

   fulladdr(a&1,b&1,incary, s1, outcary);
   fulladdr((a>>1)&1,(b>>1)&1,*outcary, s2, outcary);
   fulladdr((a>>2)&1,(b>>2)&1,*outcary, s3, outcary);
   fulladdr((a>>3)&1,(b>>3)&1,*outcary, s4, outcary);

   *sum = (sum4 << 3) | (sum3 << 2) | (sum2 << 1) | sum1;
}


/* Simulates a look ahead carry adder. This method uses boolean algebra and bitwise ops in order
  to generate all the incarries for each full adder. Once each incarry is generated we apply each
  to it's specific full adder. */
void lacadd4(int a, int b, int incary, int *sum, int *outcary)
{
   int a1 = (a & 1), a2 = (a >> 1) & 1, a3 = (a >> 2) & 1, a4 = (a >> 3) & 1;
   int b1 = (b & 1), b2 = (b >> 1) & 1, b3 = (b >> 2) & 1, b4 = (b >> 3) & 1;

   int c1 = (a1 & b1) | ((a1 ^ b1) & incary);
   int c2 = (a2 & b2) | ((a2 ^ b2) & c1);
   int c3 = (a3 & b3) | ((a3 ^ b3) & c2);
   *outcary = (a4 & b4) | ((a4 ^ b4) & c3);

   int sum1, sum2, sum3, sum4;
   int *s1 = &sum1, *s2 = &sum2, *s3 = &sum3, *s4 = &sum4;

   fulladdr(a1, b1, incary, s1, outcary);
   fulladdr(a2, b2, c1, s2, outcary);
   fulladdr(a3, b3, c2, s3, outcary);
   fulladdr(a4, b4, c3, s4, outcary);
   *sum = (sum4 << 3) | (sum3 << 2) | (sum2 << 1) | sum1;
}


/* Generates the even parity bit for lower order three bits in our input, a. This is done by
  separating our input into 3 bits and applying boolean algebra on it. */
void evenparity3gen(int a, int *paritybit)
{
   int x = (a >> 2) & 1;
   int y = (a >> 1) & 1;
   int z = a & 1;

   *paritybit = (x ^ y) | z;
}


/* Checks the odd parity bit for lower order 4 bits in our input, a, using a checkbit pointer. This is done by
  separating our input into 4 bits and applying boolean algebra on it then checking if it is equal to the value
  pointed at from our check bit. */
void oddparity4chk(int a, int *checkbit)
{
   int w = (a >> 3) & 1;
   int x = (a >> 2) & 1;
   int y = (a >> 1) & 1;
   int z = a & 1;
   *checkbit = ((w ^ x) ^ (y ^ z)) ^ 1;
}


/* Finds the modulus of a 4 bit 2's complement number using a rcadd4() and 4 xor gates. */
void modulus4bit(int a, int *rslt)
{
   int a3 = ((a >> 3) & 1);
   int na0 = (a & 1) ^ a3;
   int na1 = ((a >> 1) & 1) ^ a3;
   int na2 = ((a >> 2) & 1) ^ a3;
   int na3 = ((a >> 3) & 1) ^ a3;

   int na = (na3 << 3) | (na2 << 2) | (na1 << 1) | na0;
   int out, *ptro = &out;
   rcadd4(na, 0, a3, rslt, ptro);
}


/* Simulated 2x1 multiplexer. This is done by using boolean algebra and bitwise operators on
  our inputs, a and b. */
void mux2by1(int a, int b, int *yout)
{
   int i0 = a & 1;
   int i1 = (a >> 1) & 1;
   int s = b & 1;

   *yout = (i0 & (s ^ 1)) | (i1 & s);
}


/* Simulated 4x1 multiplexer. This is done by using boolean algebra and bitwise operators on
  our inputs, a and b. */
void mux4by1(int a, int b, int *yout)
{
   int i0 = a & 1;
   int i1 = (a >> 1) & 1;
   int i2 = (a >> 2) & 1;
   int i3 = (a >> 3) & 1;

   int b0 = b & 1;
   int b1 = (b >> 1) & 1;

   *yout = ((b0 & (~1)) & i0 & (b1 & (~1))) | (b0 & i1  & (b1 & (~1))) | ((b0 & (~1)) & i2 & b1) | (b0 & i3 & b1);
}



/* Prints the results of the label and its value, a. This then calls printbits() in order to print out a in bits. */
void printresult(char *label, int a)
{
   void printbits(int x);

   printf("%-16s", label);
   printbits(a);
}


/* Prints out the bits of x */
void printbits(int x)
{
    int i, j;
    for(i = 31, j = 0; i >= 0; i--, j++) {
        if ((j & 0x7)  == 0) putchar(' ');
        (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}
