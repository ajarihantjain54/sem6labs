#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<cuda.h>



__global__ void add(float *a , float *b)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
	b[id] = sinf(a[id]);
}

int main(void)
{
	float *a , *b ;
	float *d_a , *d_b ;
	printf("Enter the value of N \n");
	int n;
	int i;
	scanf("%d",&n);
	a = (float*)malloc(sizeof(float)*n);
	b = (float*)malloc(sizeof(float)*n);
	printf("Enter the values for 1st Array \n");
	for( i = 0;i<n;i++)
		scanf("%f",&a[i]);
	int size = sizeof(float)*n;

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

	add<<<1,n>>>(d_a,d_b);

	cudaMemcpy(b,d_b,size,cudaMemcpyDeviceToHost);
	printf("Result \n");
	for( i = 0;i<n;i++)
		printf("%f \t",b[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);
	return 0;
}
