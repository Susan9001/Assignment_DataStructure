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

	printf("1、十字链表(有向图)     2、邻接多重表(无向图)   3、邻接矩阵图    4、邻接表存储\n");
	printf("5、深度优先搜寻(邻接表) 6、深度优先生成森林     7、广度优先搜索  8、广度优先生成森林\n");
	printf("9、普里姆最小生成树(邻接矩阵，无向网)    10、迪杰斯特拉最短路径(邻接矩阵，网)\n");
	printf("11、佛洛依德最短路径(邻接矩阵，网）      12、搜索两点间路与否 (邻接表，有向图)\n");
	printf("13、拓扑排序及判断是否有环(邻接表)       14、最早发生时间   15、输出关键路径\n");
	printf("16、深度遍历判断是否有环(邻接表)");

	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 16)
		{
			printf("\n好像输入错误耶~~请重新输入选择：");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //消除回车

		switch (choice)
		{
		case 1:
			if (CreateOLG(OLG))
				ReadOLGraph(OLG);
			break;
		case 2:
			printf("此功能暂未搞定，敬请期待...\n");
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
			printf("深度优先遍历：");
			if (!DFSTraverse_ALG(ALG))
				printf("哎呀，深度优先搜寻出错了耶..\n");
			break;
		case 6:
			if (DFSForest(ALG, T))
			{
				printf("森林的先序遍历：");
				PreTraverse(T);
				putchar('\n');
				printf("森林的中序遍历：");
				InTraverse(T);
				putchar('\n');
			}
			break;
		case 9:
			printf("请输入开始的顶点名：");
			s_gets(temp, MAX_VERTEX_NAME);
			if (!MiniSpanTree_PRIM(MG, temp))
				printf("好像找不到该顶点耶~~\n");
			break;
		case 10:
			printf("请输入要开始的顶点名：");
			s_gets(temp, MAX_VERTEX_NAME);
			ShortestPath_DIJ(MG, temp, P, D);
			ReadShortestPath_DIJ(MG, temp, P, D);
			break;
		case 11:
			ShortestPath_FLOYD(MG, PF, DF);
			ReadShortestPath_FLOYD(MG, PF, DF);
			break;
		case 12:
			printf("请输入要查找的两个顶点名(空格隔开):");
			scanf("%s", name1);
			scanf("%s", name2);
			while (getchar() != '\n');
			if (!SearchPath(ALG, name1, name2))
				printf("找不到耶~~\n");
			else
				putchar('\n');
			break;
		case 13:
			printf("拓扑排序：");
			if (!TopologicalSort(ALG))
				printf("(有环耶~~)");
			putchar('\n');
			break;
		case 16:
			printf("找环：");
			if (!SearchCircle(ALG))
				printf("木有环耶~~");
			putchar('\n');
			break;
		default:
			printf("此功能暂未搞定，敬请期待...\n");
			break;
		}
	}

	return 0;
}