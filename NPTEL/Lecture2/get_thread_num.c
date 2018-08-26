/*Getting number of threads and thread id*/

#include <omp.h>
#include <stdio.h>

int main( int *argc, char *argv[] )
{
    #pragma omp parallel
    {
        /*Get the total number of OMP threads*/
        int numt = omp_get_num_threads(); //stack of each thread contains total threads in execution

        /*Get the thread id of this thread*/
        int tid = omp_get_thread_num(); //stack of each thread contains its ID

        /*Print "Hello World" along with thread id and number of threads*/
        printf("Hello World from thread %d of %d\n",tid,numt);

    }

    return 0;
}

/*----------Example output----------
Hello World from thread 1 of 4
Hello World from thread 2 of 4
Hello World from thread 0 of 4
Hello World from thread 3 of 4
Note: We cannot be sure about the order. Hence order changes.
But we know that the statements will be printed sequentially.
*/