// vectorCLKernel.cl

__kernel void vector_add(__global int*A ,__global int* C)
{
	//Get the index of the current work item
	int i = get_global_id(0);
	//Do the operation
	C[i] = 0;
	int ans = 0;
	int d = A[i];

	int rem = 0;
	for(int p = 1;d>0;p = p*10)
	{
	 rem  = d%10;
	 if(rem == 0)
	 	rem = 1;
	 else
	 	rem = 0;
	 C[i] += p*rem;
	 d = d/10;
	}
	
}

