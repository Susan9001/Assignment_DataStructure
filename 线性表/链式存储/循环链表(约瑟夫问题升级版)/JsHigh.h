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

int Init(CirLink &pNode); //初始化链表，输入密码给每人，返回一共多少元素
Status Read(CirLink pNode);
Status Process(CirLink &pNode);//打印出每次出局者的编号

#endif // !JSHIGH_H_INCLUDED

