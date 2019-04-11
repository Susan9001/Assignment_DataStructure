#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

int main()
{
	int choice;
	SqList L;
	SLinkListType SL;

	printf("1、建立顺序表  2、读取静态表  3、直接插入排序  4、折半插入排序  5、2-路插入排序\n");
	printf("6、表插入排序  7、冒泡法排序  8、双向冒泡排序  9、快速排序\n");

	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 0)
		{
			printf("Ops!好像输错了耶~~请重新输入：\n");
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
			printf("结果为：");
			ReadSqList(L);
			break;
		case 4:
			BInsertSort(L);
			printf("结果为：");
			ReadSqList(L);
			break;
		case 5:
			TWInsertSort(L);
			printf("结果为：");
			ReadSqList(L);
			break;
		case 6:
			SLInsertSort(L);
			printf("结果为：");
			ReadSqList(L);
			break;
		case 7:
			BubbleSort(L); //单向冒泡排序
			printf("结果为：");
			ReadSqList(L);
			break;
		case 8:
			BBubleSort(L); //双向冒泡排序
			printf("结果为：");
			ReadSqList(L);
			break;
		case 9:
			QuickSort(L);
			printf("结果为：");
			ReadSqList(L);
			break;
		default:
			printf("暂未有该功能耶~~\n");
			break;
		}
	}

	return 0;
}