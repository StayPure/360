
/* Name: Kevin C. Bell, Thomas Jury, Nick Bravada	Class: CPS 360
   Section: 22362460					Assignment: 01
   Due: January 18, 2019				Started: January 15, 2019
   Credit: 10

   Problem: Write a program to find the largest value, the largest value, the smallest value,
   the integer average value, and the count of values that are greater than the average value. 
   The data set itself and the results obtained will be printed on standard output using library
   function printf().

   Solution: */

#include <stdio.h>
#include <stdlib.h>


int main() {
   int data[29] = {1, 2, 3, -3, -99, 999, 42, 14, 56, 76, 99, 12,
  		  -2345, 3456789, 199, 123, 234, -567, -999, 21,
  	 	  32, -12345, 324, 345, 387, 456, 4095, 1999, 8192};
   
   int size;
   int avg, aboveavg, max, min;
   int largest(int d[], int size );
   int smallest(int d[], int size);
   int avrage(int d[], int size);
   int abvaverage(int d[], int size, int average);
   void printdata(int d[], int size);
   void printrslts(int largest, int smallest, int avrage, int abvaverage);

   size = 29;

   if(size > 0) {
       avg = avrage(data, size);
       aboveavg = abvaverage(data, size, avg);
       max = largest(data, size); 
       min = smallest(data, size);

       printdata(data, size);
       printrslts(max, min, avg, aboveavg);
   }

    exit(0);


} 

int largest(int d[], int size) {
   int i = 0, max = 0;
   for (i = 0; i < size; i++) {
      if(max < d[i]){
         max = d[i];
      }
   }

   return max;   
}



int smallest(int d[], int size) {
   int i = 0, min = 0;

   for (i = 0; i < size; i++) {
      if(min > d[i]){
         min = d[i];
      }
   }

   return min;
}


int avrage(int d[], int size) {
   int i = 0, sum = 0, avg = 0;

   for (i = 0; i < size; i++) {
      sum += d[i];
   }

   avg = sum / size;

   return avg;
}


int abvaverage(int d[], int size, int average) {
   int i = 0, count = 0;

   for (i = 0; i < size; i++) {
      if (d[i] > average) {
         count++;
      }
   }

   return count;
}


void printdata(int d[], int size) {
    int i = 0, j = 0;
       for (i = 0; i < size; i++) {
          if(j == 6) {
             printf("%8d\n", d[i]);
             j = 0;

          }else if(i != size - 1){
             printf("%8d,", d[i]);
             j++;

          }else {
             printf("%8d", d[i]);

          }
       }
}


void printrslts(int largest, int smallest, int avrage, int abvaverage) {
    printf("\nlargest = %d, smallest = %d, average = %d, above average = %d\n", largest, smallest, avrage, abvaverage);
}    
