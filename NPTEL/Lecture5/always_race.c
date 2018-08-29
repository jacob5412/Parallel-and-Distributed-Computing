/*Getting number of threads and thread id*/

#include <omp.h>
#include <stdio.h>

int main( int *argc, char *argv[] )
{
    int numt, tid, j;
    omp_set_num_threads(4);
    #pragma omp parallel
    {

        numt = omp_get_num_threads();
        tid = omp_get_thread_num();

        /*Introduce wait so that other threads get scheduled*/
        for(j = 0; j < 10000000; j++);

        printf("Hello World from thread %d of %d\n",tid,numt);

    }

    return 0;
}