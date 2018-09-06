#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
int main(int argc, char **argv)
{
    char msg[20];   
    int my_rank, tag =99;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0){
        strcpy(msg, "Greetings");
        MPI_Send(msg, strlen(msg)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
        printf("my_rank = %d: %s\n", my_rank, msg);
        } 
    else if (my_rank == 1){
        MPI_Recv(msg, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
        printf("my_rank = %d: %s\n", my_rank, msg);
        }
    MPI_Finalize();
}
