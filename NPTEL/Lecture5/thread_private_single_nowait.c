/*Illustration of how no wait removes synchronization*/

#include <stdio.h>
#include <omp.h>

int main()
{
    int numt;

    #pragma omp parallel default(shared)
    {
        int j, tid = omp_get_thread_num();
        #pragma omp single nowait
        {
            for (j = 0; j < 100000; j++);
            numt = omp_get_num_threads();
        } //does not provide synchronization

        #pragma omp barrier
        printf("Hello world from thread %d of %d\n", tid, numt);
    }
}