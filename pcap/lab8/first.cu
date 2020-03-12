#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


__global__ void multipleStrings(char* a ,  char* b,int size)
{
	int i = threadIdx.x * size;
	int j = 0;
	for(j=0;j<size;j++)
	{
		b[i+j] = a[j];
	}
}

int main()
{
	cudaError_t error;
	int n;
	int size;
	printf("Enter the value of n \n");
	scanf("%d",&n);
	printf("Enter the size of the string \n");
	scanf("%d",&size);
	char *a = (char*)malloc(sizeof(char)*(size+1));
	printf("Enter the string \n");
	scanf("%s",a);
	cudaEvent_t start,stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	char *b = (char*)malloc(sizeof(char)*(n*size+1));
	char *d_a , *d_b;
	int size1 = sizeof(char)*(size+1);
	int size2 = sizeof(char)*(size*n+1);
	cudaMalloc((void**)&d_a,size1);
	cudaMalloc((void**)&d_b,size2);
	error = cudaMemcpy(d_a,a,sizeof(char)*(size+1),cudaMemcpyHostToDevice);	
	multipleStrings<<<1,n>>>(d_a,d_b,size);
	cudaMemcpy(b,d_b,size2,cudaMemcpyDeviceToHost);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime,start,stop);
	int l = strlen(b);
	printf("string = %s \n",b);
	printf("Time taken = %f \n",elapsedTime);
	cudaFree(d_a);
	cudaFree(d_b);


}


