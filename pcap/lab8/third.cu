#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void countWord(char *a , char *b , unsigned int* d_count , int size , int wordSize)
{
    int id = threadIdx.x+1;
    int cur = 0;
    int start = 0;
    int end = size;
    int j = 0;
    for(j = 0;j<size;j++)
    {
        if(a[j] == ' ')
        {
            cur++;
            if(cur == id)
            {
                end = j;
                break;
            }
            else
            {
                start = j;
            }
        }
    }


    int i = 0;
    if(start!=0)
    {
        j = start+1;
    }
    else
        j = start;
   	i = end-1;


    int k = 0;
    int flag = 1;

   for(k = 0;k<wordSize;k++,j++)
   {
    if(a[j]!=b[k] || j>i)
        {
            flag = -1;
            break;
        }
   }

   if(flag == 1)
    atomicAdd(d_count,1);



}


int main()
{
    int n;
    unsigned int *count = 0,*d_count,*result = 0;
    count = (unsigned int*)malloc(sizeof(unsigned int));
    result = (unsigned int*)malloc(sizeof(unsigned int));
    char *a = (char*)malloc(sizeof(char)*(30));
    int size = sizeof(int);
    printf("Enter the string \n");
    scanf("%[^\n]%*c", a); 
    printf("Enter number of words \n");
    scanf("%d",&n);
    char *b = (char*)malloc(sizeof(char)*(30));
    printf("Enter the word \n");
    scanf("%s",b);
    char *d_a , *d_b;
    printf("Input String =  %s \n",a);
    int wordSize = strlen(b);
    int size1 = sizeof(char)*30;
    int size2 = sizeof(char)*30;
    cudaError_t error;
    error = cudaMalloc((void**)&d_a,size1);
    if(error != cudaSuccess)
    {
        printf("Error in first malloc\n");
        exit(0);
    }
    error = cudaMalloc((void**)&d_b,size2);
    if(error != cudaSuccess)
    {
        printf("Error in second malloc\n");
        exit(0);
    }
    error = cudaMalloc((void**)&d_count,sizeof(unsigned int));
    if(error != cudaSuccess)
    {
        printf("Error in third malloc \n");
        exit(0);
    }
    error = cudaMemcpy(d_count,count,sizeof(*count),cudaMemcpyHostToDevice);
    if(error != cudaSuccess)
    {
        printf("Error in first\n");
        printf("Cuda error 2: %s \n",cudaGetErrorString(error));
        exit(0);
    }
    error = cudaMemcpy(d_a,a,size1,cudaMemcpyHostToDevice);
    if(error != cudaSuccess)
    {
        printf("Error in second\n");
        exit(0);
    }
    error = cudaMemcpy(d_b,b,size2,cudaMemcpyHostToDevice);
    if(error != cudaSuccess)
    {
        printf("Error in third\n");
        exit(0);
    }
    size = strlen(a);
    countWord<<<1,n>>>(d_a,d_b,d_count,size,wordSize);
    cudaMemcpy(result,d_count,sizeof(unsigned int),cudaMemcpyDeviceToHost);
    printf("Total occurences of %s = %d \n",b,*result);
    cudaFree(d_a);
    cudaFree(d_b);


}


