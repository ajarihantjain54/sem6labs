	#include <stdio.h>
#include <time.h>
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_SOURCE_SIZE (0x100000)

int main(void)
{
	time_t start , end;
	start = clock();

	int len = 0 , n = 0;
	printf("Enter the length of the string \n");
	scanf("%d",&len);
	len;
	char *str = (char*)malloc(sizeof(char)*(len+1));
	printf("Enter the string \n");
	scanf("%s",str);
	printf("Enter the value of n \n");
	scanf("%d",&n);
	char* result = (char*)malloc(sizeof(char)*(len*n+1));
	printf("I am alive %d \n",__LINE__);
	FILE *fp;
	char* source_str;
	size_t source_size;
	fp = fopen("strcopy.cl","r");
	if(!fp){
		printf("Failed to load kernel\n");
	}

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);
	fclose(fp);
	printf("I am alive %d \n",__LINE__);


	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	printf("%d \n",ret);

	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_CPU,1,&device_id,&ret_num_devices);
	printf("%d \n",ret);
	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);
	printf("%d \n",ret);
	cl_command_queue command_queue = clCreateCommandQueue(context , device_id,CL_QUEUE_PROFILING_ENABLE,&ret);
	printf("%d \n",ret);
	cl_mem s_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,len*sizeof(char),NULL,&ret);
	printf("%d \n",ret);
	//cl_mem len_mem_obj = clCreateBuffer(context , CL_MEM_READ_ONLY,sizeof(int),NULL,&ret);
	//printf("%d \n",ret);
	cl_mem t_mem_obj = clCreateBuffer(context , CL_MEM_WRITE_ONLY,(len*n)*sizeof(char),NULL,&ret);
	printf("%d \n",ret);

	ret = clEnqueueWriteBuffer(command_queue,s_mem_obj,CL_TRUE,0,len*sizeof(char),str,0,NULL,NULL);
	printf("%d \n",ret);
	//ret = clEnqueueWriteBuffer(command_queue,len,CL_TRUE,0,sizeof(int),&len,0,NULL,NULL);
	//printf("%d \n",ret);


	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t*)&source_size,&ret);
	printf("%d %d \n",ret,5);

	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);
	printf("%d \n",ret);
	cl_kernel kernel = clCreateKernel(program,"str_copy",&ret);
	printf("%d \n",ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&s_mem_obj);
	printf("%d \n",ret);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&t_mem_obj);
	printf("%d \n",ret);
	ret = clSetKernelArg(kernel,2,sizeof(int),(void*)&len);
	printf("%d \n",ret);

	size_t global_item_size =  n;
	size_t local_itme_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,&global_item_size,&local_itme_size,0,NULL,&event);
	printf("%d \n",ret);
	time_t stime = clock();
	printf("I am alive %d \n",__LINE__);
	ret = clFinish(command_queue);

	cl_ulong time_start , time_end;
	double total_time;

	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(time_start),&time_start,NULL);
	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(time_end),&time_end,NULL);
	total_time = (double)(time_end - time_start);

	ret = clEnqueueReadBuffer(command_queue,t_mem_obj,CL_TRUE,0,(len*n)*sizeof(char),result,0,NULL,NULL);
	printf("%d \n",ret);
	printf("\n Done \n");
	result[len*n+1] = '\0';
	printf("\n Resultant toggled string :%s",result);

	getchar();

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(s_mem_obj);
	ret = clReleaseMemObject(t_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	end = clock();
	printf("\n\n Time taken to execute the KERNEL in milliseconds = %0.3f msec \n\n ",total_time/1000000);
	printf("\n\n Time taken to execute the whole program in seconds : %0.3f seconds \n",(end-start)/(double)CLOCKS_PER_SEC);

	free(str);
	free(result);
	getchar();
	return 0;

}
