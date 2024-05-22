#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int message = 1;
	int buf = 45;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Request request;
	if (rank == 0) {
		MPI_Isend(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, MPI_STATUS_IGNORE);
	}
	if (rank == 1) {
		MPI_Irecv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
		MPI_Wait(&request, MPI_STATUS_IGNORE);
		std::cout << "receive message '" << buf << "'\n";
	}
	MPI_Finalize();
	return 0;
}