#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


__global__ void complement(int* a , int* b,int n)
{
	int id = threadIdx.x;
	int m = blockDim.x;
	int j = 0;
	if(id!=0 && id!=(m-1))
	{
		for(j=1;j<n-1;j++)
		{
			int rem = 0,p=0;
			int d = a[id*m+j];
			for(p=1;d>0;p = p*10)
			{
				rem = d%2;
				if(rem == 0)
					rem =1;
				else
					rem = 0;
				b[id*m+j] += p*rem;
				d = d/2;
			}
		}
		b[id*m+0] = a[id*m+0];
		b[id*m+n-1] = a[id*m+n-1];
	}
	else
	{
		for(j=0;j<n;j++)
			b[id*m+j] = a[id*m+j];
	}

}

int main(void)
{
	int *a,*t,n,m,i,j;
	int *d_a,*d_t;
	printf("Enter the value of m and n ");
	scanf("%d",&m);
	scanf("%d",&n);
	int size = sizeof(int)*m*n;
	a = (int*)malloc(m*n*sizeof(int));
	t = (int*)malloc(m*n*sizeof(int));
	printf("Enter input matrix: \n");
	for(i = 0;i<m*n;i++)
		scanf("%d",&a[i]);
	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_t,size);
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	dim3 threadsPerBlock(m,1);
	dim3 numBlocks(1,1);
	complement<<<numBlocks,threadsPerBlock>>>(d_a,d_t,n);
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