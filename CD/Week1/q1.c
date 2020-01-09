#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa , *fb;
	int ca , cb;
	fa = fopen("q1in.c","r");
	if(fa == NULL)
	{
		printf("The file was not found");
		exit(0);
	}
	fb = fopen("q1out.c","w");
	ca = getc(fa);
	while(ca != EOF)
	{
		printf("%d \n",ca);
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
		else 
		{
			putc(ca , fb);
		}
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);


}

