#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "PreProcessing/comments.h"
#include "PreProcessing/spaces.h"
#include "PreProcessing/preprocessor.h"


#define TableLength 30
int ind = 0;
struct token
{
	char* lexemename;
	unsigned int row,col;
	unsigned int type;
};

typedef struct token tok;

struct ListElement
{
    tok* to;
    struct ListElement* next;
    struct ListElement* previous;
};

typedef struct ListElement elements;


elements* head = NULL;


void Display()
{
    printf("Printing the symbol table");
}

//char** ARO = {"+","-","%","*","%","++"};
// char** RO = {"==","!=",">","<",">=","<="};
// char** LO = {"&&","||","!"};
// char** ASO = {"=","+=","-=","*=","/=","%="};
// char** BO = {"&","|","^","~","<<",">>"};

void preProcessing(FILE *fa , FILE *fb)
{
	removeSpaces(fa , fb);
	fclose(fa);
	fclose(fb);
	fa = fopen("./Outputs/q1rs.c","r");
	fb = fopen("./Outputs/q1rc.c","w");
	removeComments(fa , fb);
	fclose(fa);
	fclose(fb);
	fa = fopen("./Outputs/q1rc.c","r");
	fb = fopen("./Outputs/q1rp.c","w");
	removePreprocessor(fa , fb);
	fclose(fa);
	fclose(fb);
}
int isOther(char* str)
{
    if(!strcmp(str, "+") || !strcmp(str, "-")
        || !strcmp(str, "%") || !strcmp(str, "*")
        ||!strcmp(str, "%") || !strcmp(str, "++"))
    {
        return 9;
    }
    else if(!strcmp(str, "==") || !strcmp(str, "!=")
        || !strcmp(str, ">") || !strcmp(str, "<")
        ||!strcmp(str, ">=") || !strcmp(str, "<="))
        {
            return 10;
        }
    else if(!strcmp(str, "&&") || !strcmp(str, "||")
        || !strcmp(str, "!"))
        {
            return 11;
        }
    return 12;
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
    return 0 ;
}

int isDigitLiteral(char* str)
{
    int pos = 0;
    while(str[pos] != '\0')
    {
        if(isdigit(str[pos++])==0)
            return 0;
    }
    return 1;
}

int isIdentifier(char* str)
{
    int pos =1;
    while(str[pos] != '\0')
    {
        char b = str[pos++];
        if(isdigit(b)!=0 || isalpha(b)!= 0 || b == '_' )
        {
            continue;
        }
        else
        return 0;
    }
    return 1;
}


void enterIntoList(tok* t)
{
    elements* e = (elements*)malloc(sizeof(elements));
    e->to = t;
    e->next = NULL;
    e->previous = NULL;
    elements* prev = head;
    if(prev != NULL)
    {
        while(prev->next !=NULL)
        {
            prev = prev->next;
        }
        prev->next = e;
        e->previous = prev;
    }
    else
    head = e;

}

void printList()
{
    if(head == NULL)
    {
        printf("Hello\n");
    }
    else
        printf("Bye");
    elements* cur = head;
    while(cur != NULL)
    {
        printf("Token = %s \n",cur->to->lexemename);
        cur = cur->next;

    }
}
void printToken(tok* t)
{
    printf("< %s %d %d ",t->lexemename,t->row,t->col);
    char types[][20] = {"NOTHING","STRING-LITERAL" , "KEYWORD" , "IDENTIFIER" , "DIGIT-LITERAL", "LB", "RB","LC","RC","ASSIGNMENT-OPERATOR","RELATIONAL-OPERATOR","LOGICAL-OPERATOR","SPEICAL-SYMBOLS"};
    printf("%s >",types[t->type]);
    enterIntoList(t);
}

int main()
{
	FILE *fa , *fb;
	fa = fopen("q1in.c","r");
	fb = fopen("./Outputs/q1rs.c","w");
	preProcessing(fa,fb);
	fa = fopen("./Outputs/q1rp.c","r");
	fb = fopen("./Outputs/q1final.c","w");
	int ca , cb;
	ca = getc(fa);
	int line = 0;
	int column = 0;
	while(ca != EOF)
	{

		//printf("%c \n",ca);
        if(ca == '\n')
        {
            line++;
            column = 0;
            ca = getc(fa);
            printf("\n");
            ind++;
        }
        else if(ca == ' ')
        {
            column++;
            ca = getc(fa);
        }
        else
        {
                int sudoColumn = 0;
                tok* t = (tok*)malloc(sizeof(tok));
                int pos = 0;
                t->lexemename = (char*)malloc(sizeof(char)*30);
                if(ca == '"')
                {
                    ca = getc(fa);
                    sudoColumn++;
                    while(ca != '"')
                    {
                      t->lexemename[pos++] = ca;
                      ca = getc(fa);
                      sudoColumn++;
                    }
                    t->col = column;
                    t->row = line;
                    t->type = 1;
                    ca = getc(fa);
                    sudoColumn++;
                    t->lexemename[pos] = '\0';
                    printToken(t);
                }


                else if((isalpha(ca)!=0) || ca=='_')
                {
                    t->lexemename[pos++] = ca;
                    ca = getc(fa);
                    sudoColumn++;
                    while(ca !=' ')
                    {
                        if(isdigit(ca)==0 && isalpha(ca)== 0 && ca != '_')
                        {
                            //printf("\n Operator Detected \n");
                            break;
                        }
                        else if(ca == '\n')
                            break;
                        t->lexemename[pos++] = ca;
                        ca = getc(fa);
                        sudoColumn++;
                    }
                    t->col = column;
                    t->row = line;
                    t->lexemename[pos] = '\0';
                    if(isKeyword(t->lexemename))
                    {
                        t->type = 2;
                    }
                    else
                    {
                        if(isIdentifier(t->lexemename))
                        {
                            t->type = 3;
                        }
                        else
                            t->type = 20;
                    }
                    printToken(t);

                }

                else if(isdigit(ca)!=0)
                {
                    t->lexemename[pos++] = ca;
                    ca = getc(fa);
                    sudoColumn++;
                    while(ca != ' ')
                    {
                        if(ca == '\n')
                            break;
                        t->lexemename[pos++] = ca;
                        ca = getc(fa);
                        sudoColumn++;
                    }
                    t->col = column;
                    t->row = line;
                    t->lexemename[pos] = '\0';
                    if(isDigitLiteral(t->lexemename))
                        t->type = 4;
                    else
                        t->type = 20;
                }
                else if( ca == '(')
                {
                    t->lexemename[pos++] = ca;
                    t->lexemename[pos] = '\0';
                    t->row = line;
                    t->col = column;
                    t->type =  5;
                    printToken(t);
                    ca = getc(fa);
                        sudoColumn++;
                }
                 else if( ca == ')')
                {
                    t->lexemename[pos++] = ca;
                    t->lexemename[pos] = '\0';
                    t->row = line;
                    t->col = column;
                    t->type =  6;
                    printToken(t);
                    ca = getc(fa);
                        sudoColumn++;
                }
                else if( ca == '{')
                {
                    t->lexemename[pos++] = ca;
                    t->lexemename[pos] = '\0';
                    t->row = line;
                    t->col = column;
                    t->type =  7;
                    printToken(t);
                    ca = getc(fa);
                        sudoColumn++;
                }
                else if( ca == '}')
                {
                    t->lexemename[pos++] = ca;
                    t->lexemename[pos] = '\0';
                    t->row = line;
                    t->col = column;
                    t->type =  8;
                    printToken(t);
                    ca = getc(fa);
                        sudoColumn++;
                }
                else
                {
                    t->lexemename[pos++] = ca;
                    ca = getc(fa);
                    while(ca!=' ')
                    {
                        if(isdigit(ca)!=0 || isalpha(ca)!= 0 || ca == '_')
                            break;
                        if(ca == '\n')
                            break;
                        t->lexemename[pos++] = ca;
                        ca = getc(fa);
                        sudoColumn++;
                    }
                    t->col = column;
                    t->row = line;
                    t->lexemename[pos] = '\0';
                    t->type = isOther(t->lexemename);
                    printToken(t);

                }


                column += sudoColumn;
        }
    }
    printf("Now printing the new list \n");
    printList();
    printSymbolTable(head);
}



