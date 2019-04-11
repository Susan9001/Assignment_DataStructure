#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef struct ElemType 
{
	double coef; //ϵ��
	int expen; //ָ��
}ElemType;
typedef struct Node
{
	ElemType data;
	Node* next;
}Node, *LinkList;
typedef LinkList polynomial;

/*��������*/
Status InitList(LinkList &L);
Status LoceteElem(LinkList L, ElemType e, Status (*cmpP)(ElemType, ElemType)); //���ڷ���1�� �����ڷ���0
Status InsFirst(LinkList head, LinkList s);
Status SetCurElem(LinkList &curr, ElemType e);
Status DelFirst(LinkList head, LinkList &q);

/*һԪ����ʽ�Ĳ���*/
Status cmp(ElemType a, ElemType b); //a(��)����1����ȷ���0��b�󷵻�-1
Status CreatPolyn(polynomial &L, int m);
Status Read(polynomial L);
Status AddPolyn(polynomial &Pa, polynomial &Pb);

int main()
{
	polynomial La, Lb;
	int m;

	printf("�������һ������ʽ��������");
	scanf("%d", &m);
	CreatPolyn(La, m);
	printf("\n������ڶ�������ʽ��������");
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

	printf("ָ����С��������(��ϵ��-ָ��)��\n");
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
			printf("�ظ�Ү��again��");
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

		/*qa��qb�Ͳ嵽qaǰ��haŲ��qaǰqb��λ���ϣ�
		��qb��С��qaǰ��һ�������λ�ã��ٱȽ�*/
		switch (cmp(a, b))
		{
		case -1:
			ha = qa;
			qa = ha->next;
			break;
		case 0:
			sum = a.coef + b.coef;
			if (sum != 0.0) //ϵ��֮�ͷ�0
			{
				qa->data.coef = sum; //�޸�pa��ǰ�ڵ�ϵ��
				ha = qa; 
				qa = ha->next;
			}
			else //Ҫ��ϵ��������Ϊ0��qa��ҲҪɾ��
			{
				DelFirst(ha, qa); //ɾ��qa��haֱ������ԭqa->next
				free(qa);
				qa = ha->next;
			}
			DelFirst(hb, qb);//ɾ��qb��hbֱ������ԭqb->next
			free(qb);
			qb = hb->next;
			break;
		case 1:
			DelFirst(hb, qb); //��qb������b������
			InsFirst(ha, qb); //�ѹ������qb�嵽ha��qaǰ
			ha = qb; //ha = ha->nextҲ��
			qb = hb->next;
			break;
		}
	}
	if (Pb->next) //if(hb->next)Ҳ�аɣ���û�з���hb����û����~~~
		ha->next = qb; //����Pbʣ�µĽڵ�
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
