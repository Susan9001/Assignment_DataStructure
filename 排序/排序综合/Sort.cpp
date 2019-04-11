#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Sort.h"

Status CreateSqList(SqList &L)
{
	int choice, i, j;

	printf("1���Զ�����  2���ֶ�����\n");
	printf("��ѡ��(ѡ��-������20�ĳ���)��");
	while (scanf("%d-%d", &choice, &L.lenght) != 2 || choice < 1 || choice > 2 || L.lenght > SQMAXSIZE)
	{
		printf("�д���Ү~���������룺");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');
	switch (choice)
	{
	case 1:
		srand(time(NULL));
		for (i = 1; i <= L.lenght; i++)
			L.r[i].key = 1 + rand() % 100;
		    //������Ϣ�˴���ʱ����
		break;
	case 2:
		printf("��ֱ�����ؼ��֣�");
		for (i = 1; i <= L.lenght; i++)
			scanf("%d", &L.r[i].key);
		while (getchar() != '\n');
		break;
	}

	return OK;
}

void ReadSqList(SqList L)
{
	printf("������%d��", L.lenght);
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
			//������Ϣ��ʱ����
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

	for (i = 1; i <= L.lenght; i++) //������ں���������
	{
		L.r[0] = L.r[i];
		low = 1;
		high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (LT(L.r[0].key, L.r[mid].key)) //targetС��������
				high = mid - 1;
			else
				low = mid + 1;
		}
		for (j = i - 1; j > high; j--) //targetǡ�ñ�low�󣬱�low��һ��С
			L.r[j + 1] = L.r[j]; //��lowΪ�жϱ�׼������ɵ���һ����
		L.r[high + 1] = L.r[0];
	}
}

void TWInsertSort(SqList &L)
{
	int i, j;
	int first = 1, last = 1;
	RedType d[SQMAXSIZE + 1];
	
	d[1] = L.r[1]; //��ʼ��key
	for (i = 2; i <= L.lenght; i++) //С�ڵ��ڣ�
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
			/*������first�ĳ�ʼ��*/
			if (first == last) 
			{
				first = L.lenght;
				d[first] = L.r[i];
				continue;
			}
			for (j = first; !LT(L.r[i].key, d[j].key); j++) //֮ǰ�㷴�ˣ�
				d[j - 1] = d[j];
			d[j - 1] = L.r[i];
			first--;
		}

	}

	printf("\nfirst = %d, final = %d\n", first, last);
	for (i = 1; i <= L.lenght; i++)
	{
		j = (i - first + L.lenght) % L.lenght + 1; //�����Ǵ�0��ʼ�ģ�����Ҫ+1
		L.r[j] = d[i];//jΪ�߼��ϵ�λ�ã�����ڷ�first��
	}
}

void SLInsertSort(SqList &L)
{
	SLinkListType SL;
	int i, j;

	CreateSLinkList(L, SL);
	printf("ԭ����\n");
	ReadSLinkListType(SL);

	for (i = 2; i <= SL.length; i++)
	{  //�ҵ���[i]ǡС�ġ�j != 0? ��0����0->next��ʼ��
		for (j = 0; LT(SL.r[SL.r[j].next].rd.key, SL.r[i].rd.key); j = SL.r[j].next);
		SL.r[i].next = SL.r[j].next;
		SL.r[j].next = i;
	}
	printf("�����\n");
	ReadSLinkListType(SL);
	Arrange(SL);
	printf("�����\n");
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
		while (p < i) p = SL.r[p].next; //�ܾ�������ǷǱ�Ҫ��
		q = SL.r[p].next;
		if (p != i)
		{
			SLNode temp = SL.r[p];
			SL.r[p] = SL.r[i];
			SL.r[i] = temp;
			SL.r[i].next = p; //��¼�����ߵļ�¼
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
	int low, high, flag = 1; //ÿ�ε�ͷβָ�룬���б�ʾ�Ƿ��н�����flag
	int i, j; //i��ͷlow��ʼ��j��βhigh��ʼ

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
		Partition(L, old_low, low - 1); //���ڵ�low��Ϊpivot��
	if(low + 1 < old_high)
		Partition(L, low + 1, old_high);
	return low; //�µ�pivot
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

	return low; //�µ�pivot
}*/

void swap(RedType &a, RedType &b)
{
	RedType temp = a;
	a = b;
	b = temp;
}