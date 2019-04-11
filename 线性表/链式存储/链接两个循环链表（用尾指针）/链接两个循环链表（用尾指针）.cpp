#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;
typedef struct Node
{
	ElemType data;
	Node *next;
}Node;
typedef struct Node* CirLink;

CirLink Init(CirLink &pNode);
Status Link(CirLink pNode1, CirLink pNode2, CirLink &pNode3);
Status Read(CirLink pNode);

int main()
{
	CirLink pNode1, pNode2, pNode3, rear1, rear2;
	pNode1 = pNode2 = pNode3 = rear1 = rear2 = NULL;

	printf("��һ����������\n");
	rear1 = Init(pNode1);
	printf("��һ��β��Ϊ��%d\n", rear1->data);
	printf("\n�ڶ�����������\n");
	rear2 = Init(pNode2);
	printf("�ڶ���β��Ϊ��%d\n", rear2->data);

	if (Link(rear1, rear2, pNode3))
	{
		printf("\n���Ӻ�֮��");
		Read(pNode3);
	}

	return 0;
}

CirLink Init(CirLink &pNode)
{
	int i = 1;
	ElemType data;
	CirLink rear = NULL, temp;

	while (true)
	{
		printf("��%d����(0�˳�)��", i);
		scanf("%d", &data);
		if (!data) break;

		if (!pNode) //��һ��ѭ��������ͷ���
		{
			pNode = (CirLink)malloc(sizeof(Node));
			//if (!pNode) return ERROR;
			pNode->data = data;
			pNode->next = pNode;
			rear = pNode;
		}
		else
		{
			temp = (CirLink)malloc(sizeof(Node));
			//if (!temp) return ERROR;
			temp->data = data;
			rear->next = temp;
			temp->next = pNode;
			rear = temp;
		}
		i++;
	}

	return rear; //��󷵻�βָ��
}

Status Link(CirLink rear1, CirLink rear2, CirLink &pNode3)
{
	pNode3 = (CirLink)malloc(sizeof(Node));
	CirLink pNode1 = rear1->next;
	rear1->next = rear2->next;
	rear2->next = pNode1;
	pNode3 = rear2->next;
	return OK;
}

Status Read(CirLink pNode)
{
	CirLink target = pNode;

	while (target->next != pNode)
	{
		printf("%d->", target->data);
		target = target->next;
	}
	printf("%d\n", target->data);

	return OK;
}
