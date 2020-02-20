#include<stdlib.h>
#include<stdio.h>



__global__ void add(int* a , int *b)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
	b[id] = sin(a[id]);
}

int main(void)
{
	int *a , *b , c;
	int *d_a , *d_b ,*d_c;
	printf("Enter the value of N \n");
	int n;
	int i;
	scanf("%d",&n);
	a = (int*)malloc(sizeof(int)*n);
	b = (int*)malloc(sizeof(int)*n);
	printf("Enter the values for 1st Array \n");
	for( i = 0;i<n;i++)
		scanf("%d",&a[i]);
	int size = sizeof(int)*n;

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);

	add<<<1,n>>>(d_a,d_b);

	cudaMemcpy(b,d_b,size,cudaMemcpyDeviceToHost);
	printf("Result \n");
	for( i = 0;i<n;i++)
		printf("%d \t",b[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);
	return 0;
}
