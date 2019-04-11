#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef double ElemType;

typedef struct BIGTOSMALL
{
	ElemType big;
	ElemType middle;
	ElemType small;
}BIGTOSMALL;
typedef struct BIGTOSMALL *OutPut;

typedef enum Sex
{
	Male, Female
}Sex;
typedef enum Scools
{
	A, B, C, D, E
};
typedef struct Competition
{
	char events[30];
	Sex sex;
	Scools schools;
	double result;
	double scores;
}Competition;
typedef struct Total
{
	double FemaleT;
	double MaleT;
	double BothT;
};

Status XYZ(ElemType X, ElemType Y, ElemType Z, OutPut &output );
Status Compete(Competition competitions[50], Total totals[5]);

int main()
{
	OutPut output;
	ElemType a, b, c;
	printf("请输入三个数来排序(a-b-c): ");
	scanf("%lf-%lf-%lf", &a, &b, &c);
	if(XYZ(a, b, c, output))
		printf("排序后：%.1lf, %.1lf, %.1lf\n", output->big, output->middle, output->small);

	/*int x = 91, y = 100, count = 0;
	int i = 1, k = 0, n = 10;
	while (i <= n - 1)
	{
		k += 10 * i;
		i++;
	}
	printf("%d\n", i - 1);

	i = 1; k = 0;
	do 
	{
		k += 10 * i;
		i++;
	} while (i <= n - 1);
	printf("%d\n", i - 1);

	i = 1; k = 0;
	while (i <= n - 1)
	{
		i++;
		k += 10 * i;
	}
	printf("%d\n", i - 1);

	while (y > 0)
	{
		if (x > 100)
		{
			x -= 10;
			y--;
			count++;
		}
		else x++;
	}
	printf("%d\n", count);*/

	return 0;
}

Status XYZ(ElemType X, ElemType Y, ElemType Z, OutPut &output)
{
	ElemType temp;

	output = (OutPut)malloc(sizeof(BIGTOSMALL));

	temp = (X >= Y) ? X : Y;//XY里面最大的
	output->big = (temp >= Z) ? temp : Z;
	if (output->big == Z)
	{
		output->middle = temp;
		output->small = (X >= Y) ? Y : X;
		return 1;
	}
	else if(output->big == X)
	{
		output->middle = (Y >= Z) ? Y : Z;
		output->small = (Y >= Z) ? Z : Y;
		return 1;
	}
	else
	{
		output->middle = (X >= Z) ? X : Z;
		output->small = (X > Z) ? Z : X;
		return 1;
	}
}

Status Compete(Competition competitions[50], Total totals[5])
{
	int i = 0;
	while (competitions[i].scores != 0)
	{



		i++;
	}

}
