#include <mpi.h>
#include <iostream>
#include <windows.h>
#include <iomanip>

const int NUMBER = 2;

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int n = NUMBER;
	int rank, size;

	double A[NUMBER][NUMBER];
	double B[NUMBER][NUMBER];
	double C[NUMBER][NUMBER];
	double result[NUMBER];

	for (int i = 0; i < NUMBER; ++i) {
		for (int j = 0; j < NUMBER; ++j) {
			result[i] = 0;
		}
	}

	double M[NUMBER];

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {

		int all[2];
		std::cout << "Enter " << n * n * 2 << " numbers: ";
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cin >> A[i][j];
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cin >> B[i][j];
			}
		}

		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(B[0][0]), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		MPI_Scatter(&(A[0][0]), n, MPI_DOUBLE, &(M[0]), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	}
	else {
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(B[0][0]), n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		MPI_Scatter(&(A[0][0]), n, MPI_DOUBLE, &(M[0]), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			result[j] += M[i] * B[i][j];
			//std::cout << "rank " << rank << ": " << result[0] << " " << M[0] << " " << M[1] << " " << B[rank][0] << " " << B[rank][1] << "\n";
		}
	}

	//std::cout << "C " << rank << ": " << result[0] << " " << result[1] << "\n";

	MPI_Gather(&result[0], n, MPI_DOUBLE, &C[0][0], n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		//MPI_Gather(&result[0], n, MPI_DOUBLE, &C[0][0], n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cout << C[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	MPI_Finalize();

	return 0;
}