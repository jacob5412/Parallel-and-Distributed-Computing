//Write a simple program for linear search
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main()
{
    int i, key = 85, tid;
    int a[100];
    clock_t t;

    for(i = 1; i <= 100; i++)
        a[i-1] = i;

    printf("-----------------16BCE2205-----------------");

    t = clock();
    for (i = 0; i < 100; i++)
    {
        if (a[i] == key)
        {
            printf("\nKey found. Position = %d by thread %d \n", i, tid);
        }
    }
    t = clock() - t;

    double time_taken_s = ((double)t) / CLOCKS_PER_SEC;
    printf("Program took %f seconds to execute \n", time_taken_s);
    return 0;
}