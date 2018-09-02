#include <stdio.h>
#include <omp.h>
int main()
{
    int i, j;
    omp_set_num_threads(4);
    int star[4][64];
    int N = 64;
#pragma omp parallel num_threads(4), shared(star, N)
    {
#pragma omp for schedule(static)
        for (int i = 0; i < N; i++)
        {
            if (omp_get_thread_num() == 0)
            {
                star[0][i] = 3;
                star[1][i] = 2;
                star[2][i] = 2;
                star[3][i] = 2;
            }
            if (omp_get_thread_num() == 1)
            {
                star[0][i] = 2;
                star[1][i] = 3;
                star[2][i] = 2;
                star[3][i] = 2;
            }
            if (omp_get_thread_num() == 2)
            {
                star[0][i] = 2;
                star[1][i] = 2;
                star[2][i] = 3;
                star[3][i] = 2;
            }
            if (omp_get_thread_num() == 3)
            {
                star[0][i] = 2;
                star[1][i] = 2;
                star[2][i] = 2;
                star[3][i] = 3;
            }
        }
    }
    printf("schedule (static):\n");
    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < 64; k++)
        {
            if (star[j][k] == 3)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    int star1[4][64];
#pragma omp parallel num_threads(4), shared(star1, N)
    {
#pragma omp for schedule(static, 4)
        for (int i = 0; i < N; i++)
        {
            if (omp_get_thread_num() == 0)
            {
                star1[0][i] = 3;
                star1[1][i] = 2;
                star1[2][i] = 2;
                star1[3][i] = 2;
            }
            if (omp_get_thread_num() == 1)
            {
                star1[0][i] = 2;
                star1[1][i] = 3;
                star1[2][i] = 2;
                star1[3][i] = 2;
            }
            if (omp_get_thread_num() == 2)
            {
                star1[0][i] = 2;
                star1[1][i] = 2;
                star1[2][i] = 3;
                star1[3][i] = 2;
            }
            if (omp_get_thread_num() == 3)
            {
                star1[0][i] = 2;
                star1[1][i] = 2;
                star1[2][i] = 2;
                star1[3][i] = 3;
            }
        }
    }
    printf("schedule (static, 4) - chunk size = 4:\n");
    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < 64; k++)
        {
            if (star1[j][k] == 3)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    int star2[4][64];
#pragma omp parallel num_threads(4), shared(star2, N)
    {
#pragma omp for schedule(static, 8)
        for (int i = 0; i < N; i++)
        {
            if (omp_get_thread_num() == 0)
            {
                star2[0][i] = 3;
                star2[1][i] = 2;
                star2[2][i] = 2;
                star2[3][i] = 2;
            }
            if (omp_get_thread_num() == 1)
            {
                star2[0][i] = 2;
                star2[1][i] = 3;
                star2[2][i] = 2;
                star2[3][i] = 2;
            }
            if (omp_get_thread_num() == 2)
            {
                star2[0][i] = 2;
                star2[1][i] = 2;
                star2[2][i] = 3;
                star2[3][i] = 2;
            }
            if (omp_get_thread_num() == 3)
            {
                star2[0][i] = 2;
                star2[1][i] = 2;
                star2[2][i] = 2;
                star2[3][i] = 3;
            }
        }
    }
    printf("schedule (static, 8) - chunk size = 8:\n");
    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < 64; k++)
        {
            if (star2[j][k] == 3)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}
