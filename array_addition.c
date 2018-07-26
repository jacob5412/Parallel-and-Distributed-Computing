//Write a simple OpenMP program for array addition (sum).
//we are going to take two one-dimensional arrays, each of size of 5. 
//We will then create 5 threads. Each thread will be responsible for one addition operation.
#include<stdio.h>
#include<omp.h>

int main() {
    int A[5] = {1,2,3,4,5};
    int B[5] = {6,7,8,9,10};

    #pragma omp parallel num_threads(5)
    {
        int i;
        for(i = 0; i <= 5; i++)
        {
            A[i] = A[i] + B[i];
            printf("Sum is %d, thread is %d and nthreads %d\n", A[i], omp_get_thread_num(), omp_get_num_threads());
        }
    }
}