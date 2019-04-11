#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node* next;
}Node, *LinkList;

Status InitList(LinkList *L);
int ListLen(LinkList *L);
void CreatList(LinkList *L, ElemType n);
void ViewList(LinkList *L);
void GetMid(LinkList *L, ElemType *e);
void Order(LinkList &L);
void IntersectList(LinkList L1, LinkList L2, LinkList &L3);
void MergeList(LinkList L1, LinkList L2, LinkList &L3);
Status ReverseList(LinkList &L);
Status JoinList(LinkList L1, LinkList L2, LinkList &L3);
Status InsertList(LinkList &L, int m, ElemType e); //在m位置之后插入元素e
Status DeletList(LinkList &L, int m); //删除位置m上的元素

#endif // !LINKLIST_H_INCLUDED

