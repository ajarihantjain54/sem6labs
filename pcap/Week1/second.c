#include "mpi.h"
#include <stdio.h>

int main(int argc , char* argv[])
{
	int rank , size;
	int a = 5 , b = 15 , c = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	MPI_Comm_rank(MPI_COMM_WORLD, &size);
	if(rank == 0)
	{
		printf("Performing Addition  %d \n",rank);
		c = a + b;
		printf("Answer = %d \n",c);

	}
	else if(rank == 1)
	{
		printf("Performing Subtraction %d  \n",rank);
		c = a - b;
		printf("Answer = %d \n",c);

	}
	else if(rank == 2)
	{
		printf("Performing Multiplication %d \n",rank);
		c = a * b;
		printf("Answer = %d \n",c);

	}
	else if(rank == 3	)
	{
		printf("Performing Division %d  \n",rank);
		c =  b/a;
		printf("Answer = %d \n",c);

	}

}