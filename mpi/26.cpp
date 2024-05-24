#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int rank, size;

	char message;

	MPI_Group oldgroup, group;
	MPI_Comm newcomm;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int* ranks = new int[size / 2 + 1];
	for(int i = 0; i <= size / 2; ++i) {
		ranks[i] = 2 * i;
	}

	MPI_Comm_group(MPI_COMM_WORLD, &oldgroup);
	MPI_Group_incl(oldgroup, size / 2 + 1, ranks, &group);
	MPI_Comm_create(MPI_COMM_WORLD, group, &newcomm);

	int newrank, newsize;

	if (newcomm != MPI_COMM_NULL) {
		MPI_Comm_rank(newcomm, &newrank);
		MPI_Comm_size(newcomm, &newsize);
	}

	if (rank == 0) {
		std::cout << "Enter message: ";
		std::cin >> message;
		MPI_Bcast(&message, 1, MPI_CHAR, 0, newcomm);
	}
	else {
		if (newcomm != MPI_COMM_NULL) {
			MPI_Bcast(&message, 1, MPI_CHAR, 0, newcomm);
		}
	}

	if (newcomm != MPI_COMM_NULL) {
		std::cout << "MPI_COMM_WORLD: " << rank << " from " << size << ". New comm: " << newrank << " from " << newsize << ". Message: " << message << '\n';
	}
	else {
		std::cout << "MPI_COMM_WORLD: " << rank << " from " << size << ". New comm: no" << " from no" << ". Message: no\n";
	}

	MPI_Group_free(&group);
	MPI_Group_free(&oldgroup);

	if (newcomm != MPI_COMM_NULL) {
		MPI_Comm_free(&newcomm);
	}

	MPI_Finalize();
}