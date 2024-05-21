#include <mpi.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) {
		printf("%d processes\n", rank);
	}
	else if (rank % 2 == 0) {
		printf("I am %d: SECOND!", rank);
	}
	if (rank % 2 != 0) {
		printf("I am %d: FIRST!", rank);
	}
	MPI_Finalize();
	return 0;
}