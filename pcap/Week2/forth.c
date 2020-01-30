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
		printf("Enter the number of child processes: ");
		scanf("%d",&num);		
		MPI_Ssend(&x,1,MPI_INT,1,1,MPI_COMM_WORLD);
		fprintf(stdout,"I have sent %d in process 0 \n",x);
		MPI_Recv(&x,1,MPI_INT,num,1,MPI_COMM_WORLD,&status);
		printf("I have received %d in process 0 \n",x);
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,rank-1,1,MPI_COMM_WORLD,&status);
		printf("I have received %d in process %d \n ",x,rank);
		x++;
		int send = 0;
		if(rank == size-1)
			send = 0;
		else
			send = rank+1;
		MPI_Ssend(&x,1,MPI_INT,send,1,MPI_COMM_WORLD);
		printf("I have sent %d in process %d \n ",x,rank);
		


	}
	MPI_Finalize();
	return 0;
}