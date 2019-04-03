/*
        Name: Kevin C. Bell, Nicholas J. Bravata, Thomas J. Jury        Class: CPS 360
        Section: 22362460                                               Assignment: 08
        Due: April 3, 2019                                              Started: April 29, 2019
        Credit: 10 points.
        
        Problem: Write a program that will read in exam1, exam2, exam3 scores of students of a class
        from stdin. Then compute the integer mean of scores of a student. Finally it will print the
        lowest mean, highest mean, and mean of the mean-scores of the class.
        
        Solution: When the program starts it first obtains from stdin the number of students. This number
        is then used to make an array for test scores using malloc(), the size of the array is 3*nstudents
        because each student can have 3 exams. After the array is made it is then passed to getdata(), once
        there test scores are read in from stdin and stored into our scores array. The array is then passed
        to procdata() along with nstudents, and pointers highmean, lowmean, meanofmean. This method will 
        produce the mean of each student and calculate the meanofmean. The student with the lowest mean will
        have their mean stored in lowmean and the student with the highest mean will be stored in highmean.
        Finally the results will be printed using the method printresults(). The data will be printed with a 
        meaningful message and label. Before ending the program uses free() on our scores then ends with an 
        EXIT_SUCCESS.
        
        Data-structure used: A one-dimensional array of integers to store student test scores.
        
        Accessing functions for the data structure: Standard C functions for accessing arrays and 
        malloc() to allocate the memory for the student's test scores array.
        
        Errors handled: 
        
        Limitations: 
        
        Acknowledgment:
*/
#include <stdlib.h>
#include <stdio.h>

int main() 
{
   int getcount();
   int getdata(int data[], int nstudents);
   void printresults(char *label, int mlow, int mhigh, int mmean);
   void procdata(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean);
   extern void procdata1(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean);

   int highmean, lowmean,  meanofmean, num = getcount(), *scores;

   scores = (int *)malloc(sizeof(int) * (num * 3));
   num = getdata(scores, num);

   procdata(scores, num, &lowmean, &highmean, &meanofmean);
   printresults("Procdata", lowmean, highmean, meanofmean);

   procdata1(scores, num, &lowmean, &highmean, &meanofmean);
   printresults("Procdata1", lowmean, highmean, meanofmean);

   exit(0);
}

/*Design a module that reads in from stdin using scanf().
  That data that is read in is then returned as the count.
*/
int getcount()
{
   int count;
   scanf("%d", &count);
   return count;
}

/*Design a module that fills an array d[] of size nstudents with student scores read in from stdin and
  returns the count of students actually read in from stdin. Using the scanf() and '%d' 3 test scores 
  are read in at a time and stored into d[] accordingly. Once the 3 tests are entered in a running count
  is incremented up by one. Once i = nstudents or scanf() returns a -1 for one of the tests, the running 
  count is returned.
*/
int getdata(int data[], int nstudents)
{
   int i = 0, j = 0;
   int a, b, c;
   for (i = 0; i < nstudents; i++)
   {
       scanf("%d %d %d", &a, &b, &c);
       if (a == -1 || b == -1 || c == -1) break;
       data[j] = a; data[j + 1] = b; data[j + 2] = c;
       j += 3;
   }
   return i;
}

/*Design a module that takes in an array of test scores, number of students and the returns the lowest, highest,
  and mean of means. Sum, mean, high mean, and low mean are declared and initalized to 0. Using a for loop to go
  through each students exam scores, the average score for that student's exams are stored to the mean and added to
  the overall sum. The mean is then compared to the highmean and lowmean and swaps are made accordingly. Nothing is
  returned but highmean, lowmean, and meanofmean are stored at the end.
*/
void procdata(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean)
{
   int i, sum = 0, mean = 0;
   *lowmean = 0; *highmean = 0;
   for (i = 0; i < (nstudents * 3); i += 3)
   {
       mean = (tscores[i] + tscores[i + 1] + tscores[i + 2]) / 3;
       sum += mean;
       if (*lowmean > mean) *lowmean = mean;
       if (*highmean < mean) *highmean = mean;
   }
   *meanofmean = sum / nstudents;
}

/*Design a module that takes in a char *label, int mlow, int mhigh, and int mmean then prints their results. Using
  printf() to stdout, formating conditions are used to print out each mean and label with it.
*/
void printresults(char *label, int mlow, int mhigh, int mmean)
{
   fprintf(stdout, "\n%s:\n", label);
   fprintf(stdout, "Lowest Mean score\t : %d\n", mlow);
   fprintf(stdout, "Highest Mean score\t : %d\n", mhigh);
   fprintf(stdout, "Mean of Means score\t : %d\n\n", mmean);
}
