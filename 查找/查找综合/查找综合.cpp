#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFINITY INT_MAX
#define EQ(a, b) ((a)== (b)) //相等
#define LT(a, b) ((a) < (b)) //左小
#define LQ(a, b) ((a) <= (b)) //左小于等于

typedef int Status;
typedef int KeyType; //关键字类型
typedef struct SElemType {
	KeyType key;
	//其他
}SElemType;
typedef struct SSTable { //静态查找表顺序存储
	SElemType *elem;
	int length;
}SSTable;

Status InitSSTable(SSTable &ST, int n);
Status SelectionSort(SSTable &ST);
Status ReadSSTable(SSTable ST);
int Search(SSTable ST, KeyType key, int &count);
int Search_Seq(SSTable ST, KeyType key, int &count);
int Search_SortedSeq(SSTable ST, KeyType key, int &count); //从小到大排序后，高下标位作哨兵的顺序查找
int Search_Bin(SSTable ST, KeyType key, int low, int high, int &count); //递归法
Status swap(SElemType &e1, SElemType &e2);

int main()
{
	SSTable ST;
	int n, result, choice;
	int count = 0; //表示比较次数
	KeyType key;

	printf("1、生成顺序静态查找表  2、选择排序(小->大)  3、查找\n");
	while (true)
	{
		printf("\n请输入选择（n/N退出）：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
		{
			printf("输错了耶，请重新输入：");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			printf("请输入要生成的顺序静态查找表长度：");
			scanf("%d", &n);
			if (InitSSTable(ST, n))
				ReadSSTable(ST);
			break;
		case 2:
			if (SelectionSort(ST))
			{
				printf("排序后：");
				ReadSSTable(ST);
			}
			break;
		case 3:
			printf("请输入要查找的关键字：");
			scanf("%d", &key);
			while (getchar() != '\n');
			result = Search(ST, key, count);
			if (result && result <= ST.length)
				printf("%d的位置为：%d", key, result);
			else
				printf("找不到耶~·~");
			printf("（比较次数：%d）\n", count);
			break;
		case (int)'n': case (int)'N':
			return 0;
		default:
			printf("该功能待完成~~\n");
			break;
		}
	}

	return 0;
}

Status InitSSTable(SSTable &ST, int n)
{
	ST.elem = (SElemType*)malloc(sizeof(SElemType) * (n + 2)); //0号位、高下标位要空出来
	if (!ST.elem) return ERROR;

	srand(time(NULL));
	for (int i = 1; i <= n; i++)
		ST.elem[i].key = 1 + rand() % 100; //1-100
	ST.elem[0].key = INFINITY; //0号初始化为无穷大
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
				swap(ST.elem[i], ST.elem[j]); //左大右小，换！
		}
	}
	return OK;
}

Status ReadSSTable(SSTable ST)
{
	printf("长度%d：", ST.length);
	for (int i = 1; i <= ST.length; i++)
		printf("%-4d", ST.elem[i].key);
	putchar('\n');
	return OK;
}

int Search(SSTable ST, KeyType key, int &count)
{
	int choice;
	count = 0;

	printf("1、顺序查找(无序)  2、折半查找  3、顺序查找(排序后)\n");
	printf("请输入用什么方法查找（n/N退出）：");
	while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
	{
		printf("输错了耶，请重新输入：");
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
		return ST.length + 1; //返回高下标哨兵位
	else
		return i;
}

int Search_Bin(SSTable ST, KeyType key, int low, int high, int &count)
{
	if (low > high) return 0; //找不到

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
	//此处只更改key，其他内容可以再拓展```
	return OK;
}