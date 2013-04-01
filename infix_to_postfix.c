#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct st
{
  char data[20];
	struct st *pre, *next, *last;
};

typedef struct st stack;
void gotoxy(int x,int y)
{
printf("%c[%d;%df",0x1B,y,x);
}

void push(stack **s, char *c)
{
	stack *newNode;
	newNode = (stack *) malloc(sizeof(stack));
	strcpy(newNode->data, c);
	if(!(*s))
	{
		(*s) = newNode;
		(*s)->pre = 0; (*s)->next = 0; (*s)->last = newNode;
		return;
	}
	else
	{
		newNode->pre = (*s)->last;
		newNode->next = 0;
		(*s)->last->next = newNode;
		(*s)->last = newNode;
	}
}

char *pop(stack **s)
{	
	stack *tmpNode;
	if((*s) == NULL)
	{
		printf("\n STACK UNDERFLOW");
		return "";
	}
	else if((*s)->next == NULL && (*s)->last == (*s))
	{
		(*s) = NULL;
	}
	else
	{
		tmpNode = (*s)->last;
		(*s)->last->pre->next = NULL;
		(*s)->last = (*s)->last->pre;
		return tmpNode->data;
	}
}

char *peek(stack **s)
{	
	if((*s) == NULL)
	{
		printf("\n STACK UNDERFLOW");
		return "X";
	}
	else
	{
		return (*s)->last->data;
	}
}

int isEmpty(stack *s)
{
	if(s == NULL)
		return 1;
	else
		return 0;
}

void clearString(char *string)
{
	int i;
	for(i=strlen(string); i>=0; i--)
	{
		string[i] = '\0';
	}
	string[i] = '\0';
}

void printStack(stack **s)
{
	stack *cNode;
	if(!(*s))
	{
		printf(" STACK UNDERFLOW");
	}
	else
	{
		cNode = (*s);
		while(cNode!=0)
		{
			printf("%s ", cNode->data);
			cNode = cNode->next;
		}
	}
}

void parse(char *exp, stack **s)
{
	int i=0, digits=0;
	char num[20], sym[1];
	while(exp[i] != '\0')
	{
		if(exp[i] == '(' || exp[i] == ')' || exp[i] == '^' || exp[i] == '/' || exp[i] == '*' || exp[i] == '+' || exp[i] == '-')
		{
			if(digits>0)
			{
				push(&(*s), num);
				digits = 0;
				clearString(num);
			}
			sym[0] = exp[i];
			push(&(*s), sym);
			clearString(sym);
			
		}
		else if(exp[i] == ' ')
		{
			if(digits>0)
			{
				push(&(*s), num);
				digits = 0;
				clearString(num);
			}		}
		else if(isalnum(exp[i]))
		{
			num[digits++] = exp[i];
		}
		i++;
	}
	if(digits>0)
	{
		push(&(*s), num);
		digits = 0;
		clearString(num);
	}
}

int opPre(char *c)
{
	if(c[0] == '+' || c[0] == '-')
		return 1;
	else if(c[0] == '*' || c[0] == '/')
		return 2;
	else if(c[0] == '^')
		return 3;
	else if(c[0] == '(')
		return 4;
	else if(c[0] == ')')
		return 5;
	else if(c[0] == 'X')
		return 6;
	else
		return 0;

}

stack *convert(stack **infix)
{
	stack *s, *postfix;
	int i = 4;
	postfix = NULL;
	push(&s, "(");
	push(&(*infix), ")");
	stack *tmpNode;
	tmpNode = *infix;
	system("clear");
	printf("\n|-----|------------------------|---------------------------------------------------------------------------------|");
	printf("\n| I/P |         STACK          |                             POSTFIX EXPRESSION                                  |");
	printf("\n|-----|------------------------|---------------------------------------------------------------------------------|\n");
	while(!(isEmpty(s)) && tmpNode != NULL)
	{
		if(opPre(tmpNode->data) == 0)
		{
			push(&postfix, tmpNode->data);
		}
		else if(opPre(tmpNode->data) == 4)
		{
			push(&s, tmpNode->data);
		}
		else if(opPre(tmpNode->data) <= 3)
		{
			while(opPre(peek(&s))>=opPre(tmpNode->data) && opPre(peek(&s)) <=3)
			{
				push(&postfix, pop(&s));
			}
			push(&s, tmpNode->data);
		}
		else if(opPre(tmpNode->data) == 5)
		{
			while(opPre(peek(&s)) != 4)
			{

				push(&postfix, pop(&s));
			}
			pop(&s);
		}
		gotoxy(0, ++i);
		printf("|     |                        |                                                                                 |\n");
		gotoxy(4, i);
		printf("%s", tmpNode->data);
		gotoxy(9, i);
		printStack(&s);
		gotoxy(34, i);
		printStack(&postfix);
		//gotoxy(0, ++i);
		//printf("|-----|------------------------|---------------------------------------------------------------------------------|");
		tmpNode = tmpNode->next;

	}
	gotoxy(0, ++i);
	printf("|-----|------------------------|---------------------------------------------------------------------------------|");
	return postfix;
}

int main()
{
	stack *s, *postfix, *infix;
	int i, k=0;
	s = NULL; postfix = NULL; infix = NULL;
	char sinfix[100], tmpNo[20];
	printf("\nEnter Expression : "); fgets(sinfix, 100, stdin);
	sinfix[strlen(sinfix)-1] = '\0';
	/*
	while(1)
	{
		printf("Enter Expression Data (x to finish) : "); scanf("%s", sinfix);
		if(sinfix[0] != 'x' && sinfix[0] != 'X')
			push(&infix, sinfix);
		else
			break;
	}
	
	*/
	parse(sinfix, &infix);
	printf("\nINFIX INPUT : ");
	printStack(&infix);
	postfix = convert(&infix);
	printf("\nPOSTFIX : ");
	printStack(&postfix);
	printf("\n");
	
	return 0;
}
