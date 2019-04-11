#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFINITY INT_MAX
#define EQ(a, b) ((a)== (b)) //���
#define LT(a, b) ((a) < (b)) //��С
#define LQ(a, b) ((a) <= (b)) //��С�ڵ���

typedef int Status;
typedef int KeyType; //�ؼ�������
typedef struct SElemType {
	KeyType key;
	//����
}SElemType;
typedef struct SSTable { //��̬���ұ�˳��洢
	SElemType *elem;
	int length;
}SSTable;

Status InitSSTable(SSTable &ST, int n);
Status SelectionSort(SSTable &ST);
Status ReadSSTable(SSTable ST);
int Search(SSTable ST, KeyType key, int &count);
int Search_Seq(SSTable ST, KeyType key, int &count);
int Search_SortedSeq(SSTable ST, KeyType key, int &count); //��С��������󣬸��±�λ���ڱ���˳�����
int Search_Bin(SSTable ST, KeyType key, int low, int high, int &count); //�ݹ鷨
Status swap(SElemType &e1, SElemType &e2);

int main()
{
	SSTable ST;
	int n, result, choice;
	int count = 0; //��ʾ�Ƚϴ���
	KeyType key;

	printf("1������˳��̬���ұ�  2��ѡ������(С->��)  3������\n");
	while (true)
	{
		printf("\n������ѡ��n/N�˳�����");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
		{
			printf("�����Ү�����������룺");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("������Ҫ���ɵ�˳��̬���ұ��ȣ�");
			scanf("%d", &n);
			if (InitSSTable(ST, n))
				ReadSSTable(ST);
			break;
		case 2:
			if (SelectionSort(ST))
			{
				printf("�����");
				ReadSSTable(ST);
			}
			break;
		case 3:
			printf("������Ҫ���ҵĹؼ��֣�");
			scanf("%d", &key);
			while (getchar() != '\n');
			result = Search(ST, key, count);
			if (result && result <= ST.length)
				printf("%d��λ��Ϊ��%d", key, result);
			else
				printf("�Ҳ���Ү~��~");
			printf("���Ƚϴ�����%d��\n", count);
			break;
		case (int)'n': case (int)'N':
			return 0;
		default:
			printf("�ù��ܴ����~~\n");
			break;
		}
	}

	return 0;
}

Status InitSSTable(SSTable &ST, int n)
{
	ST.elem = (SElemType*)malloc(sizeof(SElemType) * (n + 2)); //0��λ�����±�λҪ�ճ���
	if (!ST.elem) return ERROR;

	srand(time(NULL));
	for (int i = 1; i <= n; i++)
		ST.elem[i].key = 1 + rand() % 100; //1-100
	ST.elem[0].key = INFINITY; //0�ų�ʼ��Ϊ�����
	ST.length = n;
	return OK;
}

Status SelectionSort(SSTable &ST)
{
	if (!ST.elem || ST.length <= 0) return ERROR;

	int temp, i, j;
	for (i = 1; i <= ST.length; i++)
	{
		for (j = i + 1; j <= ST.length; j++)
		{
			if (!LT(ST.elem[i].key, ST.elem[j].key))
				swap(ST.elem[i], ST.elem[j]); //�����С������
		}
	}
	return OK;
}

Status ReadSSTable(SSTable ST)
{
	printf("����%d��", ST.length);
	for (int i = 1; i <= ST.length; i++)
		printf("%-4d", ST.elem[i].key);
	putchar('\n');
	return OK;
}

int Search(SSTable ST, KeyType key, int &count)
{
	int choice;
	count = 0;

	printf("1��˳�����(����)  2���۰����  3��˳�����(�����)\n");
	printf("��������ʲô�������ң�n/N�˳�����");
	while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
	{
		printf("�����Ү�����������룺");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	switch (choice)
	{
	case 1: 
		return Search_Seq(ST, key, count);
	case 2:
		return Search_Bin(ST, key, 1, ST.length, count);
	case 3:
		return Search_SortedSeq(ST, key, count);
	default:
		return 0 ;
	}
}

int Search_Seq(SSTable ST, KeyType key, int &count)
{
	int i;
	count = 0;
	ST.elem[0].key = key;
	for (i = ST.length; !EQ(ST.elem[i].key, key); i--, count++);
	return i;
}

int Search_SortedSeq(SSTable ST, KeyType key, int &count)
{
	int i;

	ST.elem[ST.length + 1].key = key;
	for (i = 1; LT(ST.elem[i].key, key); i++);
	count = i;

	if (!EQ(ST.elem[i].key, key))
		return ST.length + 1; //���ظ��±��ڱ�λ
	else
		return i;
}

int Search_Bin(SSTable ST, KeyType key, int low, int high, int &count)
{
	if (low > high) return 0; //�Ҳ���

	int mid = (low + high) / 2;
	count++;
	if (EQ(key, ST.elem[mid].key)) return mid;
	else if (LT(key, ST.elem[mid].key)) return Search_Bin(ST, key, low, mid - 1, count);
	else return Search_Bin(ST, key, mid + 1, high, count);
}

Status swap(SElemType &e1, SElemType &e2)
{
	KeyType temp = e1.key;
	e1.key = e2.key;
	e2.key = temp;
	//�˴�ֻ����key���������ݿ�������չ```
	return OK;
}