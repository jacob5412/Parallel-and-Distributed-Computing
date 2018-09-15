/*Compute the sum of elements in an array - Parallel code*/

#include <omp.h>
#include <stdio.h>

#define ARR_SIZE 1000000000
int a[ARR_SIZE];

int main()
{
    int i, tid, numt, sum = 0;
    double t1, t2;

    /*initialize array*/
    for (i = 0; i < ARR_SIZE; i++)
        a[i] = 1;

    t1 = omp_get_wtime();
    /*Do sum in paralle*/
    #pragma omp parallel default (shared) private(i,tid)
    {
        tid = omp_get_thread_num();
        numt = omp_get_num_threads();
        for (i = 0; i < ARR_SIZE; i++)
            sum += a[i];
    }
    t2 = omp_get_wtime();

    printf("Sum of the array elements = %d. Time = %g\n", sum, t2 - t1);

    return 0;
}

/*
Output:
Sum of the array elements = 1742117871. Time = 20.272
* multiple threads access same shared variable sum
* cache coherency causes multiple threads to update sum value 
* cache coherency overhead causes increase in time
*/
