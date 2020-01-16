#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	int rank , size , num ,x;
	int* arr1 = (int*)malloc(sizeof(int)*20);
	MPI_Init(&argc , &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	int s = sizeof(int)*20+MPI_BSEND_OVERHEAD;
	MPI_Buffer_attach(arr1,s);


	if(rank==0)
	{
		printf("Enter the number of processes \n");
		scanf("%d",&num);

		printf("Enter the array values \n");
		for(int i = 0;i<num;i++)
		{
			scanf("%d",&arr1[i]);

		}
		for(int i = 0;i<num;i++)
		{
			MPI_Bsend(&arr1[i],1,MPI_INT,i+1,1,MPI_COMM_WORLD);
			fprintf(stdout,"I have sent %d in process 0  to process %d \n",arr1[i],i+1);
			fflush(stdout);
		}
	
		
	}
	else
	{
		MPI_Recv(&x,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
		printf("I have received %d in process %d \n ",x,rank);

	}
	MPI_Buffer_detach(&arr1,&s);
	MPI_Finalize();
	return 0;
}