#include <stdio.h>
#include <stdlib.h>
#include "Cir.h"

int main()
{
	int choice, i;
	Status state;
	ElemType e;
	CirLink pNode = NULL;

	printf("1����ʼ��(0���)\n");
	printf("2������\t3������\n");
	printf("4��ɾ��\t5������\n");

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
			if(Init(pNode)) Read(pNode);
			else printf("��~~�е�С����\n");
			break;
		case 2:
			if (!Read(pNode)) 
				printf("��~~�е�С����\n");
			break;
		case 3:
			printf("�������ʲô�����ڵڼ��������ĺ���(��i-e)��");
			scanf("%d-%d", &i, &e);
			state = Insert(pNode, i, e);
			if (state == 0) 
				printf("��Ӵ�������ڴ�ʧ����Ү~~\n");
			else if (state == -2) 
				printf("������ĳ�����������\n");
			else if (state == 1) 
				Read(pNode);
		case 4:
			printf("����Ҫɾ�������ڼ�������");
			scanf("%d", &i);
			if(Delete(pNode, i)) 
				Read(pNode);
			else 
				printf("���Ҳ�������\n");
			break;
		case 5:
			printf("����Ҫ����ʲô����");
			scanf("%d", &e);
			if (i = Search(pNode, e))
				printf("%d�ڵ�����%d��λ��!\n", e, i);
			else 
				printf("���Ҳ�������\n");
			break;
		}
	}

	return 0;
}