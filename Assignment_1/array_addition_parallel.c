//Write a simple OpenMP program for array addition (sum).
//we are going to take two one-dimensional arrays, each of size of 5.
//We will then create 5 threads. Each thread will be responsible for one addition operation.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    int a[5], b[5], c[5];
    int i;
    clock_t u;

    printf("-----------------16BCE2205-----------------\n");
    printf("Reading values for array A \n");
    for (i = 0; i < 5; i++)
    {
        printf("Enter a value: ");
        scanf("%d", &a[i]);
    }

    printf("Reading values for array B \n");
    for (i = 0; i < 5; i++)
    {
        printf("Enter a value: ");
        scanf("%d", &b[i]);
    }

    printf("Running program parallely: \n");
    omp_set_num_threads(5);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        u = clock();
        c[tid] = a[tid] + b[tid];
        u = clock() - u;
        printf("There are %d nthreads in execution\n", omp_get_num_threads());
    }

    for (i = 0; i < 5; i++)
        printf("Sum of %d and %d is %d\n", a[i], b[i], c[i]);

    double time_taken_p = ((double)u) / CLOCKS_PER_SEC;
    printf("Running the program parallelly took %f seconds to execute \n", time_taken_p);

    return 0;
}