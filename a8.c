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
