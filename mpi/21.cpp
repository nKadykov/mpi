#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int message;
	int buf = 0;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int dest;
	if (rank == (size - 1))
		dest = 0;
	else
		dest = rank + 1;
	int source;
	if (rank == 0) {
		source = size - 1;
	}
	else {
		source = rank - 1;
	}
	MPI_Send(&rank, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
	MPI_Recv(&message, 1, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	std::cout << "[" << rank << "]: receive message '" << message << "'\n";
	MPI_Finalize();
	return 0;
}
