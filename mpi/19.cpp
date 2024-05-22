#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int message = 1;
	int buf = 0;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		for (int src = 1; src < size; ++src) {
			MPI_Recv(&buf, 1, MPI_INT, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::cout << "receive message '" << buf << "'\n";
		}
	}
	else {
		buf = rank;
		MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}