#include <stdio.h>
#include <stdlib.h>
#include "JsHigh.h"

int main()
{
	int n, choice;
	CirLink pNode = NULL;
	printf("1、输入各个人的密码(0退出)\n");
	printf("2、查阅各人密码\n");
	printf("3、游戏过程\n");

	while (1)
	{
		printf("\n请输入操作序号吧：");
		while (scanf("%d", &choice) != 1 || choice > 5 || choice < 1)
		{
			printf("请好像输错了耶~~请重新输入：");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			n = Init(pNode);
			if (!n) printf("额~~有点小问题\n");
			break;
		case 2:
			if(!Read(pNode)) printf("Ops！好像是空链表！\n");
			break;
		case 3:
			if(!Process(pNode)) printf("Ops！好像是空链表！\n");
			break;
		}
	}

	return 0;
}