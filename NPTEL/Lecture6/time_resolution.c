/*Getting time and resolution*/

#include <stdio.h>
#include <omp.h>

int main()
{
    printf("omp_get_wtime()=%g\n",omp_get_wtime()); //resolution of timer in ns
    printf("omp_get_wtick()=%g\n",omp_get_wtick()); 

    return 0;
}