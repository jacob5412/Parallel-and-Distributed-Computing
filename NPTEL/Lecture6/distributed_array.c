/*Distribute iterations among threads*/

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
    omp_set_num_threads(4);
    #pragma omp parallel default(shared) private(i, tid)
    {
        int from, to;

        tid = omp_get_num_threads();
        numt = omp_get_thread_num();

        /*Distribute the work - compute index range to work on*/
        from = (ARR_SIZE/numt)*tid;
        to = (ARR_SIZE/numt)*(tid + 1) - 1;
        if(tid == numt-1)
            to = ARR_SIZE - 1;
        
        printf("Hello from %d of %d, my range is from = %d to %d\n", tid,numt,from,to);
        for(i = from; i <= to; i++)
            #pragma omp critical
            sum += a[i];
            //critical section
            //only executed by one thread at a time

    }
    t2 = omp_get_wtime();

    printf("Sum of the array elements = %d. Time = %g\n", sum, t2 - t1);

    return 0;
}
