#include <mpi.h>
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
    int rank, size;
    int N;
    double pi = 0;
    double sum = 0;
    double start, end;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        std::cout << "Enter N: ";
        std::cin >> N;
    }
    start = MPI_Wtime();
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    for (int i = N * (rank / size); i < N * ((rank + 1) / size); ++i) {
        float x = (i + 0.5) / N;
        pi += 4 / (1 + x * x) / N;
    }
    MPI_Reduce(&pi, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Time: " << end - start << std::endl;
        std::cout << std::setprecision(9) << "Result: " << sum << std::endl;
    }
    MPI_Finalize();
    return 0;
}