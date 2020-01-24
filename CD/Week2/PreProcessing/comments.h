#include<stdio.h>
#include<stdlib.h>
void removeComments(FILE *fa , FILE* fb)
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
