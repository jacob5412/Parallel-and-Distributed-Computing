/*Shared variables in openMP*/
#include <stdio.h>
#include <omp.h>
int main()
{
    int a = 2;
    printf("----------16BCE2205----------\n");
    #pragma omp parallel num_threads(2) shared(a)
    {
        if (omp_get_thread_num() == 0)
            a = 5;
        else
            printf("1: Thread# %d: a = %d\n", omp_get_thread_num(), a); /* Print 1: the following read of x has a race */
        #pragma omp barrier
            if (omp_get_thread_num() == 0)
                printf("2: Thread# %d: a = %d\n", omp_get_thread_num(), a); /* Print 2 */
            else
                printf("3: Thread# %d: a = %d\n", omp_get_thread_num(), a); /* Print 3 */
    }
    return 0;
}