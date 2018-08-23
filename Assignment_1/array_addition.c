//simple array addition
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int a[5], b[5], c[5];
    int i;
    clock_t t,u;

    printf("-----------------16BCE2205-----------------\n");
    printf("Reading values for array A \n");
    for(i = 0; i < 5; i++){
        printf("Enter a value: ");
        scanf("%d", &a[i]);
    }

    printf("Reading values for array B \n");
    for(i = 0; i < 5; i++)
    {   
        printf("Enter a value: ");
        scanf("%d", &b[i]);
    }

    printf("Running program sequentially: \n");
    t = clock();
    for (i = 0; i < 5; i++)
    {
        c[i] = a[i] + b[i];
    }
    t = clock() - t;
    double time_taken_s = ((double)t) / CLOCKS_PER_SEC;

    printf("Running the program sequentially took %f seconds to execute \n", time_taken_s);

    for (i = 0; i < 5; i++)
        printf("Sum of %d and %d is %d\n", a[i], b[i], c[i]);

    return 0;
}