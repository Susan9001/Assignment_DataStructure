#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "LinkList.h"

int main()
{
	ElemType e, n;
	LinkList L1, L2, L3;
	int choice;

	InitList(&L1);
	InitList(&L2);
	InitList(&L3);
	printf("头结点初始化成功！\n");

	printf("\n1.查看链表\t2.创建链表（尾插法，随机生成)\t3.链表长度 \n");
	printf("4.中间结点值\t5.排序\t\t6.求交集\t7.求并集(L1、L2都会被影响哟)\n");
	printf("8.反转\t\t9.简单连接\t10.删除结点\t11.插入结点\n12.退出\n");
	do {
		printf("\n请选择你的操作：");
		while (scanf("%d", &choice) != 1 || choice > 12 || choice < 0)
		{
			printf("输入错了耶\n");
			while (getchar() != '\n');
		}
		switch (choice)
		{
		case 1:
			printf("第一个链表：\n");
			ViewList(&L1); 
			printf("第二个链表：\n");
			ViewList(&L2);
			break;
		case 2:
			printf("第一个链表：\n");
			CreatList(&L1, 15);
			Sleep(1500);
			printf("第二个链表：\n");
			CreatList(&L2, 15);
			break;
		case 3:
			printf("第一个的总长度为：%d!\n", ListLen(&L1));
			printf("第二个的总长度为：%d!\n", ListLen(&L2));
			break;
		case 4:
			printf("第一个最中间的数");
			GetMid(&L1, &e);
			printf("第二个最中间的数");
			GetMid(&L2, &e);
			break;
		case 5:
			Order(L1);
			Order(L2);
			putchar('\n');
			break;
		case 6:
			IntersectList(L1, L2, L3);
			break;
		case 7:
			MergeList(L1, L2, L3);
			break;
		case 8:
			ReverseList(L1);
			ReverseList(L2);
			break;
		case 9:
			JoinList(L1, L2, L3);
			break;
		case 10:
			printf("请输入要删除第一个链表的第几个结点:");
			scanf("%d", &n);
			DeletList(L1, n);
			break;
		case 11:
			printf("请输入要插入在第一个链表(位置-元素)：");
			scanf("%d-%d", &n, &e);
			InsertList(L1, n, e);
			break;
		}

	} while (choice);

	return 0;
}
