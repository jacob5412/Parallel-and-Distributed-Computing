#include <stdio.h> 
#include <omp.h>
int main()
{
    int x,y,tid;
    printf("Enter value of x = ");
    scanf("%d", &x);
    printf("Enter value of y = ");
    scanf("%d", &y);
    omp_set_num_threads(2);
    #pragma omp parallel private(x, y, tid)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
            printf("sum is %d\n", (x + y));
        if (tid == 1)
            printf("%d and %d values of x and y\n", x, y);
    }
    return 0;
}