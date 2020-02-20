#include<stdlib.h>
#include<stdio.h>



__global__ void add(int* a , int *b,int *c)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
	b[id] = (a[id] * (*c)) + b[id];
	//printf("A = %d \t B = %d \t C = %d \n",a[id],b[id],*c);
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
	printf("Enter the value of alpha \n");
		scanf("%d",&c);
	printf("Enter the values for 1st Array \n");
	for( i = 0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter the values for 2nd Array \n");
	for(i = 0;i<n;i++)
		scanf("%d",&b[i]);
	int size = sizeof(int)*n;

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	cudaMalloc((void**)&d_c,sizeof(int));
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_c,&c,sizeof(int),cudaMemcpyHostToDevice);
	add<<<1,n>>>(d_a,d_b,d_c);

	cudaMemcpy(b,d_b,size,cudaMemcpyDeviceToHost);
	printf("Result \n");
	for( i = 0;i<n;i++)
		printf("%d \t",b[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);
	return 0;
}
