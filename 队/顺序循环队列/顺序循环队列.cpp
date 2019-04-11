#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 5

typedef int Status;
typedef int ElemType;
typedef struct {
	ElemType *base;
	int front; //头下标（这些跟栈不同~~）
	int rear; //尾下标
}SqQueue;

Status InitQueue(SqQueue &Q);
int QueueLenght(SqQueue Q);
Status EnQueue(SqQueue &Q, ElemType e);
Status DeQueue(SqQueue &Q, ElemType &e);
Status CreateQueue(SqQueue &Q, int len);
void ReadQueue(SqQueue Q);

int main()
{
	int choice, len;
	ElemType e;
	SqQueue Q;
	if (InitQueue(Q))
		printf("初始化成功！");

	printf("\n1.生成循环队列\t2.入队\t3.出队\t4.查看队列\t5.队列长度\n");
	while (1)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
		{
			printf("输错了也，请重新输入吧：");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			printf("请输入指定队列长度：");
			scanf("%d", &len);
			if(CreateQueue(Q, len))
				ReadQueue(Q);
			break;
		case 2:
			printf("请输入要让什么元素进队列：");
			scanf("%d", &e);
			EnQueue(Q, e);
			ReadQueue(Q);
			break;
		case 3:
			DeQueue(Q, e);
			printf("%d出队\n", e);
			ReadQueue(Q);
			break;
		case 4:
			ReadQueue(Q);
			break;
		case 5:
			printf("队列长度：%d\n", QueueLenght(Q));
			break;
		}//switch
	}//while

	return 0;
}

Status CreateQueue(SqQueue &Q, int len)
{
	srand(time(NULL));
	if (len <= 0) return ERROR;
	for (int i = 0; i < len; i++)
		EnQueue(Q, rand() % 40 + 1);
	return OK;
}

void ReadQueue(SqQueue Q)
{
	int len = QueueLenght(Q);
	int i = Q.front;
	//printf("头：%d-%d; 尾巴：%d-%d\n", Q.front, Q.base[Q.front], Q.rear, Q.base[Q.rear]);
	while (i != Q.rear)
	{
		printf("%-4d", Q.base[i]);
		i = (i + 1) % MAXSIZE;
	}
		
	putchar('\n');
}

Status InitQueue(SqQueue &Q)
{
	Q.base = (ElemType*)malloc(MAXSIZE * sizeof(ElemType));
	if (!Q.base) return OVERFLOW;
	Q.front = Q.rear = 0;
	return OK;
}

int QueueLenght(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

Status EnQueue(SqQueue &Q, ElemType e)
{
	if ((Q.rear + 1) % MAXSIZE == Q.front) return ERROR;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXSIZE;
	return OK;
}

Status DeQueue(SqQueue &Q, ElemType &e)
{
	if (Q.rear == Q.front) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSIZE;
	return OK;
}