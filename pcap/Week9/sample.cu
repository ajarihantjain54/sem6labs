#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void transpose(int *a,int *t)
{
	int v = threadIdx.y;
	int n = v*blockDim.x+threadIdx.x;
	int ta = (int)powf(a[n],v+1);
	t[n] = ta;
	printf("%d row %d element  = %d  result  \n",v,n,ta);
}


int main(void)
{
	int *a,*t,n,i,j;
	int *d_a,*d_t;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	int size = sizeof(int)*n*n;
	a = (int*)malloc(n*n*sizeof(int));
	t = (int*)malloc(n*n*sizeof(int));
	printf("Enter input matrix: \n");
	for(i = 0;i<n*n;i++)
		scanf("%d",&a[i]);
	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_t,size);
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	dim3 threadsPerBlock(n,n);
	dim3 numBlocks(1,1);
	transpose<<<numBlocks,threadsPerBlock>>>(d_a,d_t);
	cudaMemcpy(t,d_t,size,cudaMemcpyDeviceToHost);
	printf("Result vector is :\n");
	for(i = 0;i<n;i++)
	{
		for(j = 0;j<n;j++)
			printf("%d ",t[i*n+j]);
		printf("\n");
	}
	getchar();
	cudaFree(d_a);
	cudaFree(d_t);
	return 0;
}