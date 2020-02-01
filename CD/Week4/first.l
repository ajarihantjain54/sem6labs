%{
	#include<stdio.h>
	int vow=0,con=0;
%}

%%

[\t\n ]+	;
[aeiouAEIOU]	{vow+=1;}
[a-zA-Z]	{con+=1;}

%%

int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	yyin = fopen("q1.txt","r");
	yylex();
	printf("Vowels count: %d\n Consonants count: %d",vow,con);
	return 0;
}