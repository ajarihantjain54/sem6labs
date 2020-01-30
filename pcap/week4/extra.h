 #include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#define  MCW MPI_COMM_WORLD 
void ErrorHandler(int error_code)
{
	if(error_code!= MPI_SUCCESS)
	{
		char error_string[20];
		int length_of_error_string , error_class;
		MPI_Error_class(error_code,&error_class);
		MPI_Error_string(error_class,error_string,&length_of_error_string);
		fprintf(stderr,"%s%d\n",error_string,length_of_error_string);
	}
}