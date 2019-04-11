#ifndef FOREST_H_INCLUDED
#define FOREST_H_INCLUDED

#include <stdio.h>

#define MAX_TREE_SIZE 100

typedef char ElemType;
typedef int Status;

/*树的孩子链表存储*/
typedef struct _CTNode //孩子结点
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
	int n; //结点总数
	int r; //根结点下标
}CTree;

/*树的二叉链表存储*/
typedef struct CSNode
{
	ElemType data;
	CSNode *firstchild;
	CSNode *nextsibling;
}CSNode, *CSTree;

#endif // !FOREST_H_INCLUDED
#pragma once
