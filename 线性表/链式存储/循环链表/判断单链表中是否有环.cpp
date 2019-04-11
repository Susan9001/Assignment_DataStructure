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

int JudgeCir(CirLink &pNode); //��ͷ������
int FastSlow(CirLink &pNode); //����ָ�뷨

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
			printf("ѭ��λ�ã�%d\n", j);
			return 1;
		}	
	}

}

int FastSlow(CirLink &pNode)
{
	CirLink p = pNode, q;
	int i = 1, j = 1;

	//���Ǻ����ж�λ��
	
}