/*Make tid persistent accross parallel sections*/

#include <stdio.h>
#include <omp.h>

int tid;

#pragma omp threadprivate(tid)
//allocate space for tid in thread private region
int main()
{
    int numt;
    
    #pragma omp parallel num_threads(4) default(shared)
    {
        int j;
        tid = omp_get_thread_num();
        if(tid == 0)
        {
            for( j = 0; j < 1000000; j++);
            numt = omp_get_num_threads();
        }
    }
    //synchronization barrier
    #pragma omp parallel num_threads(4) default(shared)
    {
        //no need to make second call to omp_get_thread_num;
        printf("Hello world from thread %d of %d\n",tid,numt);
    }
}