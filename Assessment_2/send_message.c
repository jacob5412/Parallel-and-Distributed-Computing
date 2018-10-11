#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])  
{
    int ntasks, rank, dest, source, count, n;  
    char input_msg[50], msg0[]="Tag1 used", msg1[]="Tag1 used again", msg2[]="Tag2 used", msg3[]="Tag2 used again";
    int Tag1=5,Tag2=15;
    char max_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(max_name, &n);

    if (rank == 0) {      
        dest = 1;
        source = 1;
        MPI_Send(&msg0, strlen(msg0), MPI_CHAR, dest, Tag1, MPI_COMM_WORLD);
        MPI_Send(&msg2, strlen(msg2), MPI_CHAR, dest, Tag2, MPI_COMM_WORLD);
        MPI_Send(&msg1, strlen(msg1), MPI_CHAR, dest, Tag1, MPI_COMM_WORLD);
        MPI_Send(&msg3, strlen(msg3), MPI_CHAR, dest, Tag2, MPI_COMM_WORLD);
        printf("\nTask 0 on processor %s has sent its messages to Task 1. \n\n",max_name);
    } 

    else if (rank == 1) {
        dest = 0;
        source = 0;

        memset(input_msg, 0, 50);
        MPI_Recv(&input_msg, 50, MPI_CHAR, source, Tag2, MPI_COMM_WORLD,  MPI_STATUS_IGNORE);
        printf("Task 1 on processor %s listening for Tag2 received this message:\n %s\n",max_name,input_msg);

        memset(input_msg, 0, 50);
        MPI_Recv(&input_msg, 50, MPI_CHAR, source, Tag2, MPI_COMM_WORLD,  MPI_STATUS_IGNORE);
        printf("Task 1 on processor %s listening for Tag2 received this message:\n %s\n",max_name,input_msg);

        memset(input_msg, 0, 50);
        MPI_Recv(&input_msg, 50, MPI_CHAR, source, Tag1, MPI_COMM_WORLD,  MPI_STATUS_IGNORE);
        printf("Task 1 on processor %s listening for Tag1 received this message:\n %s\n",max_name,input_msg);

        memset(input_msg, 0, 50);
        MPI_Recv(&input_msg, 50, MPI_CHAR, source, Tag1, MPI_COMM_WORLD,  MPI_STATUS_IGNORE);
        printf("Task 1 on processor %s listening for Tag1 received this message:\n %s\n",max_name,input_msg);
    }

    MPI_Finalize();
}