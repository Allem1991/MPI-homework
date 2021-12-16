#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int* argc, char** argv) {
	
	int rank, size;
	MPI_Status status;

	MPI_Init(argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		int a[10];

		for (int i = 0; i < 10; i++)
		{
			a[i] = rand();
		}

		printf("Sending array to process 1 from process 0: a = {");

		for (int i = 0; i < 9; i++)
		{
			printf("%d, ", a[i]);
		}

		printf("%d", a[9]);
		printf("}");

		MPI_Send(&a, 10, MPI_INT, 1, 2000, MPI_COMM_WORLD);
	}
	else
	{
		int a[10];
		MPI_Recv(&a, 10, MPI_INT, 0, 2000, MPI_COMM_WORLD, &status);

		string str = "{";

		for (int i = 0; i < 9; i++)
		{
			str += a[i] + ", ";
		}

		str += a[9] + "}";
		printf("Got array from process 0: a = {");

		for (int i = 0; i < 9; i++)
		{
			printf("%d, ", a[i]);
		}

		printf("%d", a[9]);
		printf("}");


	}

	MPI_Finalize();

	return 0;
}