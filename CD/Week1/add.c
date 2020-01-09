#include <stdio.h>
#include <stdlib.h>

void putLineNum(int line, FILE *fout)
{
	int rem = 0;
	while(line > 0)
	{
		rem = line%10;
		putc((rem+48), fout);
		line = line/10;
	}
}

int revNum(int n)
{
	int rem,rev = 0;
	while(n > 0)
	{
		rem = n%10;
		n = n/10;
		rev = (rev*10)+rem;
	}
	return rev;
}

int main()	
{
	FILE *fa, *fb;
	int ca, cb;
	int line = 1;
	fa = fopen("input4.txt","r");
	if(fa == NULL)
	{
		printf("\nCannot open file");
		exit(0);
	}
	fb = fopen("output4.txt","w");
	putLineNum(line, fb);
	putc(' ', fb);
	line = line + 1;
	ca = getc(fa);
	while(ca != EOF)
	{
		putc(ca, fb);
		if(ca == '\n')
		{
			putLineNum(revNum(line), fb);
			if(line%100 == 0)
				putc('0', fb);
			if(line%10 == 0)
				putc('0', fb);
			putc(' ', fb);
			line = line + 1;
		}
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}