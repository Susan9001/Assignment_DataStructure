#ifndef FOREST_H_INCLUDED
#define FOREST_H_INCLUDED

#include <stdio.h>

#define MAX_TREE_SIZE 100

typedef char ElemType;
typedef int Status;

/*���ĺ�������洢*/
typedef struct _CTNode //���ӽ��
{
	int child;
	struct _CTNode* next;
}*ChildPtr, CTNode;
typedef struct _CTBox
{
	ElemType data;
	CTNode* firstchild;
}CTBox;
typedef struct _CTree
{
	CTBox nodes[MAX_TREE_SIZE];
	int n; //�������
	int r; //������±�
}CTree;

/*���Ķ�������洢*/
typedef struct CSNode
{
	ElemType data;
	CSNode *firstchild;
	CSNode *nextsibling;
}CSNode, *CSTree;

#endif // !FOREST_H_INCLUDED
#pragma once
