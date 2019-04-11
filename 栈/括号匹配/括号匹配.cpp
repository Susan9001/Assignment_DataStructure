#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define INCREMENT 10

typedef int Status;
typedef char ElemType;
typedef struct SqStack {
	ElemType *top;
	ElemType *base;
	int stackSize;
}SqStack;

Status initStack(SqStack &s);
Status Push(SqStack &s, ElemType e);
Status Pop(SqStack &s, ElemType &e);
int Compare(ElemType inside, ElemType outside); //����ƥ�䷵��1�����򷵻�0
int Where( ElemType outside); //���ں����������1��ǰ�뷵��-1��˫����������0
Status Match(char*);

int main()
{
	char* bracket;
	printf("������һ�����Ű�~��");
	bracket = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
	fgets(bracket, STACK_INIT_SIZE - 1, stdin);
	Match(bracket);

	return 0;
}

Status initStack(SqStack &s)
{
	s.base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!s.base) return ERROR;
	s.stackSize = STACK_INIT_SIZE;
	s.top = s.base;
	return OK;
}

Status Push(SqStack &s, ElemType e)
{
	if (s.top - s.base >= s.stackSize)
	{
		s.base = (ElemType*)realloc(s.base, (s.stackSize + INCREMENT)* sizeof(ElemType));
		if (!s.base) return ERROR;
		s.stackSize += INCREMENT;
		s.top = s.base + s.stackSize;
	}
	*s.top = e;
	s.top++;
	return OK;
}

Status Pop(SqStack &s, ElemType &e)
{
	if (s.top == s.base) return ERROR;
	s.top--;
	e = *s.top;
	return OK;
}

int Compare(ElemType inside, ElemType outside)
{
	switch (inside)
	{
	case '"': case '\'':
		if (outside == inside) return 1;
		else return 0;
	case '(':
		if (outside == ')') return 1;
		else return 0;
	case '[': case '{':
		if (outside == inside + 2) return 1;
		else return 0;
	default:
		return -1; 
	}
}

int Where(ElemType outside)
{
	switch (outside)
	{
	case '\'': case '"':
		return 0;
	case '[': case '{': case '(':
		return -1;
	case ')': case ']': case '}':
		return 1;
	default:
		return -2;
	}
}

Status Match(char* bracket) //bracketΪ��������
{
	int i;
	char former;
	SqStack s;
	initStack(s);

	for (i = 0; i < STACK_INIT_SIZE && bracket[i] != '\0' && bracket[i] != '\n'; i++)
	{
		switch (Where(bracket[i]))
		{
		case -1: //������
			Push(s, bracket[i]);
			break;
		case 1: //������
			if (s.top == s.base) break;
			Pop(s, former); //former��ʾ(Ԥ�ڵ�)������
			if (Compare(former, bracket[i]) != 1)
			{
				printf("��ƥ��Ү~~\n");
				return 0;
			}
			break;
		case 0:
			if (s.top == s.base) break;
			if (Compare(*(s.top - 1), bracket[i]) == 1) //���������Ž�����
				Pop(s, former);
			else 
				Push(s, bracket[i]); //������ջ
			break;
		}
	}

	if(s.top > s.base  + 1)
	{
		printf("2��ƥ��Ү~~\n");
		return 0;
	}
	else
	{
		printf("ƥ�䣡\n");
		return 1;
	}
}
