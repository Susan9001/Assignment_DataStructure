#ifndef JSHIGH_H_INCLUDED
#define JSHIGH_H_INCLUDED

typedef int Status;
typedef int ElemType;

typedef struct Node
{
	ElemType secret;
	ElemType num;
	struct Node *next;
}Node;
typedef struct Node *CirLink;

int Init(CirLink &pNode); //��ʼ���������������ÿ�ˣ�����һ������Ԫ��
Status Read(CirLink pNode);
Status Process(CirLink &pNode);//��ӡ��ÿ�γ����ߵı��

#endif // !JSHIGH_H_INCLUDED

