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
	int front; //ͷ�±꣨��Щ��ջ��ͬ~~��
	int rear; //β�±�
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
		printf("��ʼ���ɹ���");

	printf("\n1.����ѭ������\t2.���\t3.����\t4.�鿴����\t5.���г���\n");
	while (1)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
		{
			printf("�����Ҳ������������ɣ�");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			printf("������ָ�����г��ȣ�");
			scanf("%d", &len);
			if(CreateQueue(Q, len))
				ReadQueue(Q);
			break;
		case 2:
			printf("������Ҫ��ʲôԪ�ؽ����У�");
			scanf("%d", &e);
			EnQueue(Q, e);
			ReadQueue(Q);
			break;
		case 3:
			DeQueue(Q, e);
			printf("%d����\n", e);
			ReadQueue(Q);
			break;
		case 4:
			ReadQueue(Q);
			break;
		case 5:
			printf("���г��ȣ�%d\n", QueueLenght(Q));
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
	//printf("ͷ��%d-%d; β�ͣ�%d-%d\n", Q.front, Q.base[Q.front], Q.rear, Q.base[Q.rear]);
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