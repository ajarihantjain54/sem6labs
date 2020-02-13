__kernel void str_pos( __global char* a , __global char* b , int s )
{
	
	int i = get_global_id(0);
	printf("i = %d , a[i] = %d \n",i,a[i]);
	/*int pos = 0;
	printf("s = %d \n",s);
	int j = 0;
	for(j = 0;j<s;j++)
	{
		if(a[j]<a[i])
			pos++;
	}
	b[pos] = a[i];
	printf("pos = %d , val = %d \n",pos,a[i]);*/
	
		
}