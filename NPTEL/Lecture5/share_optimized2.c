/*Getting number of threads and thread id*/

#include <omp.h>
#include <stdio.h>

int main(int *argc, char *argv[])
{
    int numt;
    omp_set_num_threads(4);
/*Specify private and shared variables*/
#pragma omp parallel default(shared)
    {
        //numt = omp_get_num_threads();
        int tid = omp_get_thread_num();

        if(tid == 0)
            numt = omp_get_num_threads();

        printf("Hello World from thread %d of %d\n", tid, numt);
    }

    return 0;
}

/*
Since execution does not happen in order:
Hello World from thread 0 of 4
Hello World from thread 1 of 1 <-
Hello World from thread 2 of 4
Hello World from thread 3 of 4
*/