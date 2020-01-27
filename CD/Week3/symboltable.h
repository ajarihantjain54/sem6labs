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


void printSymbolTable(elements* head)
{
	elements* cur = head;
	while(cur!= NULL)
	{
		if(cur->)
	}
}