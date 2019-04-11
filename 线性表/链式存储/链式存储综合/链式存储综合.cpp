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
	printf("ͷ����ʼ���ɹ���\n");

	printf("\n1.�鿴����\t2.��������β�巨���������)\t3.������ \n");
	printf("4.�м���ֵ\t5.����\t\t6.�󽻼�\t7.�󲢼�(L1��L2���ᱻӰ��Ӵ)\n");
	printf("8.��ת\t\t9.������\t10.ɾ�����\t11.������\n12.�˳�\n");
	do {
		printf("\n��ѡ����Ĳ�����");
		while (scanf("%d", &choice) != 1 || choice > 12 || choice < 0)
		{
			printf("�������Ү\n");
			while (getchar() != '\n');
		}
		switch (choice)
		{
		case 1:
			printf("��һ������\n");
			ViewList(&L1); 
			printf("�ڶ�������\n");
			ViewList(&L2);
			break;
		case 2:
			printf("��һ������\n");
			CreatList(&L1, 15);
			Sleep(1500);
			printf("�ڶ�������\n");
			CreatList(&L2, 15);
			break;
		case 3:
			printf("��һ�����ܳ���Ϊ��%d!\n", ListLen(&L1));
			printf("�ڶ������ܳ���Ϊ��%d!\n", ListLen(&L2));
			break;
		case 4:
			printf("��һ�����м����");
			GetMid(&L1, &e);
			printf("�ڶ������м����");
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
			printf("������Ҫɾ����һ������ĵڼ������:");
			scanf("%d", &n);
			DeletList(L1, n);
			break;
		case 11:
			printf("������Ҫ�����ڵ�һ������(λ��-Ԫ��)��");
			scanf("%d-%d", &n, &e);
			InsertList(L1, n, e);
			break;
		}

	} while (choice);

	return 0;
}
