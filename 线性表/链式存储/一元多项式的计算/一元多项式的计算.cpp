#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef struct ElemType 
{
	double coef; //系数
	int expen; //指数
}ElemType;
typedef struct Node
{
	ElemType data;
	Node* next;
}Node, *LinkList;
typedef LinkList polynomial;

/*基本操作*/
Status InitList(LinkList &L);
Status LoceteElem(LinkList L, ElemType e, Status (*cmpP)(ElemType, ElemType)); //存在返回1， 不存在返回0
Status InsFirst(LinkList head, LinkList s);
Status SetCurElem(LinkList &curr, ElemType e);
Status DelFirst(LinkList head, LinkList &q);

/*一元多项式的操作*/
Status cmp(ElemType a, ElemType b); //a(大)返回1，相等返回0，b大返回-1
Status CreatPolyn(polynomial &L, int m);
Status Read(polynomial L);
Status AddPolyn(polynomial &Pa, polynomial &Pb);

int main()
{
	polynomial La, Lb;
	int m;

	printf("请输入第一个多项式的项数：");
	scanf("%d", &m);
	CreatPolyn(La, m);
	printf("\n请输入第二个多项式的项数：");
	scanf("%d", &m);
	CreatPolyn(Lb, m);

	AddPolyn(La, Lb);
	Read(La);

	return 0;
}

Status CreatPolyn(polynomial &L, int m)
{
	InitList(L);
	LinkList curr = L, rear = L;
	ElemType e = { 0, -1 };
	int i;
	curr->data = e;

	printf("指数由小到大输入(如系数-指数)：\n");
	for (i = 0; i < m; i++)
	{
		scanf("%lf-%d", &e.coef, &e.expen);
		if (!LoceteElem(L, e, cmp))
		{
			curr = (LinkList)malloc(sizeof(Node));
			if (!curr) return OVERFLOW;
			curr->data = e;
			InsFirst(rear, curr);
			rear = curr;
		}
		else
		{
			printf("重复耶，again：");
			i--;
		}
	}
	
	return OK;
}

Status AddPolyn(polynomial &Pa, polynomial &Pb)
{
	polynomial ha = Pa, hb = Pb;
	polynomial qa = ha->next, qb = hb->next;
	double sum;

	while (qa && qb)
	{
		ElemType a = qa->data, b = qb->data;

		/*qa大，qb就插到qa前，ha挪到qa前qb的位置上；
		当qb大，小的qa前进一个更大的位置，再比较*/
		switch (cmp(a, b))
		{
		case -1:
			ha = qa;
			qa = ha->next;
			break;
		case 0:
			sum = a.coef + b.coef;
			if (sum != 0.0) //系数之和非0
			{
				qa->data.coef = sum; //修改pa当前节点系数
				ha = qa; 
				qa = ha->next;
			}
			else //要是系数加起来为0，qa里也要删除
			{
				DelFirst(ha, qa); //删了qa，ha直接连到原qa->next
				free(qa);
				qa = ha->next;
			}
			DelFirst(hb, qb);//删了qb，hb直接连到原qb->next
			free(qb);
			qb = hb->next;
			break;
		case 1:
			DelFirst(hb, qb); //把qb跟链表b孤立开
			InsFirst(ha, qb); //把孤立后的qb插到ha后，qa前
			ha = qb; //ha = ha->next也行
			qb = hb->next;
			break;
		}
	}
	if (Pb->next) //if(hb->next)也行吧，有没有发现hb根本没动过~~~
		ha->next = qb; //链接Pb剩下的节点
	free(hb);

	return OK;
}

Status Read(polynomial L)
{
	polynomial curr = L;
	printf("\nf(x) = ");
	for (curr = L->next; curr!= NULL;curr = curr->next)
		printf("%.2lf x^%d + ", curr->data.coef, curr->data.expen);
	printf("\b\b \n\n");
	return OK;
}

Status InitList(LinkList &L)
{
	L = (LinkList)malloc(sizeof(Node));
	if (!L) return OVERFLOW;
	L->next = NULL;
	return OK;
}

Status LoceteElem(LinkList L, ElemType e, Status (*cmpP)(ElemType, ElemType))
{
	LinkList target = L;

	for (target = L; target != NULL; target = target->next)
		if (fabs(target->data.coef - e.coef)< 0.0001 && abs(target->data.expen - e.expen) < 0.0001) break;
	
	if (target == NULL) return 0;
	else return OK;
}

Status InsFirst(LinkList head, LinkList s)
{
	s->next = head->next;
	head->next = s;
	return OK;
}

Status DelFirst(LinkList head, LinkList &q)
{
	q = head->next;
	head->next = head->next->next;
	return OK;
}

Status SetCurElem(LinkList &curr, ElemType e)
{
	curr->data = e;
	return OK;
}

Status cmp(ElemType a, ElemType b)
{
	if (a.expen < b.expen) return -1;
	else if (a.expen == b.expen) return 0;
	else return 1;
}
