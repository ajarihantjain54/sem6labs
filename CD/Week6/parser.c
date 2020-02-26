#include<stdio.h>
#include<ctype.h>
#include "lexel.c"
#include<string.h>

struct token lookahead;

int i = 0;

char types[][20] = {"NOTHING","STRING-LITERAL" , "KEYWORD" , "IDENTIFIER" , "DIGIT-LITERAL", "LB", "RB","LC","RC","ASSIGNMENT-OPERATOR","RELATIONAL-OPERATOR","LOGICAL-OPERATOR","SPEICAL-SYMBOLS","LSB","RSB" ,"ERROR"};

void proc_identifierList();
void proc_statementList();
void proc_program()
{
	int flag = 0;
	lookahead = getNextToken();
	if((!strcmp(lookahead.type == 3)) && (!strcmp(lookahead.lexemename,"main")))
	{
		lookahead = getNextToken();
		if(lookahead.type == 5)
		{
			lookahead = getNextToken();
			if(lookahead.type == 6)
			{
				lookahead = getNextToken();
				if(lookahead.type == 7)
				{

					proc_declarations();
					proc_statementList();
					lookahead = getNextToken();
					if(lookahead.type == 8)
					{
						flag = 1;
						printf("The string has been accepted \n");
					}

				}
			}
		}
	}
	if(flag == 0)
		printf("Error Box Box \n");
}

void isDataType(char* str)
{
	if(!strcmp(str,"int")||!strcmp(str,"double")||!strcmp(str,"float")
		|| !strcmp(str,"long") || !strcmp(str,"short"))
	{
		return 1;
	}
	else
		return 0;
}

void proc_declarations()
{
	printf("Inside proc_declarations \n");
	int flag = 0;
	if(lookahead.type = 2)
	{
		if(isDataType())
		{
			proc_identifierList();
			lookahead = getNextToken();
			if(lookahead.type == 12 && !strcmp(lookahead.lexemename,";"))
			{
				flag = 1;
				lookahead= getNextToken();
				proc_declarations();
			}
		}
	}
	else
		return;
	if(flag == 0)
	{
		printf("Error inside declarations \n");
		exit(0);
	}


}

void proc_identifierList()
{
	printf("Inside Identifier List \n");
	int flag = 0;
	lookahead = getNextToken();
	if(lookahead.type == 3)
	{
		lookahead = getNextToken();
		if(lookahead.type == 12 && !strcmp(lookahead.lexemename,","))
		{
			flag = 1;
			proc_identifierList();

		}
		else if(lookahead.type == 13)
		{
			lookahead = getNextToken();
			if(lookahead.type == 4)
			{
				lookahead = getNextToken();
				if(lookahead.type == 14)
				{
					flag = 1;
					lookahead = getNextToken();
					if(lookahead.type == 12 && !strcmp(lookahead.lexemename,","))
					{
						proc_identifierList();
					}
					else
						return;
				}
			}
		}
		else
		{
			return;
		}

	}
	if(flag == 0)
	{
		printf("Error inside Identifier List \n");
		exit(0);
	}
}

void proc_statementList()
{
	printf("Inside proc_statementList \n");
	if(proc_statement() == 1)
	{
		proc_statementList();
	}
	else
		return;


}

int proc_statement()
{
	printf("Inside proc_statement \n");
	return proc_assignStat();
}

int proc_assignStat()
{
	printf("Inside proc_assignStat \n");
	int flag = 0;
	if(lookahead.type == 3)
	{
		lookahead = getNextToken();
		if(	lookahead.type == 12 && !strcmp(lookahead.lexemename,"="))
		{
			flag = 1;
			return proc_expn();
		}
	}
	if(flag == 0)
	{
		return -1;
	}
}

int proc_expn()
{
	printf("Inside proc_expn \n");
	int i =  proc_simpleExpn();

}


int proc_mulop()
{
	printf("Inside proc_mulop \n");
	if(lookahead.type == 9 && (!strcmp(lookahead.lexemename,"/") || !strcmp(lookahead.lexemename ,"*") || !strcmp(lookahead.lexemename,"%") ))
	{
		return 1;
	}
	else
		return -1;
}

int proc_addop()
{
	printf("Inside proc_addop \n");
	if(lookahead.type == 9 && (!strcmp(lookahead.lexemename,"+")|| !strcmp(lookahead.lexemename,"-")))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int proc_relop()
{
	printf("Inside proc_relop \n");
	if(lookahead.type == 10)
	{
		return 1;
	}
	else
		return -1;
}

int proc_factor()
{
	printf("Inside proc_factor \n");
	if(lookahead.type == 3 || lookahead.type == 4)
		return 1;
	else
		return -1;
}

int proc_tprime()
{
	int flag = 0;
	printf("Inside proc_tprime \n");
	if(proc_mulop() == 1)
	{
		if(proc_factor() == 1)
		{
			flag = 1;
			return proc_tprime();
		}
	}
	else
		return 1;
	if(flag == 0)
		return -1;
}

int proc_term()
{
	int flag = 0;
	printf("Inside proc_term \n");
	if(proc_factor() == 1)
	{
		return proc_tprime;
	}
	else
	{
		return -1;
	}
}

int proc_seprime()
{
	int flag = 0;
	if(proc_addop() == 1)
	{
		if(proc_term() == 1)
		{
			flag = 1
			return proc_seprime();
		}
	}
	else
		return 2;
	if(flag == 0)
		return -1;
}


int proc_simpleExpn()
{
	int flag = 0;
	printf("Inside proc_simpleExpn \n");
	if(proc_term() == 1)
	{
		if(proc_seprime() == 1 || proc_seprime() == 2)
		{
			flag = 1;
			return 1;
		}
	}
	if(flag  == 0)
		return -1;
}

int proc_eprime()
{
	int flag = 0;
	printf("Inside proc_eprime \n");
	if(proc_relop() == 1)
	{
		if(proc_simpleExpn() == 1)
	}
}
