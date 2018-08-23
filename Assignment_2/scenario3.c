#include <stdio.h> 
#include <stdlib.h> 
#include <omp.h>

int add(int x, int y)
{
    return (x + y);
}

int sub(int x, int y)
{
    return (x - y);
}

int fib(int x)
{
    if (x <= 1)
        return x;
    return fib(x - 1) + fib(x - 2);
}

int main()
{
    int a,b;
    printf("Enter value of a: ");
    scanf("%d", &a);
    printf("Enter value of b: ");
    scanf("%d", &b);
    printf("\n");
    omp_set_num_threads(3);
#pragma omp parallel shared(a, b) 
{
    int tid = omp_get_thread_num();
    if (tid == 0)
        printf("Thread %d gave value %d on addition\n", tid, add(a, b));
    if (tid == 1)
        printf("Thread %d gave value %d on subtraction\n", tid, sub(a, b));
    if (tid == 2)
        printf("Thread %d gave value %d and %d on fibonacci\n", tid, fib(a), fib(b));
}
return 0;
}