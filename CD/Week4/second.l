%{
	#include<stdio.h>
	int w=0,l=0,c=0,b=0; 
%}

%%

[\n]+	{l++;}
[ ]	{b+=1;}
[a-zA-Z0-9]+ {c+=strlen(yytext); w+=1;}

%%

int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	yyin = fopen("q1.txt","r");
	yylex();
	printf("Words count: %d\n Lines count: %d\nCharacters count: %d\nBlanks count: %d",w,l,c,b);
	return 0;
}