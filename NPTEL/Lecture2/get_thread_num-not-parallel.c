/*What happens if we declare numt and tid outside the parallel block? */

#include <omp.h>
#include <stdio.h>

int main(int *argc, char *argv[])
{
    /*Declare numt and tid outside the parallel block*/
    int numt,tid;
    //since numt and tid are shared variables
    //a race condition may occur - trying to update the variable at the same time
    //hence a printed tid may be repeated by different threads
#pragma omp parallel
    {
        numt = omp_get_num_threads();
        tid = omp_get_thread_num();
        printf("Hello World from thread %d of %d\n", tid, numt);
    }

    return 0;
}
