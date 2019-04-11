#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

int main()
{
	int choice;
	SqList L;
	SLinkListType SL;

	printf("1������˳���  2����ȡ��̬��  3��ֱ�Ӳ�������  4���۰��������  5��2-·��������\n");
	printf("6�����������  7��ð�ݷ�����  8��˫��ð������  9����������\n");

	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 0)
		{
			printf("Ops!���������Ү~~���������룺\n");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			if(CreateSqList(L))
				ReadSqList(L);
			break;
		case 2:
			ReadSqList(L);
			break;
		case 3:
			InsertSort(L);
			printf("���Ϊ��");
			ReadSqList(L);
			break;
		case 4:
			BInsertSort(L);
			printf("���Ϊ��");
			ReadSqList(L);
			break;
		case 5:
			TWInsertSort(L);
			printf("���Ϊ��");
			ReadSqList(L);
			break;
		case 6:
			SLInsertSort(L);
			printf("���Ϊ��");
			ReadSqList(L);
			break;
		case 7:
			BubbleSort(L); //����ð������
			printf("���Ϊ��");
			ReadSqList(L);
			break;
		case 8:
			BBubleSort(L); //˫��ð������
			printf("���Ϊ��");
			ReadSqList(L);
			break;
		case 9:
			QuickSort(L);
			printf("���Ϊ��");
			ReadSqList(L);
			break;
		default:
			printf("��δ�иù���Ү~~\n");
			break;
		}
	}

	return 0;
}