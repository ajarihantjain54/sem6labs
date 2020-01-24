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
			while(cb == ' ' || cb == '\t' || cb == '\n')
			{
				cb = getc(fa);
			}
			ca = cb;
			cb = ' ';
			putc(cb,fb);
			putc(ca,fb);
		}
		else if(ca == '"')
		{
			putc(ca,fb);
			ca = getc(fa);
			while(ca != '"')
			{
				putc(ca,fb);
				ca = getc(fa);
			}
			putc(ca,fb);
		}
		else 
		{
			putc(ca , fb);
		}
		ca = getc(fa);
	}
}



