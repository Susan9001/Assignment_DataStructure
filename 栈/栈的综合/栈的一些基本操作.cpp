#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define INCREMENT 10

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char ElemType;
typedef int Status;
typedef struct sqStack
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;

Status initStack(sqStack &s);
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
Status ReadStack(sqStack s);

int main()
{
	int choice;
	char e;
	char *lines = (char*)malloc(sizeof(char) * STACK_INIT_SIZE);
	char* ch_ptr;

	sqStack s;
	if (initStack(s))
		printf("��ʼ���ɹ���\n");

	printf("1.����һ���ַ�����ջ\t2.��ջ\n3.��ջ\t4.�鿴ջ������Ԫ��\t5.�˳�\n");
	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
		{
			printf("\n�����������Ү~~����������ѡ��");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //�����س�

		switch (choice)
		{
		case 1:
			printf("�������ַ�����");
			fgets(lines, STACK_INIT_SIZE, stdin);
			ch_ptr = &lines[0];
			while (*ch_ptr != '\n')
			{
				Push(s, *ch_ptr);
				ch_ptr++;
			}
			ReadStack(s);
			break;
		case 2:
			printf("�������ջ��Ԫ�أ�");
			scanf("%c", &e);
			if (Push(s, e))
				ReadStack(s);
			break;
		case 3:
			if (Pop(s, e))
			{
				printf("��\"%c\"Ԫ�س�ջ��\n", e);
				ReadStack(s);
			}
			break;
		case 4:
			ReadStack(s);
			break;
		case 5:
			return 0;
		}
	} //while true

	return 0;
}

Status initStack(sqStack &s)
{
	s.base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!s.base) return ERROR;
	s.top = s.base;
	s.stackSize = STACK_INIT_SIZE;

	return OK;
}

Status Push(sqStack &s, ElemType e)
{
	if (s.top - s.base >= s.stackSize)
	{
		s.base = (ElemType*)realloc(s.base, (s.stackSize + INCREMENT) *sizeof(ElemType));
		if (!s.base) return OVERFLOW;

		/*ע��˳��*/
		s.top = s.base + s.stackSize;
		s.stackSize += INCREMENT;
	}

	*(s.top) = e;
	s.top++;

	return OK;
}

Status Pop(sqStack &s, ElemType &e)
{
	if (s.top == s.base) return ERROR;
	s.top--;
	e = *(s.top);

	return OK;
}

Status ReadStack(sqStack s)
{
	if (!s.base) return ERROR;
	ElemType *p;
	for (p = s.base; p != s.top; p++)
		printf("%c", *p);
	putchar('\n');
	return OK;
}