/* Print Hello World from multiple threads*/

/* Include OpenMP header file*/

#include <omp.h> //prototypes for various OpenMP functions
#include <stdio.h>

/*Main function*/
int main(int *argc, char *argv[] )
{
    omp_set_num_threads(3); //environment variable to specify number of threads
    /*Specify the block to be executed in parallel*/
    #pragma omp parallel //compiler directive
    {
    	/*Print "Hello world" from each thread*/
        printf("Hello world\n");
        /* Will print the same number of times as number 
        of threads were launched in the parallel block*/
    }

    return 0;
}