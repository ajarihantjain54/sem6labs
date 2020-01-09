#include "mpi.h"
#include <stdio.h>


int isPrime(int i )
{
	for(int j =2;j<i;j++)
		{
			if(i%j == 0)
				return 0;
		}
		return 1;
}
int main(int argc , char* argv[])
{
	int rank , size;
	MPI_Init(&argc , &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if (rank == 0)
	{
		for(int i = 2 ;i<=50 ;i++)
		{
			if(isPrime(i))
				printf("%d \n",i);
		}
	}
	if (rank == 1)
	{
		for(int i = 51 ;i<100;i++)
		{
			if(isPrime(i))
				printf("%d \n",i);
		}
	}
}