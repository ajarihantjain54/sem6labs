#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc , char* argv[])
{
	int rank , size ,length;
	char* arr = (char*)malloc(sizeof(char)*20);
	char* arr2 = (char*)malloc(sizeof(char)*20);
	MPI_Init(&argc , &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if(rank==0)
	{
		printf("Enter a word in master process: ");
		gets(arr2);
		length = strlen(arr2);
		MPI_Ssend(arr2,20,MPI_CHAR,1,1,MPI_COMM_WORLD);
		fprintf(stdout,"I have sent %s in process 0 \n",arr2);
		fflush(stdout);
		MPI_Recv(arr2,20,MPI_CHAR,1,2,MPI_COMM_WORLD,&status);
		printf("I have received %s in process 0 \n",arr2);

	}
	else
	{
		MPI_Recv(arr,20,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		printf("I have received %s in process 1 \n",arr);
		int i = 0;
		while(arr[i] != '\0')
		{
			if(arr[i]>='a' && arr[i]<='z')
		        {
		            arr[i] = arr[i] - 32;
		        }
        else if(arr[i]>='A' && arr[i]<='Z')
		        {
		            arr[i] = arr[i] + 32;
		        }

       			i++;
		}
		MPI_Ssend(arr,20,MPI_CHAR,0,2,MPI_COMM_WORLD);
		fprintf(stdout,"I have sent %s in process 1 \n",arr);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;

}