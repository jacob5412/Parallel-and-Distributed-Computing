/*Scheduling clause to learn the use of dynamic scheduling*/

#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#define THREADS 4
#define N 16

int fib(int x)
{
    if (x <= 1)
        return x;
    return fib(x - 1) + fib(x - 2);
}

int main()
{
    int i, j, k;
    printf("Using a chunk size of 4: \n");
    for (j = 0; j < 4; j++)
    {
    #pragma omp parallel for schedule(dynamic, 4) num_threads(THREADS)
        for (i = 0; i < N; i++)
        {
            printf("Fibonacci is %d\n", fib(i));
            printf("Thread %d has completed iteration %d.\n", omp_get_thread_num(), i);
        }
    #pragma omp barrier
    }
    /* all threads done */
    printf("All done!\n");

    printf("Using a chunk size of 8: \n");
    for (j = 0; j < 4; j++)
    {
    #pragma omp parallel for schedule(dynamic, 8) num_threads(THREADS)
        for (i = 0; i < N; i++)
        {
            printf("Fibonacci is %d\n", fib(i));
            printf("Thread %d has completed iteration %d.\n", omp_get_thread_num(), i);
        }
    #pragma omp barrier
    }
    /* all threads done */
    printf("All done!\n");

    return 0;
} /*OpenMP program to employ reduction clause to express the reduction of a for loop. */
