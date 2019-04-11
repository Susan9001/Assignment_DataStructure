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
Status Read(sqStack s);
Status Reverse(sqStack &s);
Status turnDecimal(sqStack &s, int n, ElemType &result);
Status turnOct_Hex(sqStack &s, int n, ElemType &result);

int main()
{
	int result, n, choice;
	ElemType total;
	sqStack s;

	printf("1、任意进制转10进制  2、二进制转8进制  3、二进制转16进制\n");

	while (1)
	{
		initStack(s);

		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) 
		{
			printf("哎呦输错了哟，请重新输入：");
			while (getchar() != '\n');
		}

		switch (choice) {
		case 1:
			printf("请输入多少进制：");
			scanf("%d", &n);
			getchar();
			printf("请输入%d进制数: ", n);
			scanf("%d", &total);
			getEvery(s, total);
			turnDecimal(s, n, result);
			printf("结果为：%d\n", result);
			break;
		case 2: case 3:
			printf("请输入2进制数: ");
			scanf("%d", &total);
			getEvery(s, total);
			Reverse(s);
			if (choice == 2) 
				turnOct_Hex(s, 8, result);
			else 
				turnOct_Hex(s, 16, result);
			printf("结果为：%d\n", result);
			break;
		}
	}
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


Status Pop(sqStack &s, ElemType &e)
{
	if (s.base == s.top) 
	{
		e = 0;
		return OK;
	};
	s.top --;
	e = * s.top;
	
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

Status Reverse(sqStack &s)
{
	sqStack new_s;
	ElemType e;

	initStack(new_s);
	while (s.top != s.base)
	{
		Pop(s, e);
		Push(new_s, e);
	}
	s = new_s;
	return OK;
}

Status turnDecimal(sqStack &s, int n, ElemType &result)
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

Status turnOct_Hex(sqStack &s, int n, ElemType &result)
{
	if (n == 16) n = 4;
	else n = 3;

	result = 0;
	int i = 0, j = 0, len = s.top - s.base, e;

	for(j = 0; s.top != s.base; j++)
	{
		for (i = 0; i < n && s.top != s.base; i++)
		{
			Pop(s, e);
			result += e * pow(2, i) * pow(10, j);
		}
	}
	return OK;
}
