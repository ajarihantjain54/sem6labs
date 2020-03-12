#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



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

	printf("Enter sparse matrix  : \n");
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
	
	mulElement<<<1,ha>>>(d_a,d_b,d_t,ha,wb,wa);
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