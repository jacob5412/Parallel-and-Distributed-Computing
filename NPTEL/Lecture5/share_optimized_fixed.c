/*Use #pragma parallel directive (join) as synchronization mechanism*/

#include <omp.h>
#include <stdio.h>

int main(int *argc, char *argv[])
{
    int numt, j;
    omp_set_num_threads(4);

#pragma omp parallel default(shared)
    {
        int tid = omp_get_thread_num();

        if(tid == 0)
        {
            /*Introduce a long wait*/
            for (j = 0; j < 10000000; j++);
            numt = omp_get_num_threads();
        }
    }
//point of synchronization
//again single thread execution
//wait for all threads to join

#pragma omp parallel default(shared)
    {
        int tid = omp_get_thread_num();
        printf("Hello World from thread %d of %d\n", tid, numt);
    }

    return 0;
}
