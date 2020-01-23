#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc , char* argv[])
{
	int rank , size , N = 1 , M = 0 , nonvow =0,sum=0;
	char* str = (char*)malloc(sizeof(char)*(M+1));
	int* arr3 = (int*)malloc(sizeof(int)*N);
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
	{
		N = size;
		printf("Enter the value of M \n");
		scanf("%d",&M);
		
		printf("Enter the string\n");
			scanf("%s",str);

		printf("The input string is \n");
		for(int i = 0;i<M;i++)
		{
			printf(" %c \t pos = %d \n",str[i],i);
		}
	}
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	int div = M/N;
	char* sub = (char*)malloc(sizeof(char)*(div+1));
	//printf("M = %d \t N = %d \t  Div = %d \n ",M,N,div);
	MPI_Scatter(str,div,MPI_CHAR , sub ,div,MPI_CHAR,0,MPI_COMM_WORLD);
	sub[div] = '\0';
	fflush(stdout);
	printf("I have received %s in process %d \n ",sub,rank);
	for(int i = 0;i<div;i++)
	{
		if(sub[i]=='a'||sub[i]=='e'||sub[i]=='i'||sub[i]=='o'||sub[i]=='u'||sub[i]=='A'||sub[i]=='E'||sub[i]=='I'||sub[i]=='O'||sub[i]=='U')
			continue;
		else
			nonvow++;
	}
	MPI_Gather(&nonvow,1,MPI_INT,arr3,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank == 0)
	{
		printf("The Result gathered in the root \n ");
		for(int i =0;i<N;i++)
		{
			printf("%d \t",arr3[i]);
			sum += arr3[i];
		}

		printf("\n The total number of nonvowels  is %d \n",sum);

	}


}