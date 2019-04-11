#include <stdio.h>
#include <stdlib.h>
#include "JsHigh.h"
#define OK 1
#define ERROR 0
#define OVERFLOW -2

int Init(CirLink &pNode)
{
	int i = 1, n;
	ElemType secret;
	CirLink rear, temp;

	while (true)
	{
		printf("��%d���˵����룺", i);
		scanf("%d", &secret);
		if (!secret) return i - 1;

		if (!pNode)
		{
			pNode = (CirLink)malloc(sizeof(Node));
			if (!pNode) return ERROR;
			pNode->secret = secret;
			pNode->num = 1;
			pNode->next = pNode;
			rear = pNode;
		}
		else
		{
			temp = (CirLink)malloc(sizeof(Node));
			temp->secret = secret;
			temp->num = i;
			temp->next = pNode;
			rear->next = temp;
			rear = temp;
		}
		i++;
	}
}

Status Read(CirLink pNode)
{
	CirLink target;
	int i = 1;
	if (!pNode) return ERROR;

	for (target = pNode; target->next != pNode; target = target->next, i++)
		printf("��%d���˵����룺%d\n", i, target->secret);
	printf("��%d���˵����룺%d\n", i, target->secret);
	return OK;
}

Status Process(CirLink &pNode)
{
	CirLink target = pNode;
	int M, i;
	if (!pNode) return ERROR;

	printf("���У���ָ��һ����ʼ����");
	scanf("%d", &M);

	while (target != target->next)//ÿ�ο�ʼ��target����1
	{
		for (i = 0; i < M - 2; i++)
			target = target->next;
		printf("%d->", target->next->num);
		M = target->next->secret;
		target->next = target->next->next;
		target = target->next;
	}
	printf("%d\n", target->num);

	return OK;
}