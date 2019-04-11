#include <stdio.h>
#include <stdlib.h>
#include "Triple.h"

int main()
{
	int choice, i, e;
	ElemType v1, v2, v3;
	Triple T = NULL;

	printf("1����ʼ��\t\t2������\n");
	printf("3�����ҵ�i��Ԫ�ص�ֵ\t4���滻��i��Ԫ�ص�ֵ\n");
	printf("5���ж�����\t\t6���жϽ���\n");
	printf("7�����ֵ\t\t8����Сֵ\n");

	while(1)
	{
		printf("\n����������ѡ��");
		while(scanf("%d", &choice) != 1 || choice < 1 || choice > 8)
		{
			printf("����������Ҳ�����������룺");
			while(getchar() != '\n');
		}

		switch(choice)
		{
		case 1:
			printf("��ֱ�����������������1-2-3��");
			scanf("%d-%d-%d", &v1, &v2, &v3);
			if (InitTriple(T, v1, v2, v3)) printf("�ɹ���\n");
			break;
		case 2:
			if(DestroyTriple(T)) printf("���ٳɹ���\n");;
			break;
		case 3:
			printf("��ֱ�����Ҫ���ҵڼ�����");
			scanf("%d", &i);
			if (Get(T, i, &e)) printf("�ҵ�����Ϊ��%d\n", e);
			else printf("������1,2,3�е�һ����\n");
			break;
		case 4:
			printf("������Ҫ�ѵ�i��Ԫ���滻Ϊe(��ʽ��i-e)��");
			scanf("%d-%d", &i, &e);
			if(Put(T, i, e)) printf("�滻�ɹ���\n");
			break;
		case 5:
			if (IsAscending(T)) printf("������\n");
			else printf("��������\n");
			break;
		case 6:
			if (IsDescending(T)) printf("�ǽ���\n");
			else printf("���ǽ���\n");
			break;
		case 7:
			if(Max(T, &e)) printf("�õ����Ϊ��%d\n", e);
			break;
		case 8:
			if(Min(T, &e)) printf("�õ���СΪ��%d\n", e);
			break;
		}
	}
	
	return 0;
}