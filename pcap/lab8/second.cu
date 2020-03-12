#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

__global__ void reverseWord(char *a , char *b , int size)
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
        b[start] = ' ';
        j = start+1;
    }
    else
        j = start;
   	i = end-1;
    for(;j<=i;j++,i--)
    {
        b[j] = a[i];
        b[i] = a[j];
    }
   


}


int main()
{
    int n;
    int size;
    char *a = (char*)malloc(sizeof(char)*(30));
    printf("Enter the string \n");
    scanf("%[^\n]%*c", a); 
    printf("Enter number of words \n");
    scanf("%d",&n);
    char *b = (char*)malloc(sizeof(char)*(30));
    char *d_a , *d_b;
    printf("Input String =  %s \n",a);
    size = strlen(a);
    int size1 = sizeof(char)*(size+1);
    int size2 = sizeof(char)*(size+1);
    cudaMalloc((void**)&d_a,size1);
    cudaMalloc((void**)&d_b,size2);
    cudaMemcpy(d_a,a,sizeof(char)*(size+1),cudaMemcpyHostToDevice);
    reverseWord<<<1,n>>>(d_a,d_b,size);
    cudaMemcpy(b,d_b,size2,cudaMemcpyDeviceToHost);
    printf("Output string =  %s \n",b);
    
    cudaFree(d_a);
    cudaFree(d_b);


}


