#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void addElement(int *a,int *b,int *t)
{
	int v = threadIdx.y;
	int n = v*blockDim.x+threadIdx.x;
	t[n] = a[n]+b[n];
}

__global__ void addCol(int *a , int *b , int *t)
{
	int lp =0;
	int index = threadIdx.x;
 	for(lp = 0 ;lp<blockDim.x;lp++)
 	{	
 		t[index] = a[index]+b[index];
 		index += blockDim.x;
 	}

}

__global__ void addRow(int *a , int *b , int *t)
{
 	int lp =0;
 	int index = threadIdx.x*blockDim.x;
 	for(lp = 0 ;lp<blockDim.x;lp++)
 	{	
 	t[index] = a[index] + b[index];
 	index++;
 	}

}




int main(void)
{
	int *a,*b,*t,n,i,j;
	int *d_a,*d_b,*d_t;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	int size = sizeof(int)*n*n;
	a = (int*)malloc(n*n*sizeof(int));
	b = (int*)malloc(n*n*sizeof(int));
	t = (int*)malloc(n*n*sizeof(int));

	printf("Enter input matrix 1 : \n");
	for(i = 0;i<n*n;i++)
		scanf("%d",&a[i]);

	printf("Enter input matrix 2 : \n");
	for(i = 0;i<n*n;i++)
		scanf("%d",&b[i]);

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	cudaMalloc((void**)&d_t,size);
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

	printf("Enter 1 for Row \n 2 for Column \n 3 for Element \n");
	int ch;
	scanf("%d",&ch);
	if(ch == 1)
	{
	dim3 block(n,1);
	dim3 grid(1,1);
	addRow<<<grid,block>>>(d_a,d_b,d_t);
	}
	if(ch == 2)
	{
	dim3 block(n,1);
	dim3 grid(1,1);
	addCol<<<grid,block>>>(d_a,d_b,d_t);
	}
	if(ch == 3)
	{
	dim3 block(n,n);
	dim3 grid(1,1);
	addElement<<<grid,block>>>(d_a,d_b,d_t);
	}

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