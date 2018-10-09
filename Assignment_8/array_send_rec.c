/*Initialize an array of 100 elements
Perform the sum of the elements sharing the load among 4 processes using
MPI Send and MPI Recv*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define ARRAYSIZE 100
#define ROOT 0

int main( int argc, char** argv )
{
    int rank, fraction, PROCESSES;
    MPI_Status status;
    int i, dest, offset, source;
    float sum, mysum, tasks_sum;
    float data[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &PROCESSES);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    fraction = (ARRAYSIZE / PROCESSES);
    if (rank == ROOT)
    {
        sum = 0;
        for(i = 0; i < ARRAYSIZE; i++){
            data[i] = i * 1.0;
        }
        offset = fraction;
        for (dest = 1; dest < PROCESSES; dest++){
            MPI_Send(&data[offset], fraction, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
            printf("Sent %d elements to task %d offset= %d\n", fraction, dest, offset);
            offset = offset + fraction;
        }
        offset = 0;
        for (i = 0; i < fraction; i++){
            mysum += data[i];
        }
        for (i = 1; i < PROCESSES; i++)
        {
            source = i;
            MPI_Recv(&tasks_sum, 1, MPI_FLOAT, source, 0, MPI_COMM_WORLD, &status);
            sum += tasks_sum;
            printf(" Received partial sum %f from task %d\n", tasks_sum, i);
        }
        printf(" Final sum= %f \n", sum + mysum);
    }

    if (rank > ROOT)
    {
        source = ROOT;
        MPI_Recv(&data[offset], fraction, MPI_FLOAT, source, 0, MPI_COMM_WORLD, &status);
        for ( i=offset ; i <(offset+fraction); i++){
            tasks_sum += data[i];
        }
        dest = ROOT;
        MPI_Send(&tasks_sum, 1, MPI_FLOAT, dest, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}

