/*Getting number of threads and thread id*/

#include <omp.h>
#include <stdio.h>

int main( int *argc, char *argv[] )
{
    int numt, tid;
    /*Specify private and shared variables*/
    #pragma omp parallel private(tid) shared(numt)
    {
        //private = every thread has own copy of variable (private copy)
        //shared = variable is global. shared by all threads. 
        //all threads see same memory location. 
        //by default, variables are shared if declared outside parallel region

        numt = omp_get_num_threads();
        tid = omp_get_thread_num();

        printf("Hello World from thread %d of %d\n",tid,numt);

    }

    return 0;
}