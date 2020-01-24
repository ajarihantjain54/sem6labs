#include<stdio.h>
#include<stdlib.h>

void removeSpaces(FILE *fa, FILE *fb)
{
	int ca , cb;
	ca = getc(fa);
	while(ca != EOF)
	{
		//printf("%d \n",ca);
		if(ca == ' ' || ca == '\t')
		{
			cb = getc(fa);
		}
	}
}

