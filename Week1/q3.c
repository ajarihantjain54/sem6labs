#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void removeSpaces(FILE *fa , FILE *fb)
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
		else 
		{
			putc(ca , fb);
		}
		ca = getc(fa);
	}
}



int isKeyword(char* str)
{
	if (!strcmp(str, "auto") || !strcmp(str, "default")  
        || !strcmp(str, "signed") || !strcmp(str, "enum")  
        ||!strcmp(str, "extern") || !strcmp(str, "for")  
        || !strcmp(str, "register") || !strcmp(str, "if")  
        || !strcmp(str, "else")  || !strcmp(str, "int") 
        || !strcmp(str, "while") || !strcmp(str, "do") 
        || !strcmp(str, "break") || !strcmp(str, "continue")  
        || !strcmp(str, "double") || !strcmp(str, "float") 
        || !strcmp(str, "return") || !strcmp(str, "char") 
        || !strcmp(str, "case") || !strcmp(str, "const") 
        || !strcmp(str, "sizeof") || !strcmp(str, "long") 
        || !strcmp(str, "short") || !strcmp(str, "typedef") 
        || !strcmp(str, "switch") || !strcmp(str, "unsigned") 
        || !strcmp(str, "void") || !strcmp(str, "static") 
        || !strcmp(str, "struct") || !strcmp(str, "goto") 
        || !strcmp(str, "union") || !strcmp(str, "volatile")) 
        return 1; 
    return 0; 
}


int isChar(int c)
{
	    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    else
        return 0;
}


void printKeywords()
{
printf("Lets print keywords \n");
int line = 0;
int column = 0;
FILE *fc;
fc = fopen("q3out.c","r");
int ca , cb;
ca = getc(fc);
while(ca != EOF)
{
	if(ca == '\n')
		line++;
	if(isChar(ca) != 0)
	{
		char* word = (char*)malloc(sizeof(char)*20);
		int pos = 0;
		word[pos] = (char)ca;
		pos++;
		cb = getc(fc);

		while(isChar(cb) != 0)
		{
			word[pos] = (char)cb;
			pos++;
			cb = getc(fc);
		}
		word[pos] = '\0';
		
		
		if(isKeyword(word) == 1)
		{
			for(int i = 0;i<pos;i++)
			{
				char b = toupper(word[i]);
				printf("%c",b);
			}
			printf("\n");
			 printf("\n Line number = %d \n",line);
		}

	}
	ca = getc(fc);
}

}



int main()
{
	// printf("Enter the file name \n");
	// char* str = (char*)malloc(sizeof(char)*20);
	// gets(str);
	// printf("\n %s",str);
	// FILE *fa , *fb;
	// fa = fopen(str,"r");
	// fb = fopen("q3out.c","w");
	// removeSpaces(fa,fb);
	// fclose(fb);
	// printf("\nThe spaces have been removed \n");
	printKeywords();

}


