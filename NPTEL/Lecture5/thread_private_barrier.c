/*Use explicit barrier for synchronization*/

#include <stdio.h>
#include <omp.h>

int main(){
    int numt;

    #pragma omp parallel default(shared)
    {
        int j, tid = omp_get_thread_num();
        if(tid == 0)
        {
            for(j = 0; j < 100000; j++);
            numt = omp_get_num_threads();
        }

        #pragma omp barrier
        printf("Hello world from thread %d of %d\n",tid,numt);
    }
}