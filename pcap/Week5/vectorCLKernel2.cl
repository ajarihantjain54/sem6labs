__kernel void vector_add(__global int*A ,__global int* C)
{
	//Get the index of the current work item
	int i = get_global_id(0);
	//Do the operation
	//printf("%d && %d \n",C[i],C[i+1]);
	if(i%2 == 0)
	{
		C[i] = A[i+1];
		C[i+1] = A[i];
	}
}

