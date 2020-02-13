__kernel void str_copy( __global char* a , __global char* b , int len)
{
	printf("len = %d \n",len);
	int i = get_global_id(0);
	int start = i*len;
	printf(" start = %d \n",start);
	printf(" i = %d \n",i);
	int j = 0;
	for(j = 0;j<len;j++)
	{
		b[start] = a[j];
		start++;
	}
	
		
}