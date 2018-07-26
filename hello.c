#include<stdio.h>
#include<omp.h>
int main() {
    #pragma omp parallel num_threads(5)
    {
        printf("Hello world!\n");
    }
}