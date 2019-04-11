#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define OK 1
#define ERROR 0
#define CARD_COUNT 13

typedef int ElemType;
typedef int Status;
typedef struct Node
{
	ElemType data;
	Node *next;
}Node;
typedef struct Node* CirLink;

Status Init(CirLink &pNode);
Status Putin(CirLink &pNode);
Status Read(CirLink pNode);

int main()
{
	CirLink pNode;

	if(!Init(pNode)) printf("分配内存失败了耶\n");
	if(!Putin(pNode)) printf("分配出错了耶\n");
	Read(pNode);

	return 0;
}

Status Init(CirLink &pNode)
{
	CirLink rear, temp;

	pNode = (Node*)malloc(sizeof(ElemType));
	temp = (Node*)malloc(sizeof(ElemType));
	if ((!pNode) || (!temp)) return ERROR;
	pNode->data = 0;
	pNode->next = pNode;
	rear = pNode;

	for (int i = 0; i < CARD_COUNT - 1; i++)
	{
		temp = (Node*)malloc(sizeof(ElemType));
		if (!temp) return ERROR;
		temp->data = 0;
		temp->next = pNode;
		rear->next = temp;
		rear = temp;
	}
	return OK;
}

Status Putin(CirLink &pNode)
{
	CirLink target = pNode;
	int i = 1;

	while (i <= CARD_COUNT)
	{
		target->data = i;
		if (i == CARD_COUNT && target->data == i)
			break;
		i++;
			
		for (int j = 1; j <= i; j++) //target为目标的前一个
		{
			target = target->next;
			while(target->data)
				target = target->next;
		}
		//printf("黑桃%d\n", target->data);
	}
	putchar('\n');
	return OK;
}

Status Read(CirLink pNode)
{
	CirLink target;
	int i = 1;
	if (!pNode) return ERROR;

	for (target = pNode; target != target->next && i < CARD_COUNT; target = target->next, i++)
		printf("黑桃%d->", target->data);
	printf("黑桃%d\n", target->data);
	return OK;
}


