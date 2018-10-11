#include <stdio.h>
#include <math.h>

#include "mpi.h"

double f(double x);
int main(int argc, char *argv[]);

/******************************************************************************/

int main(int argc, char *argv[])

/******************************************************************************/
/*
  Discussion:
    We break up the interval [A,B] into N subintervals, evaluate
    F(X) at the midpoint of each subinterval, and divide the
    sum of these values by N to get an estimate for the integral.

    If we have M processes available because we are using MPI, then
    we can ask processes 0, 1, 2, ... M-1 to handle the subintervals
    in the following order:

          0      1       2            M-1  <-- Process numbers begin at 0
     ------ ------  ------  -----  ------
          1      2       3    ...       M
        M+1    M+2     M+3    ...     2*M
      2*M+1    2*M+2 2*M+3    ...     3*M
                              
    and so on up to subinterval N.  The partial sums collected by 
    each process are then sent to the master process to be added 
    together to get the estimated integral.
*/
{
    double a = 0.0;
    double b = 1.0;
    int i;
    int id;
    int ierr;
    int n;
    int n_part;
    int p;
    double q;
    double q_diff;
    double q_exact = 2.0;
    double q_part;
    double wtime;
    double x;
    /*
      Initialize MPI.
    */
    ierr = MPI_Init(&argc, &argv);
    /*
      Get the number of processes.
    */
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &p);
    /*
      Determine this processes's rank.
    */
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);

    n = 1000000;
    /*
      Record the starting time.
    */
    wtime = MPI_Wtime();
    /*
      The master process broadcasts, and the other processes receive,
      the number of intervals N.
    */
    ierr = MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    /*
      Every process integrates F(X) over a subinterval determined by its process ID.
    */
    q_part = 0.0;
    n_part = 0;

    for (i = id + 1; i <= n; i = i + p)
    {
        x = ((double)(2 * n - 2 * i + 1) * a + (double)(2 * i - 1) * b) / (double)(2 * n);

        n_part = n_part + 1;
        q_part = q_part + f(x);
    }
    /*
      Each process sends its local result Q_PART to the MASTER process, 
      to be added to the global result QI.
    */
    ierr = MPI_Reduce(&q_part, &q, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    /*
      Every process scales the sum and reports the results.
    */
    q = q * (b - a) / (double)n;
    q_diff = fabs(q - q_exact);
    wtime = MPI_Wtime() - wtime;
    printf("\n");
    printf("  Integral estimate      %24.16f\n", q);
    printf("  Wall clock elapsed seconds = %f\n", wtime);
    /*
      Shut down MPI.
    */
    ierr = MPI_Finalize();

    return 0;
}
/******************************************************************************/

double f(double x)
{
    double value;

    if (x <= 0.0)
    {
        value = 0.0;
    }
    else
    {
        value = 1.0 / sqrt(x);
    }

    return value;
}