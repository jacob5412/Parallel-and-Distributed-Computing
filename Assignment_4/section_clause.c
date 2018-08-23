/*Write an OpenMP program to specify that the enclosed section(s) of code are to be divided
among the threads using OpenMP SECTION clause.*/

#include <stdio.h>
#include <omp.h>

int fib(int x)
{
    if (x <= 1)
        return x;
    return fib(x - 1) + fib(x - 2);
}

int fact(int x)
{
    unsigned long long n = 1;
    for(int j = 1; j <= x; j++)
    {
        n *= j;
    }
    return n;
}

int main()
{
    int i;
    int a[2];
    printf("Enter values: \n");
    for (i = 0; i < 2; i++)
        scanf("%d", &a[i]);

    omp_set_num_threads(2);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Thread %d gave a factorial of %d\n", omp_get_thread_num(), fact(a[0]));
        }
        #pragma omp section
        {
            printf("Thread %d gave a fibonacci of %d\n", omp_get_thread_num(), fib(a[1]));
        }
    }
}