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
        start = MPI_Wtime();
    }
    start = MPI_Wtime();
    if (rank == 0) {
        for (int i = N * (rank / size); i < N * ((rank + 1) / size); ++i) {
            float x = (i + 0.5) / N;
            pi += 4 / (1 + x * x) / N;
        }
        sum += pi;
        MPI_Send(&sum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&sum, 1, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&N, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else {
        int dest;
        if (rank == (size - 1)) {
            dest = 0;
        }
        else {
            dest = rank + 1;
        }
        MPI_Recv(&sum, 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&N, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = N * (rank / size); i < N * ((rank + 1) / size); ++i) {
            float x = (i + 0.5) / N;
            pi += 4 / (1 + x * x) / N;
        }
        sum += pi;
        MPI_Send(&sum, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
        MPI_Send(&N, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
    }
    end = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Time: " << end - start << std::endl;
        std::cout << std::setprecision(9) << "Result: " << sum << std::endl;
    }
    MPI_Finalize();
    return 0;
}