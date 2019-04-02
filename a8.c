#include <stdlib.h>
#include <stdio.h>

int main() 
{
    int getcount();
    int getdata(int data[], int nstudents);
    void procdata(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean);
    void printresults(char *label, int mlow, int mhigh, int mmean);
    extern void procdata1(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean);
    int *scores, lowmean, highmean, meanofmean;
    int num = getcount();
    scores = (int *)malloc(sizeof(int) * (num * 3));
    num = getdata(scores, num);
    procdata(scores, num, &lowmean, &highmean, &meanofmean);
    printresults("Procdata", lowmean, highmean, meanofmean);
    procdata1(scores, num, &lowmean, &highmean, &meanofmean);
    printresults("Procdata1", lowmean, highmean, meanofmean);
    exit(0);
}

int getcount()
{
    int count;
    scanf("%d", &count);
    return count;
}

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

void printresults(char *label, int mlow, int mhigh, int mmean)
{
    fprintf(stdout, "\n%s:\n", label);
    fprintf(stdout, "Highest Mean: %-5d\n", mhigh);
    fprintf(stdout, "Mean of Means: %-5d\n", mmean);
    fprintf(stdout, "Lowest Mean: %-5d\n\n", mlow);
}
