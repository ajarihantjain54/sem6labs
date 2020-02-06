#include "extra.h"
int main(int argc , char* argv[])
{
	int rank , size , fact =1, factsum , i,error_code;
	MPI_Init(&argc ,&argv);
	MPI_Errhandler_set(MCW,MPI_ERRORS_RETURN);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	for(int i =1;i<=rank+1;i++)
	{
		fact = fact*i;
	}
	error_code =  MPI_Scan(&fact,&factsum,0 ,MPI_INT,MPI_SUM,fact);
	//ErrorHandler(error_code);
	if(rank==size-1)
	{
		printf("The sum of the factorial is %d \n",factsum);
	}
}	