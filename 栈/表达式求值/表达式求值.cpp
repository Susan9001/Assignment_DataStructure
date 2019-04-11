#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INIT_SIZE 100
#define INCREMENT 10
#define OP_NUM 7 //运算符一共7种

typedef int Status;
typedef int ElemType;
typedef struct sqStack
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

Status initStack(sqStack &s);
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
ElemType GetTop(sqStack s);
Status In(char c);
char Procede(char Inside, char c);
int Operate(int a, char theta, int b);
int EvaluateExpression();

int main()
{
	printf("请输入算术表达式(每输入完一次回车一次，最后#号结束)：\n");
	int result;
	result = EvaluateExpression();
	printf("结果为：%d\n", result);

	return 0;
}

Status initStack(sqStack &s)
{
	s.base = (ElemType*)malloc(sizeof(ElemType));
	if (!s.base) return OVERFLOW;
	s.top = s.base;
	s.stackSize = INIT_SIZE;
	return OK;
}

Status Push(sqStack &s, ElemType e)
{
	if (s.top - s.base >= s.stackSize)
	{
		s.base = (ElemType*)realloc(s.base, INCREMENT + INIT_SIZE);
		s.stackSize += INCREMENT;
		s.top = s.base ;
	}
	*s.top = e;
	s.top++;
	return OK;
}

Status Pop(sqStack &s, ElemType &e)
{
	if (s.top == s.base) return ERROR;
	e = *(s.top - 1);
	s.top--;
	return OK;
}

ElemType GetTop(sqStack s)
{
	ElemType e;
	if (s.top == s.base) return ERROR;
	e = *(s.top - 1);
	return e;
}

Status In(char c)
{
	int i;
	char OP[OP_NUM] = { '+', '-', '*', '/', '(', ')', '#' };
	for (i = 0; i < OP_NUM; i++)
		if (c == OP[i]) break;
	if (i == OP_NUM) return 0;
	else return 1;
}

char Procede(char c1, char c2)
{
	switch (c1) 
	{
	case '+':case '-':
		switch (c2)
		{
		case '+': case'-': case ')':case '#':
			return '>';
		case '*': case'/': case '(':
			return '<';
		}
		break;

	case '*': case '/':
		switch (c2)
		{
		case '+': case'-': case ')':case '#': case '*': case'/':
			return '>';
		case '(':
			return '<';
		}
		break;

	case '(': 
		switch (c2)
		{
		case '+': case'-': case '(': case '*': case'/':
			return '<';
		case ')':
			return '=';
		}
		break;

	case ')':
		switch (c2)
		{
		case '+': case'-': case ')':case '#': case '*': case'/':
			return '>';
		}
		break;

	case '#':
		switch (c2)
		{
		case '+': case'-': case '(': case '*': case'/':
			return '<';
		case '#':
			return '=';
		}
		break;
	}

	printf("输入有问题耶~~\n");
	return ERROR;
}

int Operate(int a, char theta, int b)
{
	switch (theta)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		printf("有问题！\n");
		return ERROR;
	}
}

int EvaluateExpression()
{
	sqStack OPTR, OPND;
	char c;
	int elemC, a, b, temp = 0;

	initStack(OPND); //放数字
	initStack(OPTR); //放符号，越上面优先级越高

	Push(OPTR, '#');
	c = getchar();
	//getchar();
	while (c != '#'|| GetTop(OPTR) != '#') 
	{
		if (!In(c)) 
		{
			elemC = c - 48;
			Push(OPND, elemC);
			c = getchar();	
			//getchar();
		}
		else 
		{
			switch (Procede(GetTop(OPTR), c))
			{
			case '<': //输入的优先级更高
				Push(OPTR, c);
				c = getchar();
				//getchar();
				break;
			case '=': //消括号
				Pop(OPTR,temp);
				c = getchar();
				//getchar();
				putchar(c);
				break;
			case '>': //栈头的优先级更高
				Pop(OPND, b);
				Pop(OPND, a);
				Pop(OPTR, temp);
				Push(OPND, Operate(a, (char)temp, b));
				//printf("结果：%d\n", Operate(a, (char)temp, b));
				break;
			}
			//printf("符号Top = %c\n", GetTop(OPTR));
		} //else
	} //while

	return GetTop(OPND);
}
