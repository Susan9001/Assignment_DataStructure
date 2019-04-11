#include <stdio.h>
#include <stdlib.h>
#include "Triple.h"

int main()
{
	int choice, i, e;
	ElemType v1, v2, v3;
	Triple T = NULL;

	printf("1、初始化\t\t2、销毁\n");
	printf("3、查找第i个元素的值\t4、替换第i个元素的值\n");
	printf("5、判断升序\t\t6、判断降序\n");
	printf("7、最大值\t\t8、最小值\n");

	while(1)
	{
		printf("\n请输入您的选择：");
		while(scanf("%d", &choice) != 1 || choice < 1 || choice > 8)
		{
			printf("输入有问题也，请重新输入：");
			while(getchar() != '\n');
		}

		switch(choice)
		{
		case 1:
			printf("请分别输入三个数：（如1-2-3）");
			scanf("%d-%d-%d", &v1, &v2, &v3);
			if (InitTriple(T, v1, v2, v3)) printf("成功！\n");
			break;
		case 2:
			if(DestroyTriple(T)) printf("销毁成功！\n");;
			break;
		case 3:
			printf("请分别输入要查找第几个：");
			scanf("%d", &i);
			if (Get(T, i, &e)) printf("找到啦！为：%d\n", e);
			else printf("请输入1,2,3中的一个！\n");
			break;
		case 4:
			printf("请输入要把第i个元素替换为e(格式如i-e)：");
			scanf("%d-%d", &i, &e);
			if(Put(T, i, e)) printf("替换成功！\n");
			break;
		case 5:
			if (IsAscending(T)) printf("是升序！\n");
			else printf("并非升序！\n");
			break;
		case 6:
			if (IsDescending(T)) printf("是降序！\n");
			else printf("并非降序！\n");
			break;
		case 7:
			if(Max(T, &e)) printf("得到最大为：%d\n", e);
			break;
		case 8:
			if(Min(T, &e)) printf("得到最小为：%d\n", e);
			break;
		}
	}
	
	return 0;
}