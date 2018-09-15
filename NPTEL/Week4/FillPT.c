#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAXDIM 17

extern void PTUpdateEntry( int arr[MAXDIM][MAXDIM+1], int i, int j, int value  ) ;

int binomialCoeff(int n, int k)
{
    int res = 1, i = 0;
    if (k > n - k)
        k = n - k;
    for (i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

void FillPascalTriangle( int arr[MAXDIM][MAXDIM+1] )
{

    int numt;
    int i, j;
    int value = 0;
    // Compute the value of the i, j th entry. Use tasks as appropriate
    // Update the entry in the table using the function PTUpdateEntry
    #pragma omp parallel
    {
        #pragma omp single
        numt = omp_get_num_threads();
        #pragma omp for
        for (i = 0; i < MAXDIM; i++)
        {
            for (j = 0; j <= i; j++)
            {
                #pragma omp task firstprivate(i, j) shared(arr)
                PTUpdateEntry(arr, i, j, binomialCoeff(i, j));
            }
        }
    }
}

