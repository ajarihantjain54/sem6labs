#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int fact(int c)
{
	int ans = 1;
	for(int i = 1;i<=c;i++)
		ans = ans * i;
	return ans;

}
int main(int argc , char* argv[])
{
	int rank , size , N , A[10],B[10],c,i;
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	if(rank==0)
	{
		N = size;
		printf("Enter %d values : \n",N);
		for(i = 0;i<N;i++)
			scanf("%d",&A[i]);

	}
	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	printf("I have received %d in process %d \n ",c,rank);
	fflush(stdout);
	c = fact(c);
	MPI_Gather(&c , 1 , MPI_INT , B,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank == 0)
	{
		int sum = 0;
		printf("The Result gathered in the root \n ");
		for(i =0;i<N;i++)
		{
			printf("%d \t",B[i]);
			sum += B[i];
		}

		printf("\n The sum of the gathered factorials is %d \n",sum);

	}
}