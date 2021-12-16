#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int* argc, char** argv) {

	int size, rank;

	MPI_Init(argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int N = 110;
	int* x;
	int sum = 0;


	int block = N / size + 1;
	int start = rank * block;
	int end = (rank + 1) * block;

	if (start > N) {
		start = N;
	}
	if (end > N) {
		end = N;
	}

	int sendcount = end - start;
	int* data = new int[block];

	if (rank == 0) {
		x = new int[N];
		for (int i = 0; i < N; i++) {
			x[i] = i;
		}
	}
	else {
		x = NULL;
	}

	MPI_Scatter(x, sendcount, MPI_INT, data, sendcount, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < sendcount; i++) {
		sum += data[i];
	}

	int global_sum;

	MPI_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("Sum is %d\n", global_sum);
	}

	MPI_Finalize();

	return 0;
}