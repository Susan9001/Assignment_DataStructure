#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct Node
{
	ElemType data;
	struct Node* next;
}*CirLink;
typedef struct LinkQueue
{
	CirLink rearE;
	int len;
}LinkQueue;

Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, ElemType e);
Status DeQueue(LinkQueue &Q, ElemType &e);
Status ReadQueue(LinkQueue Q);
Status CreatQueue(LinkQueue &Q, int len);

int main()
{
	LinkQueue Q;
	ElemType e;
	int choice, temp, len;

	if (InitQueue(Q))
		printf("��ʼ���ɹ���\n");
	else
		return 0;

	printf("1������\t2������\n");
	printf("3������\t4��ɾ��\n");

	while (true)
	{
		printf("\n�����������Űɣ�");
		while (scanf("%d", &choice) != 1 || choice > 4 || choice < 1)
		{
			printf("����������Ү~~���������룺");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			printf("�����볤�ȣ�");
			scanf("%d", &len);
			if (!CreatQueue(Q, len))
				printf("������Ү~~\n");
			else
				ReadQueue(Q);
			break;
		case 2:
			ReadQueue(Q);
			break;
		case 3:
			printf("������Ҫ���ӵ�Ԫ�أ�");
			scanf("%d", &e);
			if (!EnQueue(Q, e))
				printf("���ӳ�����Ү~~\n");
			else
				ReadQueue(Q);
			break;
		case 4:
			if (!DeQueue(Q, e))
				printf("���ӳ�����Ү~~\n");
			else
			{
				printf("���ӵ��ǣ�%d\n", e);
				printf("���Ϊ��");
				ReadQueue(Q);
			}
			break;
		}
	}
	return 0;
}

Status InitQueue(LinkQueue &Q)
{
	Q.rearE = (Node*)malloc(sizeof(Node));
	if (!Q.rearE) return OVERFLOW;
	Q.rearE->next = Q.rearE;
	Q.len = 0;
	return OK;
}

Status EnQueue(LinkQueue &Q, ElemType e)
{
	Node* p; 
	p = (Node*)malloc(sizeof(Node));
	if (!p) return ERROR;
	p->data = e;
	p->next = Q.rearE->next;
	Q.rearE->next = p;
	Q.rearE = p;
	Q.len++;
	return OK;
}

Status DeQueue(LinkQueue &Q, ElemType &e)
{
	if (!Q.len) return ERROR;
	Node* head = Q.rearE->next;
	Node* headE = head->next;
	e = headE->data;
	head->next = headE->next;
	if (headE == Q.rearE) //ֻ��һ��Ԫ���ˣ�Ҫ�����㵽ͷȥ
		Q.rearE = head;
	if (headE) free(headE);
	Q.len--;
	return OK;
}

Status ReadQueue(LinkQueue Q)
{
	if (!Q.len)
	{
		printf("�տ���Ҳ~\n");
		return OK;
	}
	Node* curr = Q.rearE->next->next; //ָ��ͷԪ��
	if (curr == Q.rearE) //ͷԪ�ؼ�βԪ��ʱ
	{
		printf("%d\n", curr->data);
		return OK;
	}
	while (curr != Q.rearE->next) //ֱ�����е��յ�ͷָ��
	{
		printf("%-4d", curr->data);
		curr = curr->next;
	}
	return OK;
}

Status CreatQueue(LinkQueue &Q, int len)
{
	srand(time(NULL));
	for (int i = 0; i < len; i++)
	{
		if (!EnQueue(Q, rand() % 40 + 1))
			return ERROR;
	}	
	return OK;
}