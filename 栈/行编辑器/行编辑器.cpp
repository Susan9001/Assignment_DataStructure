#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INIT_SIZE 100
#define INCREMENT 10
#define LINE_MAX 50
#define EOF ';'

typedef int Status;
typedef char ElemType;
typedef struct sqStack
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

Status initStack(sqStack &s);
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
Status ClearStack(sqStack &s);
void LineEdit();

int main()
{
	LineEdit();

	return 0;
}

void LineEdit()
{
	sqStack s;
	initStack(s);

	printf("ÇëÊäÈë£º\n");
	ElemType ch = getchar(), temp;
	while (ch != EOF)
	{
		while (ch != EOF && ch != '\n')
		{
			switch (ch)
			{
			case '#':
				Pop(s, temp); break;
			case '@':
				ClearStack(s); break;
			default:
				Push(s, ch); break;
			}
			ch = getchar();
		}
		while (s.top != s.base)
		{
			s.top--;
			putchar(*s.top);
		}
		putchar('\n');
		//ClearStack(s);
		if (ch != EOF)
			ch = getchar();
	}
}

Status initStack(sqStack &s)
{
	s.base = (ElemType*)malloc(INIT_SIZE * sizeof(ElemType));
	if (!s.base) return ERROR;
	s.top = s.base;
	s.stackSize = INIT_SIZE;
	return OK;
}

Status Push(sqStack &s, ElemType e)
{
	if (s.top - s.base >= s.stackSize)
	{
		s.base = (ElemType*)realloc(s.base, sizeof(ElemType) * (INIT_SIZE + INCREMENT));
		if (!s.base) return ERROR;
		s.top = s.base + s.stackSize;
		s.stackSize += INCREMENT;
	}
	*s.top = e;
	s.top++;
	return OK;
}

Status Pop(sqStack &s, ElemType &e)
{
	if (s.top == s.base) return ERROR;
	s.top--;
	*s.top = e;
	return OK;
}

Status ClearStack(sqStack &s)
{
	s.top = s.base;
	return OK;
}


