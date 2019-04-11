#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef struct Node
{
	ElemType data;
	struct Node *Next;
}Node;
typedef struct Node *CirLink;

int JudgeCir(CirLink &pNode); //从头再来法
int FastSlow(CirLink &pNode); //快慢指针法

int JudgeCir(CirLink &pNode)
{
	CirLink p = pNode, q;
	int i = 1, j = 1;

	while (p)
	{
		q = pNode;
		j = 1;
		p = p->Next;
		i++;
		while (q != p)
		{
			q = q->Next;
			j++;
		}
		if (i != j)
		{
			printf("循环位置：%d\n", j);
			return 1;
		}	
	}

}

int FastSlow(CirLink &pNode)
{
	CirLink p = pNode, q;
	int i = 1, j = 1;

	//但是很难判断位置
	
}