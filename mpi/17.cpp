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
		std::cout << "rank = " << rank << "\n";
		std::cout << "Enter buf: ";
		std::cin >> buf;
		MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	if(rank == 1) {
		MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		std::cout << "rank = " << rank << "\n";
		std::cout << "message = " << message << std::endl;
	}
	MPI_Finalize();
	return 0;
}