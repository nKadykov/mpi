#include <mpi.h>
#include <iostream>
#include <windows.h>
#include <iomanip>

int main(int argc, char** argv) {
	int n = 4;
	int rank, size;

	double** vector_a = new double* [4];
	double** vector_b = new double* [4];
	double** vector_c = new double* [4];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		std::cout << "Enter n: ";
		std::cin >> n;
		vector_a = new double* [n];
		for (int i = 0; i < n; ++i) {
			vector_a[i] = new double[n];
		}
		vector_b = new double* [n];
		for (int i = 0; i < n; ++i) {
			vector_b[i] = new double[n];
		}
		vector_c = new double* [n];
		for (int i = 0; i < n; ++i) {
			vector_c[i] = new double[n];
		}
		std::cout << "Enter " << n * n * 2 << " numbers:";
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cin >> vector_a[i][j];
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cin >> vector_b[i][j];
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int m = 0; m < n; ++m) {
				for (int j = 0; j < n; ++j) {
					vector_c[i][m] += vector_a[i][j] * vector_b[j][m];
				}
			}
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(vector_a[0][0]), n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(vector_b[0][0]), n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(vector_c[0][0]), n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
		std::cout << "Result:\n";
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				std::cout << vector_c[i][j] << ' ';
			}
			std::cout << '\n';
			for (int i = 0; i < n; ++i) {
				delete[] vector_a[i];
			}
			delete[] vector_a;
			for (int i = 0; i < n; ++i) {
				delete[] vector_b[i];
			}
			delete[] vector_b;
			for (int i = 0; i < n; ++i) {
				delete[] vector_c[i];
			}
			delete[] vector_c;
		}
	}
	else {
		MPI_Bcast(&n, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(vector_a[0][0]), n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(vector_b[0][0]), n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&(vector_c[0][0]), n * n, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}