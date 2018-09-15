/*compute the sum of elements in an array - sequential code*/

#include <omp.h>
#include <stdio.h>

#define ARR_SIZE 1000000000
int a[ARR_SIZE];

int main()
{
    int i, sum = 0;
    double t1,t2;

    /*initialize array*/
    for(i = 0; i < ARR_SIZE; i++)
        a[i] = 1;

    t1 = omp_get_wtime();
    /*sum up the array*/
    for(i = 0; i < ARR_SIZE; i++)
        sum += a[i];
    t2 = omp_get_wtime();

    printf("Sum of the array elements = %d. Time = %g\n", sum, t2 - t1);

    return 0;
}