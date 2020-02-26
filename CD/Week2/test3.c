#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "PreProcessing/comments.h"
#include "PreProcessing/spaces.h"
#include "PreProcessing/preprocessor.h"
//#include "../Week3/symboltable.h"

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
elements* gabru = NULL;

char types[][20] = {"NOTHING","STRING-LITERAL" , "KEYWORD" , "IDENTIFIER" , "DIGIT-LITERAL", "LB", "RB","LC","RC","ASSIGNMENT-OPERATOR","RELATIONAL-OPERATOR","LOGICAL-OPERATOR","SPEICAL-SYMBOLS","LSB","RSB" ,"ERROR"};


#define SIZE 20

struct DataItem {
    char key [20];
   char type [20];
   char scope [20];
   char returnType[20];
   int size;
   int arguments;
   char arg[20];


};

struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(char* key) {

    return ((strlen(key)+key[0])%SIZE);
}

struct DataItem *search(char* key) {
   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {

      if(strcmp(hashArray[hashIndex]->key, key) == 0)
         return hashArray[hashIndex];

      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

void insert(char* key, char* type , char* scope, char* returnType,int size , int arguments,char* arg) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   strcpy(item->type, type);
   strcpy(item->scope,scope);
   strcpy(item->key , key);
   strcpy(item->returnType,returnType);
   strcpy(item->arg,arg);
   item->size = size;
   item->arguments = arguments;
   int hashIndex = hashCode(key);
   while(hashArray[hashIndex] != NULL && (strcmp(hashArray[hashIndex]->key," "))) {
      ++hashIndex;
      hashIndex %= SIZE;
   }
   hashArray[hashIndex] = item;
}

void displayHash() {
   int i = 0;
    printf("\n Printing the symbol table \n");
    printf("S.No \t Name \t Type \t  Scope \t ReturnType \t Size \t NumArg \t Arguments \n");
    int pos = 1;
   for(i = 0; i<SIZE; i++) {

      if(hashArray[i] != NULL)
         printf("%d \t %s \t %s \t %s \t %s \t\t  %d \t %d \t %s \n",pos++,hashArray[i]->key,hashArray[i]->type,hashArray[i]->scope,hashArray[i]->returnType,hashArray[i]->size,hashArray[i]->arguments,hashArray[i]->arg);
   }

   printf("\n");
}


void printSymbolTable(elements* head)
{
    char scope[20] = "G";
    int size = -1000;
    char strDatatype[20] = "";
    elements* cur = head;
    int count = 0;
    int arguments = 1;
    while(cur!= NULL)
    {
       // printf("%d \t count = %d \n",cur->to->type,count);
        if(cur->to->type == 3)
        {
            if(cur->previous->to->type == 2)
            {
            strcpy(strDatatype,cur->previous->to->lexemename);
            }
            if(cur->next->to->type != 5)
            {
                char d[20] = "NULL";
                if(cur->previous->to->type ==2 || strcmp(strDatatype," ") && strcmp(cur->previous->to->lexemename,"="))
                {
                    if(!strcmp(cur->previous->to->lexemename,"int"))
                    {
                        size = 4;
                    }
                    else if(!strcmp(cur->previous->to->lexemename,"char"))
                    {
                        size =1;
                    }
                  //  printf("Identifier = %s \t DataType = %s \t Scope = %c \n",cur->to->lexemename,strDatatype,scope);
                    insert(cur->to->lexemename,strDatatype,scope,"NULL",size,NULL,d);
                }
            }
            else if(cur->next->to->type == 5)
            {
                if(cur->previous->to->type == 2 && strcmp(cur->to->lexemename,"printf") && strcmp(cur->to->lexemename,"scanf"))
                {
                    char c[20] = "NULL";
                    strcpy(scope,cur->to->lexemename);
                    if(cur->next->next->to->type == 6 )
                    {
                        arguments = 0;

                    }
                    else if(cur->next->next->to->type == 2)
                    {
                        strcpy(c,cur->next->next->to->lexemename);
                        strcat(c," ");
                        strcat(c,cur->next->next->next->to->lexemename);
                    }

                //printf("Function = %s \t type = FUNC \t returnType = %s \t scope = %c \t arguments =%d \n",cur->to->lexemename,strDatatype,scope,arguments);
                insert(cur->to->lexemename,"FUNC","G ",strDatatype,-1,arguments,c);
                }
                else
                {
                    strcpy(strDatatype," ");
                }
            }
        }
        else if(!strcmp(cur->to->lexemename,";"))
        {
            strcpy(strDatatype," ");
        }
        else if((cur->to->type) == 7)
        {
            count++;
        }
        else if((cur->to->type == 8) )
        {
            count--;
            if(count == 0)
                strcpy(scope,"G ");
        }
        cur = cur->next;
    }
    displayHash();
}

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

tok* getNextToken()
{
    if(head == NULL)
    {
        printf("Hello\n");
        return NULL;
    }
    else
    {
        tok* re = (tok*)malloc(sizeof(tok));
        re = gabru->to;
        gabru = gabru->next;
        return re;


    }

}




void printToken(tok* t)
{
    printf("< %s %d %d ",t->lexemename,t->row,t->col);

    printf("%s >",types[t->type]);
    enterIntoList(t);
}

int helloEveryone()
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
        else if(ca == "#")
        {
            while(ca!='\n')
                ca = getc(fa);
            ca = getc(fa);
            line++;
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
                    while(ca != ' ' && isdigit(ca)!=0)
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
                        t->type = 15;
                    printToken(t);
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
                else if( ca == '}' || ca == '[' || ca==']')
                {
                    t->lexemename[pos++] = ca;
                    t->lexemename[pos] = '\0';
                    t->row = line;
                    t->col = column;
                    if(ca == '}')
                        t->type =  8;
                    else if(ca == '[')
                        t->type = 13;
                    else
                        t->type = 14;

                    printToken(t);
                    ca = getc(fa);
                    printf("\n Kaise ho");
                    if(ca == EOF)
                        printf(" EOF \n");
                    else
                        printf("NOT EOF \n");
                    printf("ca value: %d, ca: %c\n",ca, ca);
                }
                else
                {
                    t->lexemename[pos++] = ca;
                    ca = getc(fa);
                    while(ca!=' ')
                    {
                        if(isdigit(ca)!=0 || isalpha(ca)!= 0 || ca == '_' || ca == ')' || ca == '[' || ca == '{')
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
   // printf("Now printing the new list \n");
    printList();
  // printSymbolTable(head);
   gabru = head;
}





