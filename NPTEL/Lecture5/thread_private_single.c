/*Use more convention approach for work to be done
by a single thread - #pragma omp single*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int numt;

#pragma omp parallel default(shared)
    {
        int j, tid = omp_get_thread_num();
        #pragma omp single
        {
            for (j = 0; j < 100000; j++);
            numt = omp_get_num_threads();
        }//provides a implicit barrier

#pragma omp barrier
        printf("Hello world from thread %d of %d\n", tid, numt);
    }
}