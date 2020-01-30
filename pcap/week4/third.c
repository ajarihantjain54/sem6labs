#include "extra.h"
int main(int argc , char* argv[])
{
	int M,N,rank , size,search;
	int*arr = (int*)malloc(sizeof(int)*(N*M));
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Errhandler_set(MCW,MPI_ERRORS_RETURN);
	if(rank == 0)
	{
		N = size;
		printf("Enter the value of M \n");
		scanf("%d",&M);
		printf("Enter %d numbers \n",(N*M));
		for(int i = 0;i<(N*M);i++)
		{
			scanf("%d",&arr[i]);
		}
		printf("Enter the number to be searched \n");
		scanf("%d",&search);
	}
	int count =0,finalCount;
	MPI_Bcast(&M,1,MPI_INT,0,MCW);
	MPI_Bcast(&N,1,MPI_INT,0,MCW);
	MPI_Bcast(&search,1,MPI_INT,0,MCW);
	int* sub = (int*)(malloc(sizeof(int)*M));
	MPI_Scatter(arr,M,MPI_INT,sub,M,MPI_INT,0,MCW);
	for(int i =0;i<M;i++)
	{
		if(sub[i]==search)
		{
			count++;
		}
	}
	int error = MPI_Reduce(&count,&finalCount,1,MPI_INT,MPI_SUM,0,MCW);
	MPI_Barrier(MCW);
	if(rank==0)
	{
		printf("The number of occurences of %d are %d \n",search,finalCount);
	}
	return 0;
}
