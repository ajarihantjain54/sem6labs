#include<stdio.h>
#include<stdlib.h>
void removePreprocessor(FILE *fa , FILE *fb)
{
	int ca , cb;
	ca = getc(fa);
	while(ca != EOF)
	{
		//printf("%d \n",ca);
		if(ca == '#')
		{
			cb = getc(fa);
			while(cb != '\n')
			{
				cb = getc(fa);
			}
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
int main()
{
	FILE *fa , *fb;
	
	fa = fopen("q2in.c","r");
	if(fa == NULL)
	{
		printf("The file was not found");
		exit(0);
	}
	fb = fopen("q2out.c","w");
	removePreprocessor(fa ,fb);
	fclose(fa);
	fclose(fb);


}

