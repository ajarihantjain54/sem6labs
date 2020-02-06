// vectorCLKernel.cl

__kernel void vector_add(__global int*A ,__global int* C)
{
	//Get the index of the current work item
	int i = get_global_id(0);
	//Do the operation
	C[i] = 0;
	int ans = 0;
	int d = A[i];
	int p = 1;
	int rem = 0;
	while(d>0)
	{
	 rem  = d%8;
	 C[i] += p*rem;
	 d = d/8;
	 p = p*10;
	
	}
	
}

