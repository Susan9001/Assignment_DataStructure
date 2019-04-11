#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main()
{
	MGraph MG;
	ALGraph ALG;
	OLGraph OLG;
	CSTree T;
	PathMatrix P;
	ShortPathTable D;
	PathNames PF;
	DistanceMatrix DF;
	int choice;
	char temp[MAX_VERTEX_NAME], name1[MAX_VERTEX_NAME], name2[MAX_VERTEX_NAME];

	printf("1��ʮ������(����ͼ)     2���ڽӶ��ر�(����ͼ)   3���ڽӾ���ͼ    4���ڽӱ�洢\n");
	printf("5�����������Ѱ(�ڽӱ�) 6�������������ɭ��     7�������������  8�������������ɭ��\n");
	printf("9������ķ��С������(�ڽӾ���������)    10���Ͻ�˹�������·��(�ڽӾ�����)\n");
	printf("11�������������·��(�ڽӾ�������      12�����������·��� (�ڽӱ�����ͼ)\n");
	printf("13�����������ж��Ƿ��л�(�ڽӱ�)       14�����緢��ʱ��   15������ؼ�·��\n");
	printf("16����ȱ����ж��Ƿ��л�(�ڽӱ�)");

	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 16)
		{
			printf("\n�����������Ү~~����������ѡ��");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //�����س�

		switch (choice)
		{
		case 1:
			if (CreateOLG(OLG))
				ReadOLGraph(OLG);
			break;
		case 2:
			printf("�˹�����δ�㶨�������ڴ�...\n");
			break;
		case 3:
			if(StartCreateMG(MG))
				ReadMGraph(MG);
			break;
		case 4:
			if (StartCreateALG(ALG))
				ReadALGraph(ALG);
			break;
		case 5:
			printf("������ȱ�����");
			if (!DFSTraverse_ALG(ALG))
				printf("��ѽ�����������Ѱ������Ү..\n");
			break;
		case 6:
			if (DFSForest(ALG, T))
			{
				printf("ɭ�ֵ����������");
				PreTraverse(T);
				putchar('\n');
				printf("ɭ�ֵ����������");
				InTraverse(T);
				putchar('\n');
			}
			break;
		case 9:
			printf("�����뿪ʼ�Ķ�������");
			s_gets(temp, MAX_VERTEX_NAME);
			if (!MiniSpanTree_PRIM(MG, temp))
				printf("�����Ҳ����ö���Ү~~\n");
			break;
		case 10:
			printf("������Ҫ��ʼ�Ķ�������");
			s_gets(temp, MAX_VERTEX_NAME);
			ShortestPath_DIJ(MG, temp, P, D);
			ReadShortestPath_DIJ(MG, temp, P, D);
			break;
		case 11:
			ShortestPath_FLOYD(MG, PF, DF);
			ReadShortestPath_FLOYD(MG, PF, DF);
			break;
		case 12:
			printf("������Ҫ���ҵ�����������(�ո����):");
			scanf("%s", name1);
			scanf("%s", name2);
			while (getchar() != '\n');
			if (!SearchPath(ALG, name1, name2))
				printf("�Ҳ���Ү~~\n");
			else
				putchar('\n');
			break;
		case 13:
			printf("��������");
			if (!TopologicalSort(ALG))
				printf("(�л�Ү~~)");
			putchar('\n');
			break;
		case 16:
			printf("�һ���");
			if (!SearchCircle(ALG))
				printf("ľ�л�Ү~~");
			putchar('\n');
			break;
		default:
			printf("�˹�����δ�㶨�������ڴ�...\n");
			break;
		}
	}

	return 0;
}