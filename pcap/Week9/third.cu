#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void mulRow(int *a , int *b , int *c , int wb , int cm)
{
	int id = threadIdx.x;
	int sum = 0;
	int i = 0;
	int j = 0;
	for(i = 0;i<wb;i++)
	{
		sum = 0;
		for(j=0;j<cm;j++)
			sum += a[id*cm+j]*b[wb*j+i];
		c[id*wb+i] = sum;
	}
}

__global__ void mulCol(int *a , int *b ,int *c,int ha , int wa , int wb)
{
	int  id = threadIdx.x;
	int sum ,j,i;
	for(i = 0;i<ha;i++)
	{
		sum = 0;
		for(j = 0;j<wa;j++)
		{
			sum += a[i*wa+j]*b[j*wb+id];
		}
		c[i*wb+id] = sum;
	}
}

__global__ void mulElement(int *a ,int *b , int *c,int wa , int wb)
{
	int rid = threadIdx.x;
	int cid = threadIdx.y;
	printf("rid = %d , cid = %d \n",rid,cid);
	int sum , i;
	sum = 0;
	for(i  = 0;i<wa;i++)
	{
	sum += a[rid*wa+i]*b[i*wb+cid];
	}
	c[rid*wb+cid] = sum;
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

	printf("Enter 1 for Row \n 2 for Column \n 3 for Element \n");
	int ch;
	scanf("%d",&ch);
	if(ch == 1)
	{
	dim3 block(wb,1);
	dim3 grid(1,1);
	mulRow<<<grid,block>>>(d_a,d_b,d_t,wb,wa);
	}
	if(ch == 2)
	{
	dim3 block(ha,1);
	dim3 grid(1,1);
	mulCol<<<grid,block>>>(d_a,d_b,d_t,ha,wa,wb);
	}
	if(ch == 3)
	{
	dim3 block(ha,wb);
	dim3 grid(1,1);
	mulElement<<<grid,block>>>(d_a,d_b,d_t,wa,wb);
	}

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

