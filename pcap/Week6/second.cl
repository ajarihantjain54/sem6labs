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
	int i;
	int LIST_SIZE;
	printf("Enter how many elements : ");
	scanf("%d",&LIST_SIZE);
	int* a = (int*) malloc(sizeof(int)*LIST_SIZE);
	printf("Enter the values \n");
	for(i =0;i<LIST_SIZE;i++)
	{
		scanf("%d",&a[i]);
	}

	//Load the kernel source code into the array source

	FILE *fp;
	char *source_str;
	size_t source_size;

	fp = fopen("strpos.cl","r");
	if(!fp)
	{
		fprintf(stderr,"Failed to load kernel \n ");
		getchar();
		exit(1);

	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str,1,MAX_SOURCE_SIZE,fp);
	fclose(fp);

	//Get platform and device information

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret = clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_CPU,1,&device_id,&ret_num_devices);

	//Create an OpenCL context
	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);

	// Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context,device_id,NULL,&ret);

	//Create memory buffers on the device for each vector A , B and C
	cl_mem a_mem_obj = clCreateBuffer(context,CL_MEM_READ_ONLY,LIST_SIZE*sizeof(int),NULL,&ret);
	cl_mem c_mem_obj = clCreateBuffer(context,CL_MEM_WRITE_ONLY,LIST_SIZE*sizeof(int),NULL,&ret);

	//copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue,a_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(int),a,0,NULL,NULL);
	printf("lalal %d\n", ret);
	// create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context , 1, (const char**)&source_str,(const size_t*)&source_size,&ret);
	printf("lalal %d\n", ret);
	//Build the program

	ret = clBuildProgram(program,1,&device_id,NULL,NULL,NULL);
	printf("lalal %d\n", ret);
	//Create the OpenCL kernel object
	cl_kernel kernel = clCreateKernel(program,"str_pos",&ret);
	printf("lalal %d\n", ret);
	//Set the arguments of the kernel

	ret = clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&a_mem_obj);
	//ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);
	ret = clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&c_mem_obj);


	printf("lalal %d\n", ret);
	ret = clSetKernelArg(kernel,2,sizeof(int),(void*)&LIST_SIZE);

	//Execute the OpenCL kernel on the array

	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;

	//Execute the kernel on the device
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,NULL);
	printf("lalal %d\n", ret);
	ret = clFinish(command_queue);

	cl_ulong time_start , time_end;
		double total_time;

		clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(time_start),&time_start,NULL);
		clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(time_end),&time_end,NULL);
		total_time = (double)(time_end - time_start);

	// Read the memory buffer C on the device to the local variable C
	int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
	ret = clEnqueueReadBuffer(command_queue,c_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(int),C,0,NULL,NULL);

	//Display the result on the screen
	for(i = 0;i<LIST_SIZE;i++)
		printf("%d \n ",C[i]);

	//clean up



	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);

	ret = clReleaseMemObject(c_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	end = clock();
	printf("\n\n Time taken to execute the KERNEL in milliseconds = %0.3f msec \n\n ",total_time/1000000);
	printf("\n\n Time taken to execute the whole program in seconds : %0.3f seconds \n",(end-start)/(double)CLOCKS_PER_SEC);


	free(a);
	//free(b);
	free(C);
	getchar();
	return 0;

}


