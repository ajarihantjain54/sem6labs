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
						//printToken(lookahead);
					}

				}
			}
		}
	}
	if(flag == 0)
	{
		printf("\n Error Box Box \n");
		printToken(lookahead);
    }
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
		printToken(lookahead);
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
			lookahead = getNextToken();
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
        lookahead = getNextToken();
		proc_statementList();
	}
	else
	{
        printf("Returning NULL from statementList \n");
		return;
    }


}

int proc_statement()
{
	printf("Inside proc_statement \n");
	if(proc_assignStat() == 1)
	{
                lookahead = getNextToken();
                if(lookahead->type == 12 && !strcmp(lookahead->lexemename,";"))
					{
						return 1;
					}
                lookahead = ungetNextToken();

	}
    return -1;

}

int proc_dprime()
{
	printf("I am inside dprime \n");
	if(lookahead->type == 2 && !strcmp(lookahead->lexemename,"else"))
	{
		lookahead = getNextToken();
		if(lookahead->type == 5 )
		{
			lookahead = getNextToken();
			proc_statementList();
			if(lookahead->type == 12 && !strcmp(lookahead->lexemename,";"))
					{
						return 1;
					}
			lookahead = ungetNextToken();


		}
		lookahead = ungetNextToken();
	}
	else
	{
		printf("Returning epsilon from proc_dprime \n");
		return 1;
	}
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
			lookahead = getNextToken();
			int val = proc_expn();
			if( val == -1)
			lookahead = ungetNextToken();
			return val;

		}
	}
	if(flag == 0)
	{
        printf("Error inside proc_assignStat \n");
		return -1;
	}
}

int proc_expn()
{
	printf("Inside proc_expn \n");
	if(proc_simpleExpn() == 1)
	{
        lookahead = getNextToken();
        int val = proc_eprime();
        printf("I am alive \n");
        if(val == -1)
        lookahead = ungetNextToken();
        else if(val == 2)
            {
            printf("Token = %s ",lookahead->lexemename);
            lookahead = ungetNextToken();
            val = 1;
            }
            return val;


    }
    printf("Error inside proc_expn \n");
    return -1;


}


int proc_eprime()
{
	printf("Inside proc_eprime \n");
	if(proc_relop() == 1)
	{
        lookahead = getNextToken();
		if(proc_simpleExpn() == 1)
		{
            return 1;
		}
		lookahead = ungetNextToken();

	}
	printf("Returning epsilon from proc_eprime \n");
	printf("Token = %s \n",lookahead->lexemename);
	return 2;
}


int proc_simpleExpn()
{
	int flag = 0;
	printf("Inside proc_simpleExpn \n");
	if(proc_term() == 1)
	{
        lookahead = getNextToken();
		int val = proc_seprime();
		if(val == -1)
            lookahead = ungetNextToken();

		if(val == 2)
		{
            lookahead = ungetNextToken();
            val = 1;
		}
		return val;
	}
	if(flag  == 0)
	{
        printf("Error inside proc_simpleExpn\n");
		return -1;
    }
}


int proc_seprime()
{
	if(proc_addop() == 1)
	{
        lookahead = getNextToken();
		if(proc_term() == 1)
		{
			lookahead = getNextToken();
            int val = proc_seprime();
            if(val == -1)
                lookahead = ungetNextToken();
            if(val == 2)
                {
                    lookahead = ungetNextToken();
                    val = 1;
                }
            return val;
		}
		lookahead = ungetNextToken();
	}
    printf("Returning epsilon from proc_seprime \n");
    return 2;
}



int proc_term()
{
	int flag = 0;
	printf("Inside proc_term \n");
	if(proc_factor() == 1)
	{
        lookahead = getNextToken();
        int val = proc_tprime();
        if(val == -1 || val == 2)
            lookahead = ungetNextToken();
        return 1;
	}
	else
	{
        printf("Error inside proc_term \n");
		return -1;
	}
}



int proc_tprime()
{
	int flag = 0;
	printf("Inside proc_tprime \n");
	if(proc_mulop() == 1)
	{
        lookahead = getNextToken();
		if(proc_factor() == 1)
		{
			flag = 1;
			lookahead = getNextToken();
			int val = proc_tprime();
			if(val == -1)
                lookahead = ungetNextToken();
            if(val == 2)
            {
                lookahead = ungetNextToken();
                val = 1;
            }
            return val;
		}
		lookahead = ungetNextToken();
	}
	printf("Returning epsilon from proc_tprime \n");
	return 2;
}


int proc_mulop()
{
	printf("Inside proc_mulop \n");
	if(lookahead->type == 9 && (!strcmp(lookahead->lexemename,"/") || !strcmp(lookahead->lexemename ,"*") || !strcmp(lookahead->lexemename,"%") ))
	{
		return 1;
	}
	else
	{
        printf("Error inside proc_mulop \n");
		return -1;
    }
}

int proc_addop()
{
	printf("Inside proc_addop \n");
	if(lookahead->type == 9 && (!strcmp(lookahead->lexemename,"+")|| !strcmp(lookahead->lexemename,"-")))
	{
		return 1;
	}
	else
	{
        printf("Error inside proc_addop \n");
		return -1;
	}
}

int proc_relop()
{
	printf("Inside proc_relop \n");
	if(lookahead->type == 10)
	{
		return 1;
	}
	else
	{
        printf("Error inside proc_relop \n");
		return -1;
    }
}

int proc_factor()
{
	printf("Inside proc_factor \n");
	if(lookahead->type == 3 || lookahead->type == 4)
		return 1;
	else
	{
        printf("Error inside proc_factor\n");
		return -1;
    }
}

int main()
{
    helloEveryone();
    printf("I am alive\n");
    proc_program();
}


