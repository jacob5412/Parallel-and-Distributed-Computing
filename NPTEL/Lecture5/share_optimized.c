/*Getting number of threads and thread id*/

#include <omp.h>
#include <stdio.h>

int main(int *argc, char *argv[])
{
    /*Declare and initialize numt outside parallel block*/
    int numt = omp_get_num_threads();

/*Specify private and shared variables*/
#pragma omp parallel default(shared)
    {
        //numt = omp_get_num_threads();
        int tid = omp_get_thread_num();

        printf("Hello World from thread %d of %d\n", tid, numt);
    }

    return 0;
}

/*
Since before parallel region only one thread is executing,
printed out as follows:
Hello World from thread 0 of 1
Hello World from thread 2 of 1
Hello World from thread 1 of 1
Hello World from thread 3 of 1
*/