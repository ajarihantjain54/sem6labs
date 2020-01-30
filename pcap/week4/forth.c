#include "extra.h"
int main(int argc , char* argv[])
{
	int M,N,rank , size;
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
	}
	int count =0,finalCount;
	MPI_Bcast(&M,1,MPI_INT,0,MCW);
	MPI_Bcast(&N,1,MPI_INT,0,MCW);
	int* sub = (int*)(malloc(sizeof(int)*M));
	int* sub1 = (int*)(malloc(sizeof(int)*M));
	MPI_Scatter(arr,M,MPI_INT,sub,M,MPI_INT,0,MCW);
	int error = MPI_Scan(sub,sub1,M,MPI_INT,MPI_SUM,MCW);
	ErrorHandler(error);
	for(int i = 0;i<M;i++)
	{
		printf("%d \t",sub1[i]);
	}
	printf("\n");
}