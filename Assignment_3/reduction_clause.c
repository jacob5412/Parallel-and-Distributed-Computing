/*OpenMP program to employ reduction clause to express the reduction of a for loop. */

#include <stdio.h>
#include <omp.h>
#include <time.h>

int main()
{
    int sum = 0;
    int temp = 0;
    int a[10];
    clock_t t;

    printf("Enter a value: \n");
    for(int j = 0; j < 9; j ++)
        scanf("%d",&a[j]);

    omp_set_num_threads(3);
    t = clock();
    #pragma omp parallel for shared(temp, a) reduction(+:sum)
        for (int i = 0; i < 9; i++)
        {
            temp = a[i];
            sum += temp;
            printf("Thread %d is in execution and temp is = %d\n", omp_get_thread_num(),temp);
            printf("Value of temp is = %d (race condition) and sum = %d\n", temp, sum);
        }
    t = clock() - t;

    printf("Value of sum is: %d\n",sum);
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Running the program parallelly took %f seconds to execute \n", time_taken);
}