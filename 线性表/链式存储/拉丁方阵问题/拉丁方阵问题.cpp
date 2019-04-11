#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef struct Node
{
	ElemType data;
	Node *next;
}Node;
typedef struct Node* CirLink;

Status Init(CirLink &pNode, int n);
Status Latin(CirLink &pNode, int n);

int main()
{
	int n;
	CirLink pNode;

	printf("请输入拉丁方阵的行列数：");
	scanf("%d", &n);
	Init(pNode, n);
	Latin(pNode, n);

	return 0;
}

Status Init(CirLink &pNode, int n)
{
	CirLink temp, rear;
	pNode = (CirLink)malloc(sizeof(Node));
	if (!pNode) return ERROR;
	pNode->data = 1;
	pNode->next = pNode;
	rear = temp = pNode;

	for (int i = 2; i <= n; i++)
	{
		temp = (CirLink)malloc(sizeof(Node));
		if (!temp) return ERROR;
		temp->data = i;
		temp->next = pNode;
		rear->next = temp;
		rear = temp;
	}

	return OK;
}

Status Latin(CirLink &pNode, int n)
{
	int i, j;
	CirLink target, head = pNode;

	for (j = 1; j <= n; j++)
	{
		for (target = head, i = 1; i <= n; i++, target = target->next)
			printf("%-3d", target->data);
		putchar('\n');
		head = head->next;
	}

	return OK;
}

