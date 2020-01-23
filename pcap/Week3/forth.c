#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc , char* argv[])
{
	int rank , size , N = 1 , M = 0 ;
	char* str = (char*)malloc(sizeof(char)*(M+1));
	char* str2 = (char*)malloc(sizeof(char)*(M+1));
	char* arr3 = (char*)malloc(sizeof(char)*((2*M+1)));
	MPI_Init(&argc ,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	if(rank==0)
	{
		N = size;
		printf("Enter the value of M \n");
		scanf("%d",&M);
		
		printf("Enter the string1\n");
			scanf("%s",str);

		printf("Enter the string2\n");
			scanf("%s",str2);

		// printf("The first input string is \n");
		// for(int i = 0;i<M;i++)
		// {
		// 	printf(" %c \t pos = %d \n",str[i],i);
		// }

		// printf("The seond input string is \n");
		// for(int i = 0;i<M;i++)
		// {
		// 	printf(" %c \t pos = %d \n",str2[i],i);
		// }
	}
	MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	int div = M/N;
	char* sub = (char*)malloc(sizeof(char)*(div+1));
	char* sub2 = (char*)malloc(sizeof(char)*(div+1));
	char* finalsub = (char*)malloc(sizeof(char)*(2*div));
	//printf("M = %d \t N = %d \t  Div = %d \n ",M,N,div);
	MPI_Scatter(str,div,MPI_CHAR , sub ,div,MPI_CHAR,0,MPI_COMM_WORLD);
	MPI_Scatter(str2,div,MPI_CHAR , sub2,div,MPI_CHAR,0,MPI_COMM_WORLD);
	sub[div] = '\0';
	sub2[div] = '\0';
	int pos = 0;
	fflush(stdout);
	printf("I have received %s & %s in process %d \n ",sub,sub2,rank);
	for(int i = 0;i<div;i++)
	{
		finalsub[pos++] = sub[i];
		finalsub[pos++] = sub2[i];

	}
	MPI_Gather(finalsub,(2*div),MPI_CHAR,arr3,(2*div),MPI_CHAR,0,MPI_COMM_WORLD);
	if(rank == 0)
	{
		printf("The Result gathered in the root \n ");
		for(int i =0;i<(2*M);i++)
		{
			printf("%c \t",arr3[i]);
		}

		//printf("\n The total number of nonvowels  is %d \n",sum);

	}


}