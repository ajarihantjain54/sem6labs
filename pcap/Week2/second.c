#include "mpi.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
	int rank , size , x ,num;
	MPI_Init(&argc , &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter a value in master process: ");
		scanf("%d",&x);
		printf("Enter the number of slave processes: ");
		scanf("%d",&num);
		for(int i = 1;i<=num;i++)
		{
		MPI_Send(&x,1,MPI_INT,i,1,MPI_COMM_WORLD);
		fprintf(stdout,"I have sent %d in process 0 to process %d \n",x,i);
		fflush(stdout);
		x++;
		}
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		printf("I have received %d in process %d \n ",x,rank);

	}
	MPI_Finalize();
	return 0;
}