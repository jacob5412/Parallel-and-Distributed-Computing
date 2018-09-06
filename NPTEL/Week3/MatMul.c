void MatMul(int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C)
{
    int i, j, k, ii, jj, kk;

    #pragma omp parallel default(shared) private(j, ii, jj, kk)
    #pragma omp for collapse(2)
    for(i = 0; i < m; i += b)
    {
        for(k = 0; k < n; k += b)
        {
                for (ii = i; ii < i+b && ii < m; ii++)
                    for (kk = k; kk < k+b && kk < n; kk++)
                    {
                        #pragma omp atomic
                        C[ii * p + kk] *= beta;
                        for (j = 0; j < p; j++)
                        {
                            #pragma omp atomic
                            C[ii * p + kk] += alpha * A[ii * n + j] * B[j * p + kk];
                        }
                    }
        }
    }
}