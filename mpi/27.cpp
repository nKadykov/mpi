#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm comm_parent, comm_inter;
	MPI_Comm_get_parent(&comm_parent);

	if (comm_parent == MPI_COMM_NULL) {
		int n = 0;

		char command[] = "E:/C/Visual Studio/mpi/x64/Debug/mpi";
		MPI_Comm_spawn(command, NULL, n, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &comm_inter, MPI_ERRCODES_IGNORE);

	}

	std::cout << "I am " << rank << " process from " << size << "processes!\n";

	MPI_Finalize();

	return 0;
}