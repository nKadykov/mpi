#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[])
{
    int rank, size, buf, message;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    buf = rank;

    for (int i = 0; i < size; ++i) {
        if (i != rank) {
            MPI_Send(&buf, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    for (int i = 0; i < size; ++i) {
        if (i != rank) {
            MPI_Recv(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("[%d]: receive message '%d' from %d\n", rank, message, message);
        }
    }
    MPI_Finalize();
    return 0;
}
