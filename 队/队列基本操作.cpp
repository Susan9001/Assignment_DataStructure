#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;
typedef int Status;
typedef struct QNode 
{
	ElemType data;
	struct QNode* next;
}QNode;
typedef struct LinkQueue 
{
	QNode* front; //空的！
	QNode* rear;
}LinkQueue;
typedef QNode* QueuePtr;

Status InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) return ERROR;
	Q.front->next = NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q, ElemType e)
{
	QNode* q;

	q = (QNode*)malloc(sizeof(QNode));
	q->data = e;
	q->next = NULL;
	Q.rear->next = q;
	Q.rear = q;
	return OK;
}

Status DeQueue(LinkQueue &Q, ElemType &e)
{
	if (Q.front == Q.rear) 
		return ERROR; //空

	QNode *p = Q.front->next; //待删除的头元素
	e = p->data;
	if (p == Q.rear) 
		Q.rear = Q.front; //考虑当rear指针和front紧挨着的时候，rear指针会被影响到
	Q.front->next = p->next;
	free(p);
	return OK;
}