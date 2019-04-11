#pragma once
#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define SQMAXSIZE 20 //顺序表容量
#define SLMAXSIZE 100 //静态链表容量
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
/*二路插入排序辅助*/
typedef RedType TWList[SQMAXSIZE + 1];
/*表插入排序*/
typedef struct {
	RedType rd; //记录
	int next; //指针(下标)
}SLNode; //表结点
typedef struct {
	SLNode r[SLMAXSIZE + 1];
	int length;
}SLinkListType; //静态链表类型

/*插入排序*/
void InsertSort(SqList &L); //直接插入排序
void BInsertSort(SqList &L); //二叉排序法
void TWInsertSort(SqList &L); //二路插入排序
void SLInsertSort(SqList &L); //表插入排序
void Arrange(SLinkListType &SL); //表插入法重排关键字；
/*交换排序*/
void BubbleSort(SqList &L);
void BBubleSort(SqList &L); //双向冒泡排序
void QuickSort(SqList &L); //快速排序
void QSort(SqList &L, int low, int high); //其实可以不要你的
int Partition(SqList &L, int low, int high); //其实这个完全可以改为void的
/*其他功能函数*/
Status CreateSqList(SqList &L);
void CreateSLinkList(SqList &L, SLinkListType &SL);
void ReadSqList(SqList L); //读静态顺序表
void ReadSLinkListType(SLinkListType SL); //读静态链表
void swap(RedType &a, RedType &b);

#endif // !SORT_H_INCLUDED
