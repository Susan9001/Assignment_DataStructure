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
Status Insert(CirLink &pNode, int i, ElemType e);//��iλ�ò���Ԫ��e
Status Delete(CirLink &pNode, int i); //����ɾ����ʲô
int Search(CirLink pNode, ElemType e); //����ĳԪ�ص�λ�ã�����λ��

#endif // !CIR_H_INCLUDED

