#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define MINDIM 1024
#define MAXDIM 1536
#define NUM_VALIDATES 10

void MatMul(int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C);

int main(int argc, char **argv)
{
    double *A, *B, *C, *Corg, alpha, beta, time1, time2, time3, time4;
    int m, n, p, b, bb, bbmin, bbmax;
    int row, col, numt;
    char status[100];

    alpha = (double)1.3;
    beta = (double)2.9;

    //printf( "X" ) ; fflush( stdout) ;

    A = (double *)malloc(sizeof(double) * MAXDIM * MAXDIM);
    B = (double *)malloc(sizeof(double) * MAXDIM * MAXDIM);
    C = (double *)malloc(sizeof(double) * MAXDIM * MAXDIM);
    Corg = (double *)malloc(sizeof(double) * MAXDIM * MAXDIM);
    if ((A == NULL) || (B == NULL) || (C == NULL) || (Corg == NULL))
    {
        printf("Out of Memory\n");
        exit(1);
    }

    //printf( "Y" ) ; fflush( stdout ) ;
    // m = n = p = 64 ;
    // b = 16 ;
    for (row = 0; row < MAXDIM; row++)
        for (col = 0; col < MAXDIM; col++)
            A[row * MAXDIM + col] = rand();

    for (row = 0; row < MAXDIM; row++)
        for (col = 0; col < MAXDIM; col++)
            B[row * MAXDIM + col] = rand();

    for (row = 0; row < MAXDIM; row++)
        for (col = 0; col < MAXDIM; col++)
            Corg[row * MAXDIM + col] = rand();

    //printf( "A" ) ; fflush( stdout ) ;

    for (m = MINDIM; m <= MAXDIM; m += 256)
    {
        n = p = m;
        for (numt = 1; numt <= 4; numt *= 2)
        {
            if (numt == 4)
            {
                bbmin = 4;
                bbmax = 64;
            }
            else
                bbmin = bbmax = 16;
            for (bb = bbmin; bb <= bbmax; bb *= 4)
            {
                for (row = 0; row < m; row++)
                    for (col = 0; col < p; col++)
                        C[row * p + col] = Corg[row * p + col];
                b = bb;
                if (b > m)
                    b = m;
                if (b > n)
                    b = n;
                if (b > p)
                    b = p;

                //printf ( "0" ) ; fflush( stdout ) ;
                omp_set_num_threads(numt);
                time1 = time(NULL);
                MatMul(m, n, p, b, alpha, beta, A, B, C);
                time2 = time(NULL);
                //time2 = omp_get_wtime() ;
                //printf ( "1" ) ; fflush( stdout ) ;

                /* Validate random entries */
                int success = 1, r;
                for (r = 0; r < NUM_VALIDATES; r++)
                {
                    double min, max, err, ans;

                    row = (rand() % m);
                    col = (rand() % p);

                    int k;
                    ans = Corg[row * p + col] * beta;
                    for (k = 0; k < n; k++)
                        ans += alpha * A[row * n + k] * B[k * p + col];

                    if (ans > C[row * p + col])
                    {
                        min = C[row * p + col];
                        max = ans;
                    }
                    else
                    {
                        min = ans;
                        max = C[row * p + col];
                    }
                    err = (double)(max - min) / (double)max;

                    if ((min > (double)0.0001) && (err > (double)0.01))
                        success = 0;
                }
                //printf ( "2" ) ; fflush( stdout ) ;

                if (success == 0)
                    strcpy(status, "Failed");
                else
                    strcpy(status, "Passed");
                //printf ( "3" ) ; fflush( stdout ) ;

                printf("{m=%d,n=%d,p=%d,numt=%d,b=%d,time=%g,status=%s},  ",
                       m, n, p, numt, b, (double)difftime(time2, time1), status);
                fflush(stdout);
            }
        }
    }

    return 0;
}
