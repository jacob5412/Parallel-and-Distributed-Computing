#include <stdio.h>
#include <omp.h>
int main()
{
    int rank;
    int a;
    #pragma omp parallel private(a, rank)
    {
        a = 50000;
        #pragma omp master
        {
            a = ­50000;
        }
        rank = omp_get_thread_num();
        printf("Rank : %d ; A =%d\n",rank,a);
    }
    return 0;
}