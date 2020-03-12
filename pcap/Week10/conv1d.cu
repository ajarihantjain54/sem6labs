#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void convolution_1D(float *N , float *M , float *P , int Mask_width,int width)
{
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	float pvalue = 0.0;
	int N_start_point = i - ((Mask_width)/2);
	for(int j =0;j<Mask_width;j++)
	{
		if(((N_start_point+j)>=0)&& ((N_start_point + j)<width))
		{
			pvalue  += N[N_start_point + j] * M[j];
		}
	}
	P[i] = pvalue;
}

int main()
{
	float *a , *m , *t;
	float *d_a, *d_m, *d_t;
	int width , mask_width;
	printf("Enter the size of array \n");
	scanf("%d",&width);
	a = (float*)malloc(sizeof(float)*width);
	t = (float*)malloc(sizeof(float)*width);
	printf("Enter the array \n");
	int i = 0;
	for(i = 0;i<width;i++)
	{
		scanf("%f",&a[i]);
	}
	printf("Enter the size of mask \n");
	scanf("%d",&mask_width);
	m = (float*)malloc(sizeof(float)*mask_width);
	printf("Enter the mask \n");
	for(i = 0;i<mask_width;i++)
	{
		scanf("%f",&m[i]);
	}
	int size1 = sizeof(float)*width;
	int size2 = sizeof(float)*mask_width;
	cudaMalloc((void**)&d_a,size1);
	cudaMalloc((void**)&d_m,size2);
	cudaMalloc((void**)&d_t,size1);
	cudaMemcpy(d_a,a,size1,cudaMemcpyHostToDevice);
	cudaMemcpy(d_m,m,size2,cudaMemcpyHostToDevice);
	dim3 dimGrid((width-1)/mask_width + 1,1,1);
	dim3 dimBlock(mask_width,1,1);
	convolution_1D<<<dimGrid,dimBlock>>>(d_a,d_m,d_t,mask_width,width);
	cudaMemcpy(t,d_t,size1,cudaMemcpyDeviceToHost);
	printf("The result array is \n");
	for(int i = 0;i<width;i++)
	{
		printf("%f ",t[i]);
	}
	printf("\n");
	cudaFree(d_a);
	cudaFree(d_m);
	cudaFree(d_t);


}