/* ‘Work Sharing’ clause to assign each thread an
independent set of iterations.*/

#include <stdio.h>
#include <omp.h>

int add(int x, int y)
{
    return (x + y);
}

int sub(int x, int y)
{
    return (x - y);
}

int min(int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    int i;
    int a[10];
    printf("Enter values: \n");
    #pragma omp parallel for shared(a)
    for (i = 0; i < 9; i++)
        scanf("%d", &a[i]);

    omp_set_num_threads(4);
    int var;
    #pragma omp parallel for
    //The threads divide up the loop iterations among themselves
    for(i = 0; i < 8; i ++)
    {
        for(int ttid = 0; ttid < omp_get_num_threads();ttid++)
        {
            int tid = omp_get_thread_num();
            printf("Thread %d gave value %d on adding %d and %d\n", tid, add(a[i], a[i + 1]), a[i], a[i + 1]);
            printf("Thread %d gave value %d on subtracting %d and %d\n", tid, sub(a[i], a[i + 1]), a[i], a[i + 1]);
            printf("Thread %d computed %d as minimum of %d and %d\n", tid, min(a[i], a[i + 1]), a[i], a[i + 1]);
            printf("Thread %d computed %d as maximum of %d and %d\n", tid, max(a[i], a[i + 1]), a[i], a[i + 1]);
        }   
    }
    return 0;
}