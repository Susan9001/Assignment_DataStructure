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
		printf("初始化成功！\n");
	else
		return 0;

	printf("1、生成\t2、遍历\n");
	printf("3、插入\t4、删除\n");

	while (true)
	{
		printf("\n请输入操作序号吧：");
		while (scanf("%d", &choice) != 1 || choice > 4 || choice < 1)
		{
			printf("请好像输错了耶~~请重新输入：");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			printf("请输入长度：");
			scanf("%d", &len);
			if (!CreatQueue(Q, len))
				printf("出错了耶~~\n");
			else
				ReadQueue(Q);
			break;
		case 2:
			ReadQueue(Q);
			break;
		case 3:
			printf("请输入要进队的元素：");
			scanf("%d", &e);
			if (!EnQueue(Q, e))
				printf("进队出错了耶~~\n");
			else
				ReadQueue(Q);
			break;
		case 4:
			if (!DeQueue(Q, e))
				printf("出队出错了耶~~\n");
			else
			{
				printf("出队的是：%d\n", e);
				printf("结果为：");
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
	if (headE == Q.rearE) //只有一个元素了，要把他搞到头去
		Q.rearE = head;
	if (headE) free(headE);
	Q.len--;
	return OK;
}

Status ReadQueue(LinkQueue Q)
{
	if (!Q.len)
	{
		printf("空空如也~\n");
		return OK;
	}
	Node* curr = Q.rearE->next->next; //指向头元素
	if (curr == Q.rearE) //头元素即尾元素时
	{
		printf("%d\n", curr->data);
		return OK;
	}
	while (curr != Q.rearE->next) //直到进行到空的头指针
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