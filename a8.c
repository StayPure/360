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
    int j = 0, i = 0;
    for (i = 0; i < nstudents; i++)
    {  
      scanf("%d %d %d", &data[j], &data[j + 1], &data[j + 2]);
      if (data[j] == -1 || data[j + 1] == -1 || data[j + 2] == -1)
      {
          data[j] = 0; data[j + 1] = 0; data[j + 2] = 0; i--;
          break;
      }
      j += 3;
    }
    return i;
}

void procdata(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean)
{
    int mean[3], i, sum = 0;
    for (i = 0; i < (nstudents * 3); i += 3) sum += tscores[i];
    mean[0] = sum / nstudents; 
    sum = 0;

    for (i = 1; i < (nstudents * 3); i += 3) sum += tscores[i];
    mean[1] = sum / nstudents; 
    sum = 0;

    for (i = 2; i < (nstudents * 3); i += 3) sum += tscores[i];
    mean[2] = sum / nstudents;

    *meanofmean = (mean[0] + mean[1] + mean[2]) / 3;
    *lowmean = mean[0]; *highmean = mean[0];

    for(i = 0; i < 3; i++)
    {
        if (*lowmean > mean[i]) *lowmean = mean[i];
        if (*highmean < mean[i]) *highmean = mean[i];
    }
}

void printresults(char *label, int mlow, int mhigh, int mmean)
{
    fprintf(stdout, "\n%s:\n", label);
    fprintf(stdout, "Highest Mean: %-5d\n", mhigh);
    fprintf(stdout, "Mean of Means: %-5d\n", mmean);
    fprintf(stdout, "Lowest Mean: %-5d\n\n", mlow);
}