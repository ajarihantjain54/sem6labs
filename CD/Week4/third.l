%{
	#include<stdio.h>
	int posi=0,negi=0,posf=0,negf=0; 
%}

%%

[0-9]+ {posi++;}
[-][0-9]+ {negi++;}
[0-9]+[.][0-9]+ {posf++;}
[-][0-9]+[.][0-9]+ {negf++;}

%%

int yywrap() {
	return 1;
}

int main(int argc, char *argv[]) {
	yyin = fopen("q1.txt","r");
	yylex();
	printf("+ve Int count: %d\n -ve Int count: %d\n+ve FLoat count: %d\n-ve Float count: %d",posi,negi,posf,negf);
	return 0;
}