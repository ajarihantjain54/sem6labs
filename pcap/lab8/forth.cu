#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void reverseWord(char *a , char *b , int size)
{
    int id = threadIdx.x;
    b[size-id] = a[id];
}




int main()
{
    int size;
    char *a = (char*)malloc(sizeof(char)*(30));
    printf("Enter the string \n");
    scanf("%[^\n]%*c", a); 
    char *b = (char*)malloc(sizeof(char)*(30));
    char *d_a , *d_b;
    printf("Input String =  %s \n",a);
    size = strlen(a);
    int size1 = sizeof(char)*(size+1);
    int size2 = sizeof(char)*(size+1);
    cudaMalloc((void**)&d_a,size1);
    cudaMalloc((void**)&d_b,size2);
    cudaMemcpy(d_a,a,sizeof(char)*(size+1),cudaMemcpyHostToDevice);
    reverseWord<<<1,size>>>(d_a,d_b,size-1);
    cudaMemcpy(b,d_b,size2,cudaMemcpyDeviceToHost);
    printf("Output string =  %s \n",b);
    
    cudaFree(d_a);
    cudaFree(d_b);


}