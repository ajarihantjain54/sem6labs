#include<stdlib.h>
#include<stdio.h>



__global__ void add(int* a , int *b,int *c)
{
	int id = blockIdx.x*blockDim.x+threadIdx.x;
	c[id] = a[id] + b[id];
	printf("A = %d \t B = %d \t C = %d \n",a[id],b[id],c[id]);
}

int main(void)
{
	int *a , *b ,*c;
	int *d_a , *d_b ,*d_c;
	printf("Enter the value of N \n");
	int n;
	int i;
	scanf("%d",&n);
	printf("Enter your choice \n");
	int ch = 0;
	scanf("%d",&ch);
	a = (int*)malloc(sizeof(int)*n);
	b = (int*)malloc(sizeof(int)*n);
	c = (int*)malloc(sizeof(int)*n);
	printf("Enter the values for 1st Array \n");
	for( i = 0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter the values for 2nd Array \n");
	for(i = 0;i<n;i++)
		scanf("%d",&b[i]);
	int size = sizeof(int)*n;

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);
	cudaMalloc((void**)&d_c,size);
	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,size,cudaMemcpyHostToDevice);
	if(ch == 1)
		add<<<n,1>>>(d_a,d_b,d_c);
	else if(ch==2)
		add<<<1,n>>>(d_a,d_b,d_c);
	else if(ch == 3)
		add<<<n,256>>>(d_a,d_b,d_c);

	cudaMemcpy(c,d_c,size,cudaMemcpyDeviceToHost);
	printf("Result \n");
	for( i = 0;i<n;i++)
		printf("%d \t",c[i]);
	printf("\n");

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}
