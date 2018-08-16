/* Write an OpenMP program to find the smallest element 
in a list of numbers using OpenMP REDUCTION clause.*/

#include <stdio.h>
#include <omp.h>
#include <time.h>

int min(int x,int y)
{
    if(x<y)
        return x;
    else
        return y;
}

int max(int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}

int main()
{
    int min_val = 9999;
    int max_val = -9999;
    int a[10];
    int temp = 0;
    clock_t t;

    printf("Enter a value: \n");
    for (int j = 0; j < 9; j++)
        scanf("%d", &a[j]);

    omp_set_num_threads(3);
    t = clock();
    #pragma omp parallel for shared(temp, a) reduction(min:min_val) reduction(max:max_val)
    for (int i = 0; i < 9; i++)
    {
        temp = a[i];
        min_val = min(min_val,temp);
        max_val = max(max_val,temp);
        printf("Thread %d is in execution and temp is = %d\n", omp_get_thread_num(), temp);
        printf("Value of temp is = %d (race condition) and min_val = %d\n", temp, min_val);
        printf("Value of temp is = %d (race condition) and max_val = %d\n", temp, max_val);
    }
    t = clock() - t;

    printf("Value of min is: %d\n", min_val);
    printf("Value of max is: %d\n", max_val);
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Running the program parallelly took %f seconds to execute \n", time_taken);
}