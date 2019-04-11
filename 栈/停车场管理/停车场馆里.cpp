#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_IN 2 //ͣ�����������Ŷ��ٳ�
#define MAX_NAME 30 //���ƺ������
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef struct Time
{
	int hour;
	int min;
	int sec;
};
typedef struct ElemType
{
	char name[MAX_NAME];
	Time arr_time;
	Time dep_time;
}Car;
typedef struct sqStack
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;
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

/*�������복*/
Status SetCarTime(Car &car, char choice); //choice��choiceΪA��a��ʾ���룬D��d��ʾ�趨�뿪ʱ��
Status GetCharge(Car car, double &charge); //�շѺ���,�����ն���Ǯ
Status CarIn(LinkQueue &Q, sqStack &s);
Status CarOut(LinkQueue &Q, sqStack &s);
/*���л�������*/
Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, ElemType e);
Status DeQueue(LinkQueue &Q, ElemType &e);
Status EmptyQueue(LinkQueue Q);
Status ReadQueue(LinkQueue Q);
/*ջ��������*/
Status initStack(sqStack &s);
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
Status FullStack(sqStack s); //�ж��Ƿ�����
Status EmptyStack(sqStack s); //�ж��Ƿ��
Status ReadStack(sqStack s);

int main()
{
	sqStack inside;
	LinkQueue waiting;
	int choice;

	if (initStack(inside) && InitQueue(waiting))
		printf("����һ�����Ǽ���ͣ������һ��%d��ͣ��λ~~\n", MAX_IN);

	printf("1������\t2������\t3���鿴ͣ����\t4���鿴�ȴ�����5���˳�\n");
	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
		{
			printf("�����������Ү~~����������ѡ��");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //�����س�

		switch (choice)
		{
		case 1:
			CarIn(waiting, inside);
			break;
		case 2:
			CarOut(waiting, inside);
			break;
		case 3:
			if (!ReadStack(inside))
				printf("ͣ��������տ���Ҳ��\n");
			break;
		case 4:
			if (!ReadQueue(waiting))
				printf("û�г��ȴ�����~~\n");
			break;
		case 5:
			return 0;
		}
	}

	return 0;
}

Status SetCarTime(Car &car, char choice)
{
	time_t start;
	struct tm* timeInfo;

	time(&start);
	timeInfo = gmtime(&start);
	
	switch (choice)
	{
	case 'A':case 'a':
		car.arr_time = { timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec };
		car.dep_time = { 0, 0, 0 };
		break;
	case 'D':case'd':
		car.dep_time = { timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec };
		//car.arr_time = { 0, 0, 0 };
		break;
	}
	
	return OK;
}

Status CarIn(LinkQueue &Q, sqStack &s)
{
	Car car;

	printf("������Ҫ���ӵĳ��ƻ����֣�");
	gets_s(car.name, MAX_NAME);

	if (!FullStack(s))
	{
		SetCarTime(car, 'a');
		if (Push(s, car))
		{
			printf("�ɹ����복�⣡\n");
			ReadStack(s);
		}
	}
	else
	{
		printf("������������������ȴ�����\n");
		if(EnQueue(Q, car))
			ReadQueue(Q);
	}
	return OK;
}

Status CarOut(LinkQueue &Q, sqStack &s)
{
	sqStack temp;
	ElemType curr_car;
	double charge; //�շ�
	char name[MAX_NAME];

	initStack(temp);
	printf("������Ҫ��ȥ�ĳ����֣�");
	gets_s(name, MAX_NAME);
	do
	{
		Pop(s, curr_car);
		Push(temp, curr_car);
	} while (strcmp(curr_car.name, name) && !EmptyStack(s)); //��һ���������״�

	if (strcmp(curr_car.name, name) != 0) 
	{
		printf("������ͷû�ҵ��ó�Ү~~\n");
		while(!EmptyStack(temp)) //�ٴ�ԭ���Ż�ȥ
		{
			Pop(temp, curr_car);
			Push(s, curr_car);
		}
		return ERROR;
	}
	else
	{
		SetCarTime(curr_car, 'd');
		if (GetCharge(curr_car, charge))
			printf("��%s��ͣ��%d�룬ʢ��%.2lfԪ��\n", curr_car.name, 
			(curr_car.dep_time.hour - curr_car.arr_time.hour) * 3600 
				+(curr_car.dep_time.min - curr_car.arr_time.min) * 60 
				+ (curr_car.dep_time.sec - curr_car.arr_time.sec), charge);
		Pop(temp, curr_car); //��ָ���ĳ�����
		while (!EmptyStack(temp)) //�������ٴ�ԭ���Ż�ȥ
		{
			Pop(temp, curr_car);
			Push(s, curr_car);
		}
		if (!EmptyQueue(Q)) //�Ѷ����еȺ�ĵ�һ��������ȥͣ����
		{
			DeQueue(Q, curr_car);
			SetCarTime(curr_car, 'a'); //��һ��Ҳ�������ǣ�
			Push(s, curr_car);
		}
		return OK;
	}
}

Status GetCharge(Car car, double &charge)
{
	if (!car.dep_time.hour && !car.dep_time.min && !car.dep_time.sec)
		return ERROR;
	charge = ((car.dep_time.hour - car.arr_time.hour) * 3600 +
		(car.dep_time.min - car.arr_time.min) * 60 + (car.dep_time.sec - car.arr_time.sec)) / 10.0; //��������.0

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
	if (EmptyQueue(Q)) return ERROR;
	NQueue* p = Q.head->next;
	e = p->data;
	if (Q.rear == p) Q.rear = Q.head;
	Q.head->next = p->next;
	free(p);
	return OK;
}

Status EmptyQueue(LinkQueue Q)
{
	if (Q.head == Q.rear) return OK;
	else return 0;
}

Status ReadQueue(LinkQueue Q)
{
	if (EmptyQueue(Q)) return ERROR;
	NQueue *p;
	printf("�ȴ����У�");
	for (p = Q.head->next; p != Q.rear; p = p->next)
		printf("%s, ", p->data.name);
	printf("%s\n", p->data.name);
	return OK;
}

Status initStack(sqStack &s)
{
	s.base = (ElemType*)malloc(sizeof(ElemType) * MAX_IN);
	if (!s.base) return ERROR;
	s.top = s.base;
	s.stackSize = MAX_IN;

	return OK;
}

Status Push(sqStack &s, ElemType e)
{
	if (FullStack(s))
		return ERROR;

	*(s.top) = e;
	s.top++;
	return OK;
}

Status Pop(sqStack &s, ElemType &e)
{
	if (EmptyStack(s)) return ERROR;
	s.top--;
	e = *(s.top);

	return OK;
}

Status FullStack(sqStack s)
{
	if (s.top - s.base >= s.stackSize) return OK;
	else return 0;
}

Status EmptyStack(sqStack s)
{
	if (s.base == s.top) return OK;
	else return 0;
}

Status ReadStack(sqStack s)
{
	if (!s.base) return ERROR;
	ElemType *p;

	printf("����\t����ʱ��\n");
	for (p = s.base; p != s.top; p++)
		printf("%s\t%dʱ%d��%d��\n", p->name, p->arr_time.hour, p->arr_time.min, p->arr_time.sec);
	//putchar('\n');
	return OK;
}
