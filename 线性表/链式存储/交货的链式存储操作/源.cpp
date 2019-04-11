#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;
typedef struct Node
{
	ElemType data;
	struct Node* next;
}Node, *LinkList;

Status InitList(LinkList *L);
void CreatList(LinkList *L, ElemType n);
void ViewList(LinkList *L);
Status InsertList(LinkList &L, int m, ElemType e); //��mλ��֮�����Ԫ��e
Status DeletList(LinkList &L, int m); //ɾ��λ��m�ϵ�Ԫ��

int main()
{
	ElemType e, n;
	LinkList L1, L2, L3;
	int choice;

	InitList(&L1);
	printf("ͷ����ʼ���ɹ���\n");

	printf("\n1.�鿴����\t2.��������β�巨���������)\t3. ɾ�����\t4. ������\n");
	do {
		printf("\n��ѡ����Ĳ�����");
		while (scanf("%d", &choice) != 1 || choice > 12 || choice < 0)
		{
			printf("�������Ү\n");
			while (getchar() != '\n');
		}
		switch (choice)
		{
		case 1:
			printf("��һ������\n");
			ViewList(&L1);
			break;
		case 2:
			printf("��һ������\n");
			CreatList(&L1, 15);
			break;
		case 3:
			printf("������Ҫɾ����һ������ĵڼ������:");
			scanf("%d", &n);
			DeletList(L1, n);
			break;
		case 4:
			printf("������Ҫ�����ڵ�һ������(λ��-Ԫ��)��");
			scanf("%d-%d", &n, &e);
			InsertList(L1, n, e);
			break;
		}
	} while (choice); //0�˳�
	return 0;
}

Status InitList(LinkList *L)//��һͷ
{
	*L = (LinkList)malloc(sizeof(Node));
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;
	return OK;
}




void CreatList(LinkList *L, ElemType n)
{
	LinkList p, r;
	int i, elem;
	srand(time(NULL));

	/*����һ��ָ��ָ��ڵ�*/
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	r = (*L);

	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		r->next = p;
		p->data = rand() % 40 + 1;
		r = p;
	}
	r->next = NULL;
	printf("�����ɹ���\n");
}

void ViewList(LinkList *L)
{
	LinkList p;

	p = (*L)->next;
	if (!p) printf("��ϴ�ٹ���һ�����տ���ҲҮ��");
	while (p)
	{
		printf("%-3d ", p->data);
		p = p->next;
	}
	putchar('\n');
}

Status InsertList(LinkList &L, int m, ElemType e)
{
	LinkList target = L, temp;
	int i;

	for (i = 0; i < m && target != NULL; i++)
		target = target->next;
	if (target == NULL)
	{
		printf("Ҫ�����λ�ó����������ȣ�\n");
		return ERROR;
	}

	temp = (LinkList)malloc(sizeof(Node));
	if (!temp)
	{
		printf("�����ڴ�ʧ����~~\n");
		return ERROR;
	}
	temp->data = e;
	temp->next = target->next;
	target->next = temp;
	ViewList(&L);
	return OK;
}

Status DeletList(LinkList &L, int m)
{
	LinkList target = L;
	int i;

	for (i = 1; i < m && target != NULL; i++)
		target = target->next;
	if (target == NULL)
	{
		printf("Ҫɾ����λ�ó����������ȣ�\n");
		return ERROR;
	}
	target->next = target->next->next;
	ViewList(&L);
	return OK;
}
