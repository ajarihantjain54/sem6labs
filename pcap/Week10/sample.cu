#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__device__ int getTid()
{
	int bid = blockIdx.y * gridDim.x + blockIdx.x;
	int tid = threadIdx.y * blockDim.x + threadIdx.x;
	int tPB = blockDim.x * blockDim.y ;
	int fin = bid*tPB+tid;
	return fin;
}

__global__ void mulElement(int *a ,int *b , int *c , int ha ,int wa)
{
	int th = getTid();
	if(th<(ha*wa))
	{
		c[th] = a[th]+b[th];
	}
	
}

int main(void)
{
	int *a,*b,*t,i,j;
	int *d_a,*d_b,*d_t;
	int ha , wa;
	printf("Enter the dimensions of first matrix \n ");
	scanf("%d %d",&ha,&wa);
	int size1 = sizeof(int)*ha*wa;
	a = (int*)malloc(size1);
	b = (int*)malloc(size1);
	t = (int*)malloc(size1);

	printf("Enter input matrix 1 : \n");
	for(i = 0;i<ha*wa;i++)
		scanf("%d",&a[i]);

	printf("Enter input matrix 2 : \n");
	for(i = 0;i<ha*wa;i++)
		scanf("%d",&b[i]);

	cudaMalloc((void**)&d_a,size1);
	cudaMalloc((void**)&d_b,size1);
	cudaMalloc((void**)&d_t,size1);
	cudaMemcpy(d_a,a,size1,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size1,cudaMemcpyHostToDevice);
	int gx,gy,bx,by;
	printf("Enter the dimension of the grid \n");
	scanf("%d %d",&gx,&gy);
	bx = ceil((double)ha/gx);
	by = ceil((double)wa/gy);
	printf("The dimensions of block are : \n %d %d \n",bx,by);
	dim3 grid(gx,gy);
	dim3 block(bx,by);
	mulElement<<<grid,block>>>(d_a,d_b,d_t,ha,wa);
	cudaMemcpy(t,d_t,size1,cudaMemcpyDeviceToHost);
	printf("Result vector is :\n");
	for(i = 0;i<ha;i++)
	{
		for(j = 0;j<wa;j++)
		printf("%d ",t[i*wa+j]);
		printf("\n");
	}
	getchar();
	cudaFree(d_a);
	cudaFree(d_t);
	return 0;
}