#include <stdio.h>
#include <omp.h>

int tid;
int main()
{
    int j, k=0,numt,i=1;

    omp_set_num_threads(4);
    //parallelize
    #pragma omp parallel
    {
	    for(j = 0; j < 10; j++);
	    //explicit wait to prevent race conditions
	    k = k + i;
	    tid = omp_get_thread_num();
	    if(tid == 0)
	    {
	        printf("Hello World! This is thread %d\n",tid);
	    }
        numt = omp_get_num_threads();
	}
    
	//introduce a synchronization point for programs
    #pragma omp barrier
    printf("%d was caculated by %d threads\n",k,numt);

    omp_set_num_threads(4);
    //get threads that executed the program
    #pragma omp parallel default(shared)
    {
    	tid = omp_get_thread_num();
    	printf("%d was involved in the calculation\n",tid);
    }

}
