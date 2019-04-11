#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LinkList.h"
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

Status InitList(LinkList *L)//就一头
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

	/*声明一个指针指向节点*/
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
	printf("创建成功！\n");
}

void ViewList(LinkList *L)
{
	LinkList p;

	p = (*L)->next;
	if (!p) printf("被洗劫过了一样，空空如也耶！");
	while (p)
	{	
		printf("%-3d ", p->data);
		p = p->next;
	}
	putchar('\n');
}

int ListLen(LinkList *L)
{
	int count = 0;
	LinkList p;
	p = (LinkList)malloc(sizeof(Node));
	
	p->next = (*L)->next;
	while (p)
	{
		count++;
		p = p->next;
	}
	return count;
}

void GetMid(LinkList* L, ElemType* e)
{
	LinkList search, mid;
	mid = search = *L;
	
	while (search->next)
	{
		if (!search->next->next)
			*e = mid->next->data;
		else
		{
			mid = mid->next;
			search = search->next->next;
		}
	}
	*e = mid->data;
	printf("%d\n", *e);
}

void Order(LinkList &L)
{
	LinkList tempL = L;
	LinkList slow = L->next;
	LinkList target;
	ElemType temp;
	int len = 1, i, j;

	for (slow = L->next; slow->next; slow = slow->next)
		len++;

	for(i = 0; i < len ; i++)
	{
		target = L->next;

		for(j= 0; j < len - 1 - i; j++)
		{
			if (target->data > target->next->data)
			{
				temp = target->data;
				target->data = target->next->data;
				target->next->data = temp;
			}
			target = target->next;
		}
	}
	printf("排序后：");
	ViewList(&L);
}

void IntersectList(LinkList L1, LinkList L2, LinkList &L3)
{
	LinkList pa = L1->next, pb = L2->next, pc;
	LinkList tempL, rear = L3;

	while (pa && pb)
	{
		tempL = (LinkList)malloc(sizeof(Node));

		if (pa->data < pb->data) //要free掉小的a，并且到下一个
		{
			tempL->next = pa->next;
			//free(pa);
			pa = tempL->next;
		}
		else if (pa->data > pb->data)
			pb = pb->next;
		else if (pa->data == pb->data)
		{
			//pc->next = pa;
			//pc = pa;
			pc = (LinkList)malloc(sizeof(Node));
			pc->data = pa->data;
			rear->next = pc;
			rear = pc;
			pa = pa->next;
			pb = pb->next;
		}
	}

	//free(L2); //释放L2头结点
	//free(pa->next);
	pc->next = NULL;
	
	printf("得交集：");
	ViewList(&L3);
}

void MergeList(LinkList L1, LinkList L2, LinkList &L3)
{
	LinkList pa = L1->next, pb = L2->next, pc = L3 = L1;

	while (pa && pb)
	{
		if (pa->next && pa->data == pa->next->data)
			pa = pa->next;
		if (pb->next && pb->data == pb->next->data)
			pb = pb->next;

		if (pa->data < pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	pc->next = pa ? pa : pb;
	ViewList(&L3);
}

Status ReverseList(LinkList &L)
{
	LinkList p = L->next, q = L->next->next, temp;
	L->next->next = NULL;

	while (q)
	{
		/*头插法部分*/
		temp = q->next;
		q->next = L->next;
		L->next = q;
		q = temp;
	}

	ViewList(&L);
	return OK;
}

Status JoinList(LinkList L1, LinkList L2, LinkList &L3)
{
	LinkList p;

	if (ListLen(&L1) <= ListLen(&L2))
	{
		for (p = L3 = L1; p->next; p = p->next);
		p->next = L2->next;
	}		
	else
	{
		for (p = L3 = L2; p->next; p = p->next);
		p->next = L1->next;
	}
	
	ViewList(&L3);
	return OK;
}

Status InsertList(LinkList &L, int m, ElemType e)
{
	LinkList target = L, temp;
	int i;

	for (i = 0; i < m && target != NULL; i++)
		target = target->next;
	if (target == NULL)
	{
		printf("要插入的位置超过了链表长度！\n");
		return ERROR;
	}
	
	temp = (LinkList)malloc(sizeof(Node));
	if (!temp)
	{
		printf("分配内存失败了~~\n");
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
		printf("要删除的位置超过了链表长度！\n");
		return ERROR;
	}
	target->next = target->next->next;
	ViewList(&L);
	return OK;
}
