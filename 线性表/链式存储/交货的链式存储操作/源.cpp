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
Status InsertList(LinkList &L, int m, ElemType e); //在m位置之后插入元素e
Status DeletList(LinkList &L, int m); //删除位置m上的元素

int main()
{
	ElemType e, n;
	LinkList L1, L2, L3;
	int choice;

	InitList(&L1);
	printf("头结点初始化成功！\n");

	printf("\n1.查看链表\t2.创建链表（尾插法，随机生成)\t3. 删除结点\t4. 插入结点\n");
	do {
		printf("\n请选择你的操作：");
		while (scanf("%d", &choice) != 1 || choice > 12 || choice < 0)
		{
			printf("输入错了耶\n");
			while (getchar() != '\n');
		}
		switch (choice)
		{
		case 1:
			printf("第一个链表：\n");
			ViewList(&L1);
			break;
		case 2:
			printf("第一个链表：\n");
			CreatList(&L1, 15);
			break;
		case 3:
			printf("请输入要删除第一个链表的第几个结点:");
			scanf("%d", &n);
			DeletList(L1, n);
			break;
		case 4:
			printf("请输入要插入在第一个链表(位置-元素)：");
			scanf("%d-%d", &n, &e);
			InsertList(L1, n, e);
			break;
		}
	} while (choice); //0退出
	return 0;
}

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
