#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INIT_SIZE 100
#define INCREMENT 10

typedef int Status;
typedef int ElemType;
typedef struct sqStack
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

Status initStack(sqStack &s);
Status getEvery(sqStack &s, ElemType total); //分解
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
Status turnDecimal(sqStack s, int n, ElemType &result);
Status Read(sqStack s);

int main()
{
	int result, n;
	ElemType total;
	sqStack s;

	initStack(s);

	printf("请输入多少进制：");
	scanf("%d", &n);
	getchar();
	printf("请输入%d进制数: ", n);
	scanf("%d", &total);
	getEvery(s, total);

	turnDecimal(s, n, result);
	printf("\n结果为：%d\n", result);

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
	while (s.top - s.base >= s.stackSize)
	{
		s.base = (ElemType*)realloc(s.base, (s.stackSize + INCREMENT));
		if (!s.base) return OVERFLOW;
		s.top = s.base + s.stackSize;
		s.stackSize += INCREMENT;
	}
	*(s.top) = e;
	s.top++;

	return OK;
}

Status getEvery(sqStack &s, ElemType total)
{
	int temp = total, count = 0, i;

	do {
		temp /= 10;
		count += 1;
	} while (temp);

	for (i = 0, temp = total; i < count; i++)
	{
		Push(s, temp % 10);
		temp /= 10;
	}

	return OK;
}

Status turnDecimal(sqStack s, int n, ElemType &result)
{
	result = 0;
	ElemType* target = s.base;
	int e, len = s.top - s.base;
	int count = (len - 1);

	while (count >= 0)
	{
		Pop(s, e);
		result += e * pow(n, count);
		count--;
	}

	return OK;
}

Status Pop(sqStack &s, ElemType &e)
{
	if (s.base == s.top) return OK;
	s.top--;
	e = *s.top;

	return OK;
}

Status Read(sqStack s)
{
	ElemType *target = s.top - 1;

	while (target != s.base)
	{
		printf("%x  %d\n", target, *target);
		target--;
	}
	printf("%x  %d\n", target, *target);
	return OK;
}