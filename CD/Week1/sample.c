#include<stdio.h>
#include<stdlib.h>
void removeSpaces(FILE *fa , FILE* fb)
{
	int ca , cb;
	ca = getc(fa);
	while(ca != EOF)
	{
		if(ca == '/')
		{
			cb = getc(fa);
			if(cb == '/')
			{
				while(ca != '\n')
					ca = getc(fa);

			}
			else if(cb == '*')
			{
				do
				{
					while(ca!= '*')
						ca = getc(fa);
					ca = getc(fa);

				}while(ca!= '/');

			}
			else
			{
				putc(ca,fb);
				putc(cb,fb);
			}
		}
		else 
			putc(ca,fb);
		ca = getc(fa);

	}
}
int main()
{
	FILE *fa , *fb;
	fa = fopen("q4in.c","r");
	if(fa == NULL) 
	{
		printf("Cannot open file \n");
		exit(0);

	}
	fb = fopen("q4out.c","w");	
	removeSpaces(fa,fb);
	fclose(fa);
	fclose(fb);
	return 0;

}