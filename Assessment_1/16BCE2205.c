#include <stdio.h>
#include <omp.h>

int tid;

#pragma omp threadprivate(tid)
//creating the tid variable as threadprivate for persistent storage
int main()
{
    int i, j, k, numt = 0;

    //parallelize the for loop
    #pragma omp parallel for default(shared)
    for(i = 1; i < 100000; i ++)
    {
        tid = omp_get_thread_num();
        for(j = 0; j < 10; j++);
        //explicit wait to prevent race conditions
        k = k + i;

        if(tid == 0)
        //single thread in execution determines no. of threads
        {
            //wait to prevent race conditions
            for(j = 0; j < 10; j ++);
            numt = omp_get_num_threads();
        }
    }

    //introduce a synchronization point for programs
    #pragma omp barrier
    printf("%d was caculated by %d threads\n",k,numt);

    //get threads that executed the program
    #pragma omp parallel default(shared)
    printf("%d was involved in the calculation\n",tid);
}