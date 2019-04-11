#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define LETT_NUM 26
#define LETT_MAX 100

typedef char ElemType;
typedef int Status;
typedef struct DualNode
{
	ElemType lett; //输入为明文
	int secret;
	struct DualNode *prior;
	struct DualNode *next;
}DualNode, *DuLinkList;

Status Init(DuLinkList &L0);
DuLinkList Turn(DuLinkList L, int n);
Status Encrypt(DuLinkList &L, ElemType *str, DuLinkList L0);
Status Decrypt(DuLinkList &L, DuLinkList);
Status Read(DuLinkList L);

int main()
{
	ElemType *str;
	str = (ElemType*)malloc(LETT_MAX * sizeof(ElemType));
	
	DuLinkList L, L0;

	printf("随机生成密码表(小写字母)...\n");
	Init(L0);

	printf("请输入要加密的字符串吧(不大于100个字)：");
	fgets(str, LETT_MAX, stdin);

	if(Encrypt(L, str, L0))
		Read(L);
	else printf("错误！\n");
	
	printf("任意键再显示明文：");
	getchar();
	if (Decrypt(L, L0))
		Read(L);

	return 0;
}

Status Init(DuLinkList &L0)
{
	DuLinkList temp, rear;
	L0 = (DuLinkList)malloc(sizeof(DualNode));
	if (!L0) return ERROR;

	srand(time(NULL));
	L0->lett = 'a';
	L0->secret = rand() % 50 - 100;
	L0->next = L0;
	L0->prior = L0;
	temp = rear = L0;

	for (int i = 1; i < LETT_NUM; i++)
	{
		temp = (DuLinkList)malloc(sizeof(DualNode));
		if (!temp) return ERROR;
		temp->secret = rand() % 50 - 100;
		temp->lett = 'a' + i;
		temp->next = L0;
		temp->prior = rear;
		rear->next = temp;
		L0->prior = temp;
		rear = temp;
	}

	return OK;
}

DuLinkList Turn(DuLinkList L0, int n)
{
	DuLinkList head = L0;

	for (int i = n; i > 0; i--)
		head = head->next;
	for (int i = n; i < 0; i++)
		head = head->prior;

	return head;
}

Status Encrypt(DuLinkList &L, ElemType *str, DuLinkList L0)
{
	ElemType* curr = &str[0]; //重要！！！
	//str[1] = 't';
	//malloc之后，可以修改单个字母！(当然了，要修改一串时，用strncpy才行)
	DuLinkList temp, rear, target, cipher;
	L = (DuLinkList)malloc(sizeof(DualNode));
	if (!L) return ERROR;

	target = L0;
	while (target->lett != *curr)
		target = target->next;
	L->secret = target->secret;
	L->lett = Turn(target, target->secret)->lett;
	L->next = L;
	L->prior = L;
	rear = L;
	curr++;
	
	while (curr != NULL && *curr != '\n' && *curr != '\0')
	{
		temp = (DuLinkList)malloc(sizeof(DualNode));
		if (!temp) return ERROR;

		target = L0;
		while (target->lett != *curr)
			target = target->next;

		temp->secret = target->secret;
		temp->lett = Turn(target, target->secret)->lett;
		temp->next = L;
		temp->prior = rear;
		rear->next = temp;
		L->prior = temp;
		rear = temp;
		curr++;
	}

	return OK;
}

Status Decrypt(DuLinkList &L, DuLinkList L0)
{
	DuLinkList target, L0_target = L0;

	for (target = L; target->next != L; target = target->next)
	{
		while (target->lett != L0_target->lett)
			L0_target = L0_target->next;
		target->lett = Turn(L0_target, -target->secret)->lett;
	}

	while (target->lett != L0_target->lett)
		L0_target = L0_target->next;
	target->lett = Turn(L0_target, -target->secret)->lett;

	return OK;
}

Status Read(DuLinkList L)
{
	DuLinkList target;

	for (target = L; target->next != L; target = target->next)
		printf("%-2c", target->lett);
	printf("%-2c\n", target->lett);
	
	return OK;
}


