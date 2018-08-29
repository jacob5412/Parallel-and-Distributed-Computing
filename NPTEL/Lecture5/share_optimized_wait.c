/*Getting number of threads and thread id*/

#include <omp.h>
#include <stdio.h>

int main(int *argc, char *argv[])
{
    int numt, j;
    omp_set_num_threads(4);
/*Specify private and shared variables*/
#pragma omp parallel default(shared)
    {
        //numt = omp_get_num_threads();
        int tid = omp_get_thread_num();

        if(tid == 0)
        {
            /*Introduce a long wait*/
            for (j = 0; j < 10000000; j++);
            numt = omp_get_num_threads();
        }
        printf("Hello World from thread %d of %d\n", tid, numt);
    }

    return 0;
}
