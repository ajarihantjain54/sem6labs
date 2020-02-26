#include<stdio.h>
#include<ctype.h>
#include "test3.c"
#include<string.h>

struct token* lookahead;

int i = 0;

void proc_identifierList();
void proc_statementList();
void proc_program()
{
	int flag = 0;
	lookahead = getNextToken();
	if( lookahead->type == 3 && (!strcmp(lookahead->lexemename,"main")))
	{
        printf("%s \n",lookahead->lexemename);
		lookahead = getNextToken();
		if(lookahead->type == 5)
		{
		 printf("%s \n",lookahead->lexemename);
			lookahead = getNextToken();
			if(lookahead->type == 6)
			{
			 printf("%s \n",lookahead->lexemename);
				lookahead = getNextToken();
				if(lookahead->type == 7)
				{
				 printf("%s \n",lookahead->lexemename);
                    lookahead = getNextToken();
					proc_declarations();
					proc_statementList();
					if(lookahead->type == 8)
					{
					 printf("%s \n",lookahead->lexemename);
						flag = 1;
						printf("The string has been accepted \n");
					}

				}
			}
		}
	}
	if(flag == 0)
		printf("\n Error Box Box \n");
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
    printf("%s %d\n",lookahead->lexemename,lookahead->type);
	printf("Inside proc_declarations \n");
	int flag = 0;
	if(lookahead->type == 2)
	{
        char* str = lookahead->lexemename;
        if(!strcmp(str,"int")||!strcmp(str,"double")||!strcmp(str,"float")
            || !strcmp(str,"long") || !strcmp(str,"short"))
		{
            printf("%s %d\n",lookahead->lexemename,lookahead->type);
            lookahead = getNextToken();
            proc_identifierList();
			if(lookahead->type == 12 && !strcmp(lookahead->lexemename,";"))
			{
                printf("%s %d\n",lookahead->lexemename,lookahead->type);
				flag = 1;
				lookahead= getNextToken();
				proc_declarations();
				printf("I am back \n");
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
	if(lookahead->type == 3)
	{
	 printf("%s %d\n",lookahead->lexemename,lookahead->type);
		lookahead = getNextToken();
		if(lookahead->type == 12 && !strcmp(lookahead->lexemename,","))
		{
             printf("%s %d\n",lookahead->lexemename,lookahead->type);
			flag = 1;
			proc_identifierList();

		}
		else if(lookahead->type == 13)
		{
			lookahead = getNextToken();
			if(lookahead->type == 4)
			{
				lookahead = getNextToken();
				if(lookahead->type == 14)
				{
					flag = 1;
					lookahead = getNextToken();
					if(lookahead->type == 12 && !strcmp(lookahead->lexemename,","))
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
	if(lookahead->type == 3)
	{
		lookahead = getNextToken();
		if(	lookahead->type == 12 && !strcmp(lookahead->lexemename,"="))
		{
			flag = 1;
			return 1;
			//return proc_expn();
		}
	}
	if(flag == 0)
	{
		return -1;
	}
}


int main()
{
    helloEveryone();
    printf("I am alive\n");
    proc_program();
}


