#ifndef CIR_H_INCLUDED
#define CIR_H_INCLUDED

typedef int ElemType;
typedef int Status;

typedef struct Node
{
	ElemType data;
	struct Node *Next;
}Node;
typedef struct Node *CirLink;

Status Init(CirLink &pNode);
Status Read(CirLink pNode);
Status Insert(CirLink &pNode, int i, ElemType e);//在i位置插入元素e
Status Delete(CirLink &pNode, int i); //返回删除了什么
int Search(CirLink pNode, ElemType e); //查找某元素的位置，返回位置

#endif // !CIR_H_INCLUDED

