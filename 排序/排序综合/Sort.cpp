#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Sort.h"

Status CreateSqList(SqList &L)
{
	int choice, i, j;

	printf("1、自动生成  2、手动输入\n");
	printf("请选择(选项-不长于20的长度)：");
	while (scanf("%d-%d", &choice, &L.lenght) != 2 || choice < 1 || choice > 2 || L.lenght > SQMAXSIZE)
	{
		printf("有错误耶~请重新输入：");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
	switch (choice)
	{
	case 1:
		srand(time(NULL));
		for (i = 1; i <= L.lenght; i++)
			L.r[i].key = 1 + rand() % 100;
		    //其他信息此处暂时忽略
		break;
	case 2:
		printf("请分别输入关键字：");
		for (i = 1; i <= L.lenght; i++)
			scanf("%d", &L.r[i].key);
		while (getchar() != '\n');
		break;
	}

	return OK;
}

void ReadSqList(SqList L)
{
	printf("（长度%d）", L.lenght);
	for (int i = 1; i <= L.lenght; i++)
		printf("%-4d", L.r[i].key);
	putchar('\n');
}

void InsertSort(SqList &L)
{
	int i, j;

	for (i = 2; i <= L.lenght; i++)
	{
		if (LT(L.r[i].key, L.r[i - 1].key))
		{
			L.r[0] = L.r[i];
			L.r[i] = L.r[i - 1];
			//其他信息暂时忽略
			for (j = i - 2; j > 0 && L.r[j].key > L.r[0].key; j--)
				L.r[j + 1] = L.r[j];
			L.r[j + 1] = L.r[0];
		}
	}
}

void BInsertSort(SqList &L)
{
	int i, j;
	int high, low, mid;

	for (i = 1; i <= L.lenght; i++) //这个等于很容易忘！
	{
		L.r[0] = L.r[i];
		low = 1;
		high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (LT(L.r[0].key, L.r[mid].key)) //target小，放左区
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i - 1; j > high; j--) //target恰好比low大，比low后一个小
			L.r[j + 1] = L.r[j]; //以low为判断标准，会忽律掉第一个的
		L.r[high + 1] = L.r[0];
	}
}

void TWInsertSort(SqList &L)
{
	int i, j;
	int first = 1, last = 1;
	RedType d[SQMAXSIZE + 1];
	
	d[1] = L.r[1]; //初始化key
	for (i = 2; i <= L.lenght; i++) //小于等于！
	{
		if (LT(L.r[1].key, L.r[i].key))
		{
			for (j = last; LT(L.r[i].key, d[j].key); j--)
				d[j + 1] = d[j];
			d[j + 1] = L.r[i];
			last++;
		}
		else 
		{
			/*不方便first的初始化*/
			if (first == last) 
			{
				first = L.lenght;
				d[first] = L.r[i];
				continue;
			}
			for (j = first; !LT(L.r[i].key, d[j].key); j++) //之前搞反了！
				d[j - 1] = d[j];
			d[j - 1] = L.r[i];
			first--;
		}

	}

	printf("\nfirst = %d, final = %d\n", first, last);
	for (i = 1; i <= L.lenght; i++)
	{
		j = (i - first + L.lenght) % L.lenght + 1; //并不是从0开始的，所以要+1
		L.r[j] = d[i];//j为逻辑上的位置（相对于非first）
	}
}

void SLInsertSort(SqList &L)
{
	SLinkListType SL;
	int i, j;

	CreateSLinkList(L, SL);
	printf("原来：\n");
	ReadSLinkListType(SL);

	for (i = 2; i <= SL.length; i++)
	{  //找到比[i]恰小的。j != 0? 从0还是0->next开始？
		for (j = 0; LT(SL.r[SL.r[j].next].rd.key, SL.r[i].rd.key); j = SL.r[j].next);
		SL.r[i].next = SL.r[j].next;
		SL.r[j].next = i;
	}
	printf("排序后：\n");
	ReadSLinkListType(SL);
	Arrange(SL);
	printf("整理后：\n");
	ReadSLinkListType(SL);
	for (i = 1; i < SL.length; i++)
		L.r[i] = SL.r[i].rd;
}

void Arrange(SLinkListType &SL)
{
	int p = SL.r[0].next, q;
	int i;

	for (i = 1; i < SL.length; i++)
	{
		while (p < i) p = SL.r[p].next; //总觉得这个是非必要的
		q = SL.r[p].next;
		if (p != i)
		{
			SLNode temp = SL.r[p];
			SL.r[p] = SL.r[i];
			SL.r[i] = temp;
			SL.r[i].next = p; //记录被移走的记录
		}
		p = q;
	}
}

void CreateSLinkList(SqList &L, SLinkListType &SL)
{
	int i;

	SL.length = L.lenght;
	SL.r[0].rd.key = MAXINT;
	SL.r[0].next = 1;
	for (i = 1; i <= L.lenght; i++)
	{
		SL.r[i].rd = L.r[i];
		SL.r[i].next = MAXINT;
	}
	SL.r[1].next = 0;
}

void ReadSLinkListType(SLinkListType SL)
{
	int i;
	for (i = 0; i <= SL.length; i++) printf("%-5d", i);
	printf("\n%-5c", '#');
	for (i = 1; i <= SL.length; i++) printf("%-5d", SL.r[i].rd.key);
	putchar('\n');
	for (i = 0; i <= SL.length; i++) printf("%-5d", SL.r[i].next == MAXINT ? '#' : SL.r[i].next);
	putchar('\n');
}

void BubbleSort(SqList &L)
{
	int i, j, flag = 1;

	for (i = 1; i <= L.lenght && flag == 1; i++)
	{
		flag = 0;
		for (j =1 ; j <= (L.lenght - i + 1); j++)
		{
			if (!LT(L.r[j - 1].key, L.r[j].key))
			{
				swap(L.r[j - 1], L.r[j]);
				flag = 1;
			}
		}
	}
}

void BBubleSort(SqList &L)
{
	int low, high, flag = 1; //每次的头尾指针，还有表示是否有交换的flag
	int i, j; //i从头low开始，j从尾high开始

	for (low = 1, high = L.lenght; low < high; low++, high--)
	{
		for (i = low, j = high, flag = 0; i + 1 <= high && j - 1 >= low; i++, j--)
		{
			if (!LQ(L.r[i].key, L.r[i + 1].key))
			{
				flag = 1;
				swap(L.r[i], L.r[i + 1]);
			}
			if (!LQ(L.r[j - 1].key, L.r[j].key))
			{
				flag = 1;
				swap(L.r[j - 1], L.r[j]);
			}
		}
		ReadSqList(L);
	}
}

void QuickSort(SqList &L)
{
	//QSort(L, 1, L.lenght);
	Partition(L, 1, L.lenght);
}

int Partition(SqList &L, int low, int high)
{
	int pivotkey = L.r[low].key;
	int old_low = low, old_high = high;
	L.r[0] = L.r[low];

	while (low < high)
	{
		while (low < high && LQ(pivotkey, L.r[high].key))high--;
		L.r[low] = L.r[high];
		while (low < high && LQ(L.r[low].key, pivotkey)) low++;
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];

	if(old_low < low - 1)
		Partition(L, old_low, low - 1); //现在的low成为pivot了
	if(low + 1 < old_high)
		Partition(L, low + 1, old_high);
	return low; //新的pivot
}

/*void QSort(SqList &L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(L, low, high);
		QSort(L, low, pivot - 1);
		QSort(L, pivot + 1, high);
	}
}

int Partition(SqList &L, int low, int high)
{
	int pivotkey = L.r[low].key;
	L.r[0] = L.r[low];

	while (low < high)
	{
		while (low < high && LQ(pivotkey, L.r[high].key))high--;
		L.r[low] = L.r[high];
		while (low < high && LQ(L.r[low].key, pivotkey)) low++;
		L.r[high] = L.r[low];
	}
	L.r[low] = L.r[0];

	return low; //新的pivot
}*/

void swap(RedType &a, RedType &b)
{
	RedType temp = a;
	a = b;
	b = temp;
}