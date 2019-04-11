#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define LETT_NUM 26

typedef char ElemType;
typedef int Status;
typedef struct DualNode
{
	ElemType lett;
	struct DualNode *prior;
	struct DualNode *next;
}DualNode, *DuLinkList;

Status Init(DuLinkList &L);
Status Turn(DuLinkList &L, int n);
Status Read(DuLinkList &L);

int main()
{
	DuLinkList L;
	int n;
	if (Init(L))
	{
		printf("请输入要移动多少：");
		scanf("%d", &n);
	}
	Turn(L, n);

	return 0;
}

Status Init(DuLinkList &L)
{
	DuLinkList temp, rear;
	L = (DuLinkList)malloc(sizeof(DualNode));
	if (!L) return ERROR;
	L->lett = 'A';
	L->next = L;
	L->prior = L;
	temp = rear = L;

	for (int i = 1; i < LETT_NUM; i++)
	{
		temp = (DuLinkList)malloc(sizeof(DualNode));
		if (!temp) return ERROR;
		temp->lett = 'A' + i;
		temp->next = L;
		temp->prior = rear;
		rear->next = temp;
		L->prior = temp;
		rear = temp;
	}

	return OK;
}

Status Turn(DuLinkList &L, int n)
{
	DuLinkList head = L;

	for (int i = n; i > 0; i--)
		head = head->next;
	for (int i = n; i < 0; i++)
		head = head->prior;
	Read(head);

	return OK;
}

Status Read(DuLinkList &L)
{
	DuLinkList target;
	int i;

	for (target = L, i = 0; i < LETT_NUM;target = target->next, i++)
		printf("%-3c", target->lett);
	printf("\n");

	return OK;
}