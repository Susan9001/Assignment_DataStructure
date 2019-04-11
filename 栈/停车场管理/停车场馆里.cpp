#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_IN 2 //停车场里面最多放多少车
#define MAX_NAME 30 //车牌号最长多少
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

/*出车和入车*/
Status SetCarTime(Car &car, char choice); //choice，choice为A、a表示进入，D、d表示设定离开时间
Status GetCharge(Car car, double &charge); //收费函数,返回收多少钱
Status CarIn(LinkQueue &Q, sqStack &s);
Status CarOut(LinkQueue &Q, sqStack &s);
/*队列基本操作*/
Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, ElemType e);
Status DeQueue(LinkQueue &Q, ElemType &e);
Status EmptyQueue(LinkQueue Q);
Status ReadQueue(LinkQueue Q);
/*栈基本操作*/
Status initStack(sqStack &s);
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
Status FullStack(sqStack s); //判断是否满了
Status EmptyStack(sqStack s); //判断是否空
Status ReadStack(sqStack s);

int main()
{
	sqStack inside;
	LinkQueue waiting;
	int choice;

	if (initStack(inside) && InitQueue(waiting))
		printf("给你一个五星级的停车场！一共%d个停车位~~\n", MAX_IN);

	printf("1、进车\t2、出车\t3、查看停车场\t4、查看等待队列5、退出\n");
	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 5)
		{
			printf("好像输入错误耶~~请重新输入选择：");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //消除回车

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
				printf("停车场里面空空如也！\n");
			break;
		case 4:
			if (!ReadQueue(waiting))
				printf("没有车等待进入~~\n");
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

	printf("请输入要进队的车牌或车名字：");
	gets_s(car.name, MAX_NAME);

	if (!FullStack(s))
	{
		SetCarTime(car, 'a');
		if (Push(s, car))
		{
			printf("成功进入车库！\n");
			ReadStack(s);
		}
	}
	else
	{
		printf("车库塞不下啦，进入等待队列\n");
		if(EnQueue(Q, car))
			ReadQueue(Q);
	}
	return OK;
}

Status CarOut(LinkQueue &Q, sqStack &s)
{
	sqStack temp;
	ElemType curr_car;
	double charge; //收费
	char name[MAX_NAME];

	initStack(temp);
	printf("请输入要出去的车名字：");
	gets_s(name, MAX_NAME);
	do
	{
		Pop(s, curr_car);
		Push(temp, curr_car);
	} while (strcmp(curr_car.name, name) && !EmptyStack(s)); //这一步超级容易错！

	if (strcmp(curr_car.name, name) != 0) 
	{
		printf("车库里头没找到该车耶~~\n");
		while(!EmptyStack(temp)) //再次原样放回去
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
			printf("《%s》停了%d秒，盛惠%.2lf元！\n", curr_car.name, 
			(curr_car.dep_time.hour - curr_car.arr_time.hour) * 3600 
				+(curr_car.dep_time.min - curr_car.arr_time.min) * 60 
				+ (curr_car.dep_time.sec - curr_car.arr_time.sec), charge);
		Pop(temp, curr_car); //把指定的车开走
		while (!EmptyStack(temp)) //其他车再次原样放回去
		{
			Pop(temp, curr_car);
			Push(s, curr_car);
		}
		if (!EmptyQueue(Q)) //把队列中等候的第一辆车塞进去停车场
		{
			DeQueue(Q, curr_car);
			SetCarTime(curr_car, 'a'); //这一步也容易忘记！
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
		(car.dep_time.min - car.arr_time.min) * 60 + (car.dep_time.sec - car.arr_time.sec)) / 10.0; //经常忘掉.0

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
	printf("等待队列：");
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

	printf("车名\t到达时间\n");
	for (p = s.base; p != s.top; p++)
		printf("%s\t%d时%d分%d秒\n", p->name, p->arr_time.hour, p->arr_time.min, p->arr_time.sec);
	//putchar('\n');
	return OK;
}
