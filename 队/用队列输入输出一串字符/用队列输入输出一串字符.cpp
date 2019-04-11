#include <stdlib.h>
#include <stdio.h>

#define EOF ';'
#define OK 1
#define ERROR 0
#define MAX_SIZE 255

typedef char ElemType;
typedef int Status;
typedef struct NQueue
{
	ElemType data;
	NQueue* next;
}NQueue;
typedef struct LinkQueue
{
	NQueue* head;
	NQueue* rear;
}LinkQueue;
typedef NQueue* NQueuePre;

Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, ElemType e);
Status DeQueue(LinkQueue &Q, ElemType &e);
Status ClearQueue(LinkQueue &Q);
Status ReadQueue(LinkQueue Q);
void Queue();
void Lines();

int main()
{
	Queue();
	return 0;
}

void Lines()
{
	LinkQueue Q;
	InitQueue(Q);

	printf("请输入字符串吧：(@有清除一行的作用，分号结束)\n");
	char ch = getchar(), temp;
	while (ch != EOF)
	{
		while (ch != '\n' && ch != EOF)
		{
			switch (ch)
			{
			case '@':
				ClearQueue(Q); break;
			default:
				EnQueue(Q, ch); break;
			} //switch
			ch = getchar();
		}
		while (Q.rear != Q.head)
		{
			DeQueue(Q, temp);
			putchar(temp);
		}
		putchar('\n');
		ClearQueue(Q);
		if (ch != EOF) ch = getchar();
	}
}

void Queue()
{
	int choice;
	ElemType e;
	ElemType *lines = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
	ElemType* ch_ptr;

	LinkQueue Q;
	if(InitQueue(Q)) 
		printf("初始化成功！\n");

	printf("1.生成一个字符串队列\t2.进队\n3.出队\t4.查看队列\t5.退出\n");
	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
		{
			printf("好像输入错误耶~~请重新输入选择：");
			while (getchar() != '\n');
		}
		while(getchar()!= '\n'); //消除回车

		switch (choice)
		{
		case 1:
			printf("请输入字符串：");
			fgets(lines, MAX_SIZE, stdin);
			ch_ptr = &lines[0];
			while (*ch_ptr != '\n')
			{
				EnQueue(Q, *ch_ptr);
				ch_ptr++;
			}
			ReadQueue(Q);
			break;
		case 2:
			printf("请输入进队的元素：");
			scanf("%c", &e);
			if (EnQueue(Q, e))
				ReadQueue(Q);
			break;
		case 3:
			if (DeQueue(Q, e))
			{
				printf("让\"%c\"元素出队！\n", e);
				ReadQueue(Q);
			}
			break;
		case 4:
			ReadQueue(Q);
			break;
		case 5:
			return;
		}
	}
}

Status ReadQueue(LinkQueue Q)
{
	if (Q.head == Q.rear) return ERROR;
	NQueue *p;
	for (p = Q.head->next; p != Q.rear; p = p->next)
		printf("%c", p->data);
	printf("%c\n", p->data);
	return OK;
}

Status InitQueue(LinkQueue &Q)
{
	Q.head = (NQueue*)malloc(sizeof(NQueue));
	if (!Q.head) return ERROR;
	Q.rear = Q.head;
	Q.rear->next = NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q, ElemType e)
{
	NQueue* p = (NQueue*)malloc(sizeof(NQueue));
	if (!p) return ERROR;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

Status DeQueue(LinkQueue &Q, ElemType &e)
{
	if (Q.head == Q.rear) return ERROR;
	NQueue* p = Q.head->next;
	e = p->data;
	if (Q.rear == Q.head->next) Q.rear = Q.head;
	Q.head->next = p->next;
	free(p);
	return OK;
}

Status ClearQueue(LinkQueue &Q)
{
	Q.rear = Q.head;
	Q.rear->next = NULL;
	return OK;
}
