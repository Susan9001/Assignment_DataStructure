#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define OK 1
#define ERROR 0

typedef int Status;
typedef double ElemType;
typedef struct Complex
{
	ElemType a;
	ElemType b;
}Complex;

Status PutIn(Complex &complex, ElemType v1, ElemType v2);
Status Add(Complex &complex1, Complex &complex2, Complex &complex3);
Status Sub(Complex &complex1, Complex &complex2, Complex &complex3);
Status Mul(Complex &complex1, Complex &complex2, Complex &complex3);
Status Div(Complex &complex1, Complex &complex2, Complex &complex3);

int main()
{
	ElemType v1, v2;
	Complex complex1, complex2, complex3;
	int choice;

	printf("1�����븴��\n");
	printf("2���ӷ� 3������\n");
	printf("4���˷� 5������\n");

	while (1)
	{
		printf("\n������ѡ�");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
		{
			printf("���������Ү�����������룺");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			printf("�������һ������(a+bi)��");
			scanf("%lf+%lfi", &v1, &v2);
			PutIn(complex1, v1, v2);
			printf("������ڶ�������(a+bi)��");
			scanf("%lf+%lfi", &v1, &v2);
			PutIn(complex2, v1, v2);
			break;
		case 2:
			if(Add(complex1, complex2, complex3))
				printf("��Ϊ��%.1lf+%.1lfi\n",complex3.a, complex3.b );
			break;
		case 3:
			if(Sub(complex1, complex2, complex3))
				printf("��Ϊ��%.1lf+%.1lfi\n", complex3.a, complex3.b);
			break;
		case 4:
			if (Mul(complex1, complex2, complex3))
				printf("��Ϊ��%.1lf+%.1lfi\n", complex3.a, complex3.b);
			break;
		case 5:
			if (Div(complex1, complex2, complex3))
				printf("��Ϊ��%.2lf+%.2lfi\n", complex3.a, complex3.b);
			else
				printf("��������Ϊ0Ŷ~~\n");
			break;
		}
	}

	return 0;
}

Status PutIn(Complex &complex, ElemType v1, ElemType v2)
{
	complex.a = v1;
	complex.b = v2;
	return OK;
}

Status Add(Complex &complex1, Complex &complex2, Complex &complex3)
{
	complex3.a = complex1.a + complex2.a;
	complex3.b = complex1.b + complex2.b;
	return OK;
}

Status Sub(Complex &complex1, Complex &complex2, Complex &complex3)
{
	complex3.a = complex1.a - complex2.a;
	complex3.b = complex1.b - complex2.b;
	return OK;
}

Status Mul(Complex &complex1, Complex &complex2, Complex &complex3)
{
	complex3.a = complex1.a * complex2.a - complex1.b * complex2.b;
	complex3.b = complex1.b * complex2.a + complex1.a * complex2.b;
	return OK;
}

Status Div(Complex &complex1, Complex &complex2, Complex &complex3)
{
	if (complex2.a == 0 && complex2.b == 0)
		return ERROR;
	complex3.a = (complex1.a * complex2.a + complex1.b * complex2.b) / (pow(complex2.a, 2) + pow(complex2.b, 2));
	complex3.b = (complex1.b * complex2.a - complex1.a * complex2.b) / (pow(complex2.a, 2) + pow(complex2.b, 2));
	return OK;
}