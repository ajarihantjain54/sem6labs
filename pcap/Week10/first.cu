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
}

__global__ void mulElement(int *a ,int *b , int *c , int ha , int wb,int wa)
{
	int th = getTid();
	if(th<(ha*wb))
	{
		int row = th/wb;
		int col = th%wb;
		int i = 0 , sum = 0;
		for(i = 0;i<wa;i++)
		{
			sum += a[row*wa+i]*b[wb*i+col];
		}
		c[th] = sum;
	}
	
}

int main(void)
{
	int *a,*b,*t,i,j;
	int *d_a,*d_b,*d_t;
	int ha , wa;
	int hb , wb;
	printf("Enter the dimensions of first matrix \n ");
	scanf("%d %d",&ha,&wa);
	printf("Enter the dimensions of second matrix \n");
	scanf("%d %d",&hb,&wb);
	int size1 = sizeof(int)*ha*wa;
	int size2 = sizeof(int)*hb*wb;
	int size3 = sizeof(int)*ha*wb;
	a = (int*)malloc(ha*wa*sizeof(int));
	b = (int*)malloc(hb*wb*sizeof(int));
	t = (int*)malloc(ha*wb*sizeof(int));

	printf("Enter input matrix 1 : \n");
	for(i = 0;i<ha*wa;i++)
		scanf("%d",&a[i]);

	printf("Enter input matrix 2 : \n");
	for(i = 0;i<hb*wb;i++)
		scanf("%d",&b[i]);

	cudaMalloc((void**)&d_a,size1);
	cudaMalloc((void**)&d_b,size2);
	cudaMalloc((void**)&d_t,size3);
	cudaMemcpy(d_a,a,size1,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size2,cudaMemcpyHostToDevice);
	int gx,gy,bx,by;
	printf("Enter the dimension of the grid \n");
	scanf("%d %d",&gx,&gy);
	bx = ceil((double)ha/gx);
	by = ceil((double)wb/gy);
	printf("The dimensions of block are : \n %d %d \n",bx,by);
	dim3 grid(gx,gy);
	dim3 block(bx,by);
	mulElement<<<grid,block>>>(d_a,d_b,d_t,ha,wb,wa);
	cudaMemcpy(t,d_t,size3,cudaMemcpyDeviceToHost);
	printf("Result vector is :\n");
	for(i = 0;i<ha;i++)
	{
		for(j = 0;j<wb;j++)
		printf("%d ",t[i*wb+j]);
		printf("\n");
	}
	getchar();
	cudaFree(d_a);
	cudaFree(d_t);
	return 0;
}