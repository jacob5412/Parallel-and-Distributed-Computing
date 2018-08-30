/*Illustration of how #pragma omp master works*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int numt;

    #pragma omp parallel default(shared)
    {
        int j, tid = omp_get_thread_num();
        #pragma omp master
        {
            for (j = 0; j < 100000; j++);
            numt = omp_get_num_threads();
        } //explicitly says only executed by the master
        //master's thread private variables available

        #pragma omp barrier
        printf("Hello world from thread %d of %d\n", tid, numt);
    }
}