#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100 //最多可以放多少个元素
#define LIST_INCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;
typedef struct SqList
{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList &L);
Status MergeList_Sq(SqList La, SqList Lb, SqList &Lc);
Status InsertOrder(SqList &L, ElemType x);

int main()
{
	SqList La, Lb, Lc;
	ElemType Input, x;
	int i, choice;
	InitList_Sq(La);
	InitList_Sq(Lb);
	printf("初始化成功！\n");
	
	printf("\n1.输入两个顺序表\n2.合并两个顺序表\n3.按照顺序插一个数\n");
	while (1)
	{
		printf("\n请输入选择：");
		while (scanf("%d", &choice) != 1 || choice > 3 || choice < 1)
		{
			printf("输错了也~请重新输入：");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			i = 0;
			printf("请输入从小到大的第一个数组(0退出)：\n");
			do {
				scanf("%d", &Input);
				if (!Input) break;
				La.elem[i] = Input;
				i++;
			} while (i < LIST_INIT_SIZE);
			La.length = i;
			i = 0;
			printf("请输入从小到大的第二个数组(0退出)：\n");
			do {
				scanf("%d", &Input);
				if (!Input) break;
				Lb.elem[i] = Input;
				i++;
			} while (i < LIST_INIT_SIZE);
			Lb.length = i;
			break;

		case 2:
			if (MergeList_Sq(La, Lb, Lc) == 1)
			{
				printf("合并后：");
				for (i = 0; i < Lc.length; i++)
					printf("%d ", Lc.elem[i]);
				putchar('\n');
			}
			break;

		case 3:
			printf("请输入要插入的数字：");
			scanf("%d", &x);
			if (InsertOrder(La, x) && InsertOrder(Lb, x) == 1)
			{
				printf("插入后：");
				for (i = 0; i < La.length; i++)
					printf("%d ", La.elem[i]);
				putchar('\n');
				for (i = 0; i < Lb.length; i++)
					printf("%d ", Lb.elem[i]);
				putchar('\n');
			}
			break;
		}

	}

	return 0;
}

Status InitList_Sq(SqList &L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) return OVERFLOW;

	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status MergeList_Sq(SqList La, SqList Lb, SqList &Lc)
{
	int i = 0, j = 0, k = 0;
	//int shortt = La.length < Lb.length ? La.length: Lb.length;
	
	Lc.listsize = Lc.length = La.length + Lb.length;
	Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
	if (!Lc.elem) return OVERFLOW;
	
	while (i < La.length && j < Lb.length)
	{
		if (La.elem[i] < Lb.elem[j])
		{
			Lc.elem[k] = La.elem[i];
			i++;
		}
		else
		{
			Lc.elem[k] = Lb.elem[j];
			j++;
		}
		k++;
	}

	if (j == Lb.length)
	{
		while (i < La.length)
		{
			Lc.elem[k] = La.elem[i];
			i++;
			k++;
		}
	}
	else
	{
		while (j < Lb.length)
		{
			Lc.elem[k] = Lb.elem[j];
			j++;
			k++;
		}
	}
	return OK;
}

Status InsertOrder(SqList &L, ElemType x)
{
	int i, j;
	ElemType temp;

	if (L.length >= L.listsize) return OVERFLOW;

	for (i = 0; i < L.length - 1; i++)
		if (x >= L.elem[i] && x <= L.elem[i + 1]) break; 

	for (j = L.length - 1; j >= i + 1; j--)
		L.elem[j + 1] = L.elem[j];
	L.elem[i + 1] = x;
	L.length++;

	return OK;
}