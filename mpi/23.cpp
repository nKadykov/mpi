#include <mpi.h>
#include <iostream>
#include <map>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	int message = 1;
	char buf[100];
	int n;
	std::map<char, int> letters;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		std::cout << "Enter n: ";
		std::cin >> n;
		std::cout << "Enter string: ";
		for (int i = 0; i < n; ++i) {
			std::cin >> buf[i];
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(buf, n, MPI_CHAR, 0, MPI_COMM_WORLD);
		for (int i = 0; i < n; ++i) {
			if ((buf[i] >= 'a' && buf[i] <= 'g') || (buf[i] >= 'A' && buf[i] <= 'G')) {
				if (letters[buf[i]] == 0)
					letters[buf[i]] = 1;
				else
					letters[buf[i]]++;
			}
		}
	}
	if (rank == 1) {
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(buf, n, MPI_CHAR, 0, MPI_COMM_WORLD);
		for (int i = 0; i < n; ++i) {
			if ((buf[i] >= 'h' && buf[i] <= 'n') || (buf[i] >= 'H' && buf[i] <= 'N')) {
				if (letters[buf[i]] == 0)
					letters[buf[i]] = 1;
				else
					letters[buf[i]]++;
			}
		}
	}
	if (rank == 2) {
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(buf, n, MPI_CHAR, 0, MPI_COMM_WORLD);
		for (int i = 0; i < n; ++i) {
			if ((buf[i] >= 'o' && buf[i] <= 'u') || (buf[i] >= 'O' && buf[i] <= 'U')) {
				if (letters[buf[i]] == 0)
					letters[buf[i]] = 1;
				else
					letters[buf[i]]++;
			}
		}
	}
	if (rank == 3) {
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(buf, n, MPI_CHAR, 0, MPI_COMM_WORLD);
		for (int i = 0; i < n; ++i) {
			if ((buf[i] >= 'v' && buf[i] <= 'z') || (buf[i] >= 'V' && buf[i] <= 'Z')) {
				if (letters[buf[i]] == 0)
					letters[buf[i]] = 1;
				else
					letters[buf[i]]++;
			}
		}
	}
	for (auto x : letters) {
		std::cout << x.first << " = " << x.second << '\n';
	}
	MPI_Finalize();
	return 0;
}