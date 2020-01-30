#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_ELEMS 5
int main(int argc, char* argv[]){
	int rank, size;
	int num[NUM_ELEMS];
	int bufsize = sizeof(int)*NUM_ELEMS + MPI_BSEND_OVERHEAD;
	int* buf = malloc(bufsize);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Buffer_attach(buf, bufsize);
	MPI_Status status;
	if(rank==0){
		printf("Enter %d values: ", NUM_ELEMS);
		for(int i=0;i<NUM_ELEMS;++i)
			scanf("%d", num+i);
		for(int i=1; i<NUM_ELEMS+1; ++i){
			MPI_Bsend(num+i-1, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			printf("Sent value %d to process %d\n", num[i-1], i);
		}
	}
	else{
		MPI_Recv(num, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		if(rank%2 == 0) printf("Proc %d: Square of %d is %d\n", rank, num[0], num[0]*num[0]);
		else printf("Proc %d: Cube of %d is %d\n", rank, num[0], num[0]*num[0]*num[0]);
	}
	MPI_Buffer_detach(&buf, &bufsize);
	MPI_Finalize();
	return 0;
}
