#include <stdio.h>
#include <stdlib.h>
#include "JsHigh.h"

int main()
{
	int n, choice;
	CirLink pNode = NULL;
	printf("1����������˵�����(0�˳�)\n");
	printf("2�����ĸ�������\n");
	printf("3����Ϸ����\n");

	while (1)
	{
		printf("\n�����������Űɣ�");
		while (scanf("%d", &choice) != 1 || choice > 5 || choice < 1)
		{
			printf("����������Ү~~���������룺");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			n = Init(pNode);
			if (!n) printf("��~~�е�С����\n");
			break;
		case 2:
			if(!Read(pNode)) printf("Ops�������ǿ�����\n");
			break;
		case 3:
			if(!Process(pNode)) printf("Ops�������ǿ�����\n");
			break;
		}
	}

	return 0;
}