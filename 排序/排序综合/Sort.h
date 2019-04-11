#pragma once
#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define SQMAXSIZE 20 //˳�������
#define SLMAXSIZE 100 //��̬��������
#define MAXINT INT_MAX
#define EQ(a, b) ((a)==(b)) //a==b
#define LT(a, b) ((a)< (b)) //a < b
#define LQ(a, b) ((a)<=(b)) //a <= b

typedef int Status;
typedef int KeyType;
typedef char* InfoType;
typedef struct {
	KeyType key;
	InfoType otherinfo;
}RedType;
typedef struct {
	RedType r[SQMAXSIZE + 1];
	int lenght;
}SqList;
/*��·����������*/
typedef RedType TWList[SQMAXSIZE + 1];
/*���������*/
typedef struct {
	RedType rd; //��¼
	int next; //ָ��(�±�)
}SLNode; //����
typedef struct {
	SLNode r[SLMAXSIZE + 1];
	int length;
}SLinkListType; //��̬��������

/*��������*/
void InsertSort(SqList &L); //ֱ�Ӳ�������
void BInsertSort(SqList &L); //��������
void TWInsertSort(SqList &L); //��·��������
void SLInsertSort(SqList &L); //���������
void Arrange(SLinkListType &SL); //����뷨���Źؼ��֣�
/*��������*/
void BubbleSort(SqList &L);
void BBubleSort(SqList &L); //˫��ð������
void QuickSort(SqList &L); //��������
void QSort(SqList &L, int low, int high); //��ʵ���Բ�Ҫ���
int Partition(SqList &L, int low, int high); //��ʵ�����ȫ���Ը�Ϊvoid��
/*�������ܺ���*/
Status CreateSqList(SqList &L);
void CreateSLinkList(SqList &L, SLinkListType &SL);
void ReadSqList(SqList L); //����̬˳���
void ReadSLinkListType(SLinkListType SL); //����̬����
void swap(RedType &a, RedType &b);

#endif // !SORT_H_INCLUDED
