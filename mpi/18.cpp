#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int message = 1;
	int buf = 0;
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(&message, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << "[" << rank << "]" << ": receive message '" << message << "'\n";
	}
	if (rank == 1) {
		MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << "[" << rank << "]" << ": receive message '" << message << "'\n";
		buf = message + 1;
		MPI_Send(&buf, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
	}
	if (rank == 2) {
		MPI_Recv(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << "[" << rank << "]" << ": receive message '" << message << "'\n";
		buf = message + 1;
		MPI_Send(&buf, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
	}
	if (rank == 3) {
		MPI_Recv(&message, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << "[" << rank << "]" << ": receive message '" << message << "'\n";
		buf = message + 1;
		MPI_Send(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}