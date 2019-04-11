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
		printf("第%d个人的密码：", i);
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
		printf("第%d个人的密码：%d\n", i, target->secret);
	printf("第%d个人的密码：%d\n", i, target->secret);
	return OK;
}

Status Process(CirLink &pNode)
{
	CirLink target = pNode;
	int M, i;
	if (!pNode) return ERROR;

	printf("大佬，请指定一个起始数：");
	scanf("%d", &M);

	while (target != target->next)//每次开始都target都报1
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