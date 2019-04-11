#include <stdio.h>
#include <stdlib.h>
#include "Cir.h"

int main()
{
	int choice, i;
	Status state;
	ElemType e;
	CirLink pNode = NULL;

	printf("1、初始化(0完成)\n");
	printf("2、遍历\t3、插入\n");
	printf("4、删除\t5、查找\n");

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
			if(Init(pNode)) Read(pNode);
			else printf("额~~有点小问题\n");
			break;
		case 2:
			if (!Read(pNode)) 
				printf("额~~有点小问题\n");
			break;
		case 3:
			printf("请输入把什么数放在第几个倒数的后面(如i-e)：");
			scanf("%d-%d", &i, &e);
			state = Insert(pNode, i, e);
			if (state == 0) 
				printf("哎哟，分配内存失败了耶~~\n");
			else if (state == -2) 
				printf("您输入的超出长度啦！\n");
			else if (state == 1) 
				Read(pNode);
		case 4:
			printf("请问要删除倒数第几个数：");
			scanf("%d", &i);
			if(Delete(pNode, i)) 
				Read(pNode);
			else 
				printf("您找不到啦！\n");
			break;
		case 5:
			printf("请问要查找什么数：");
			scanf("%d", &e);
			if (i = Search(pNode, e))
				printf("%d在倒数第%d个位置!\n", e, i);
			else 
				printf("您找不到啦！\n");
			break;
		}
	}

	return 0;
}