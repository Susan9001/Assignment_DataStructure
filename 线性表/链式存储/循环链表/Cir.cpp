#include <stdio.h>
#include <stdlib.h>
#include "Cir.h"
#define OK 1
#define ERROR 0
#define OVERFLOW -2

Status Init(CirLink &pNode)
{
	CirLink temp, target;
	int i = 1;
	ElemType item;

	while (1)
	{
		printf("请输入倒数第%d个元素：", i);
		i++;
		scanf("%d", &item);
		if (!item) return OK;

		if (!pNode)
		{
			pNode = (CirLink)malloc(sizeof(Node));
			if (!pNode) return ERROR;
			pNode->data = item;
			pNode->Next = pNode;
		}
		else
		{
			temp = (CirLink)malloc(sizeof(Node));
			for (target = pNode; target->Next != pNode; target = target->Next);
			temp->data = item;
			temp->Next = pNode;
			target->Next = temp;
		}
	}
}

Status Read(CirLink pNode)
{
	CirLink target;
	if (!pNode)
	{
		printf("Ops!空循环链表！\n");
		return ERROR;
	}
	printf("现在的循环表为（倒数）：");
			
	for (target = pNode; target->Next != pNode; target = target->Next)
		printf("%d ", target->data);
	printf("%d", target->data);
	putchar('\n');
	return OK;
}

Status Insert(CirLink &pNode, int i, ElemType e)
{
	int j;
	CirLink target = pNode, temp;

	temp = (CirLink)malloc(sizeof(ElemType));
	if (!temp) return ERROR;
		
	for (j = 0; j < i - 1 && target->Next != pNode; j++)
		target = target->Next;	
	if (target->Next == pNode && j < i - 1 || i < 1)  return OVERFLOW;
	//以上表示已经转过一圈了但还没到终点	
		
	temp->data = e;
	temp->Next = target->Next;
	target->Next = temp;
	return OK;
}

Status Delete(CirLink &pNode, int i)
{
	int j;
	CirLink target = pNode;

	for (j = 0; j < i - 2 && target->Next != pNode; j++)
		target = target->Next;//target最终为要删除的元素的前一个
	if (target->Next == pNode && j < i - 2 || i < 1)  return OVERFLOW;
	//以上表示已经转过一圈了但还没到终点	

	target->Next = target->Next->Next;
	return OK;
}

int Search(CirLink pNode, ElemType e)
{
	CirLink target;
	int i = 1;

	for (target = pNode; target->data != e && target->Next != pNode; i++)
		target = target->Next;
	if (target->Next == pNode && target->Next != pNode) return ERROR;
	else return i;
}