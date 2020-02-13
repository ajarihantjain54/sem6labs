#include <stdio.h>
#include <time.h>
#include <CL/cl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define MAX_SOURCE_SIZE(0x100000)

int main(void)
{
	time_t start , end;
	start = clock();

	char tempstr[20486];

	int i;
	for(i = 0;i<20485;i++)
		tempstr[i] = 'A';
	tempstr[20485] = '\0';

	int len = strlen(tempstr);
	len++;

	char* str = (char*)malloc(sizeof(char)*len);
	strcpy(str,tempstr);

	FILE *fp;
	char* source_str;
	size_t source_size;
	fp = fopen("strtoggle.cl","r");
	if(!fp){
		print("Failed to load kernel\n");
	}

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);
	fclose(fp);


	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	cl_int ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_CPU,1,&device_id,&ret_num_devices);

	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);
	cl_command_queue command_queue = clCreateCommandQueue(context , device_id,CL_ENQUEUE_PROFILING_ENABLE,&ret);

	cl_mem s_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,len*sizeof(char),NULL,&ret);
	cl_mem t_mem_obj = clCreateBuffer(context , CL_MEM_WRITE_ONLY,len*sizeof(char),NULL,&ret);

	ret = clEnqueueWriteBuffer(command_queue,s_mem_obj,CL_TRUE,0,len*sizeof(char),str,0,NULL,NULL);

	cl_program program = clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t*)&source_size,&ret);

	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);
	cl_kernel kernel = clCreateKernel(program,"str_chgcase",&ret);

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&s_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&t_mem_obj);

	size_t global_item_size =  len;
	size_t local_itme_size = 1;

	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,&global_item_size,&local_itme_size,0,NULL,&event);
	time_t stime = clock();

	ret = clFinish(command_queue);

	cl_ulong time_start , time_end;
	double total_time;

	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(time_start),&time_start,NULL);
	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(time_end),&time_end,NULL);
	total_time = (double)(time_end - time_start);

	char *strres = (char*)malloc(sizeof(char)*len);

	ret = clEnqueueReadBuffer(command_queue,t_mem_obj,CL_TRUE,0,len*sizeof(char),strres,0,NULL,NULL);

	printf("\n Done \n");
	strres[len-1] = '\0';
	printf("\n Resultant toggled string :%s",strres);
	getchar();

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObjects(s_mem_obj);
	ret = clReleaseMemObjects(t_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	end = clock();
	printf("\n\n Time taken to execute the KERNEL in milliseconds = %0.3f msec \n\n ",total_time/1000000);
	printf("\n\n Time taken to execute the whole program in seconds : %0.3f seconds \n",(end-start)/(double)CLOCKS_PER_SEC);

	free(str);
	free(strres);
	getch();
	return 0;
	
}