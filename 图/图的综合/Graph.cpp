#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

Status StartCreateMG(MGraph &MG)
{
	int choice;

	printf("1、有向图  2、有向网  3、无向图  4、无向网\n");
	printf("请输入选择：");
	while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
	{
		printf("输错了耶，请重新输入您的选择：");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	switch (choice)
	{
	case 1:
		MG.kind = DG;
		return CreateMG(MG);
	case 2:
		MG.kind = DN;
		return CreateMG(MG);
	case 3:
		MG.kind = UDG;
		return CreateMG(MG);
	case 4:
		MG.kind = UDN;
		return CreateMG(MG);
	default:
		return ERROR;
	}
}

Status CreateMG(MGraph &MG) //图
{
	int i, j, k, w, AutoOrNot; //w为权值
	char IncInfo;
	char temp[MAX_VERTEX_NAME * 2 + 5];
	char* temp1 = NULL, *temp2 = NULL;

	printf("请输入顶点数-弧数-是否含弧的其他信息(Y是,其他否):");
	scanf("%d-%d-%c", &MG.vexnum, &MG.arcnum, &IncInfo);
	while (getchar() != '\n');

	printf("生成名字(从0/1/65(A)开始/手动输入任意字符)：");
	scanf("%d", &AutoOrNot);
	while (getchar() != '\n');
	switch (AutoOrNot)
	{
	case 0:case 1:
		printf("所起的名字为：");
		for (i = 0; i < MG.vexnum; i++)
		{
			sprintf(MG.vexs[i], "%c%d", 'v', i + AutoOrNot);
			printf("%-4s", MG.vexs[i]);
			for (j = 0; j < MG.vexnum; j++)
				MG.arcs[i][j].adj = INFINITY;
		}
		putchar('\n');
		break;
	case 65:
		printf("所起的名字为：");
		for (i = 0; i < MG.vexnum; i++)
		{
			sprintf(MG.vexs[i], "%c", 'A' + i);
			printf("%-4s", MG.vexs[i]);
			for (j = 0; j < MG.vexnum; j++)
				MG.arcs[i][j].adj = INFINITY;
		}
		putchar('\n');
		break;
	default:
		printf("请输入%d个顶点的名字(空格隔开)：", MG.vexnum);
		for (i = 0; i < MG.vexnum; i++)
		{
			scanf("%s", MG.vexs[i]);
			for (j = 0; j < MG.vexnum; j++)
				MG.arcs[i][j].adj = INFINITY;
		}
		while (getchar() != '\n');
		break;
	}

	for (k = 0; k < MG.arcnum; k++)
	{
		if (MG.kind == UDG || MG.kind == DG)
		{
			printf("请输入第%d条弧尾-头的名字：", k + 1);
			scanf("%s", temp);
			i = LocateMGVex(MG, strtok(temp, "-"));
			j = LocateMGVex(MG, strtok(NULL, "-"));
			w = 1;
		}
		else
		{
			printf("请输入第%d条弧尾-头-w(权值)：", k + 1);
			scanf("%s", temp);
			i = LocateMGVex(MG, strtok(temp, "-"));
			j = LocateMGVex(MG, strtok(NULL, "-"));
			w = atoi(strtok(NULL, "-"));
		}
		
		MG.arcs[i][j].adj = w;
		while (getchar() != '\n');
		
		if (IncInfo == 'y' || IncInfo == 'Y')
		{
			printf("请输入顶点信息：");
			MG.arcs[i][j].info = (InfoType*)malloc(sizeof(InfoType) * MAX_ARC_INFO);
			s_gets(MG.arcs[i][j].info, MAX_ARC_INFO);
		}
		if(MG.kind == UDG || MG.kind == UDN)
			MG.arcs[j][i].adj = MG.arcs[i][j].adj;
	}

	return OK;
}

int LocateMGVex(MGraph MG, char* v)
{
	for (int i = 0; i < MG.vexnum; i++)
	{
		if (!strcmp(MG.vexs[i], v))
			return i;
	}

	return OVERFLOW; //-2，不能是0啊~~
}

Status ReadMGraph(MGraph MG)
{
	printf("顶点%d个弧%d条\n\t", MG.vexnum, MG.arcnum);
	for (int i = 0; i < MG.vexnum; i++)
		printf("%s\t", MG.vexs[i]);
	for (int i = 0; i < MG.vexnum; i++)
	{
		printf("\n%s\t", MG.vexs[i]);
		for (int j = 0; j < MG.vexnum; j++)
		{
			if (MG.arcs[i][j].adj != INFINITY)
				printf("%d\t", MG.arcs[i][j].adj);
			else
				printf("#\t");
		}
	}
	putchar('\n');
	return OK;
}

Status StartCreateALG(ALGraph &ALG)
{
	int choice;

	printf("1、有向图  2、有向网  3、无向图  4、无向网\n");
	printf("请输入选择：");
	while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
	{
		printf("输错了耶，请重新输入您的选择：");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	switch (choice)
	{
	case 1:
		ALG.kind = DG;
		return CreateALG(ALG);
	case 2:
		ALG.kind = DN;
		return CreateALG(ALG);
	case 3:
		ALG.kind = UDG;
		return CreateALG(ALG);
	case 4:
		ALG.kind = UDN;
		return CreateALG(ALG);
	default:
		return ERROR;
	}
}

Status CreateALG(ALGraph &ALG)
{
	int i, j, k, w,AutoOrNot; //w为权值
	char IncInfo;
	char temp[MAX_VERTEX_NAME * 2 + 5];
	ArcNode*p = NULL, *q = NULL;

	printf("请输入顶点数-弧数-是否含弧的其他信息(Y是,其他否):");
	scanf("%d-%d-%c", &ALG.vexnum, &ALG.arcnum, &IncInfo);
	while (getchar() != '\n');

	printf("生成名字(输入0/1/65(A)开始/手动输入任意字符)：");
	scanf("%d", &AutoOrNot);
	while (getchar() != '\n');
	switch (AutoOrNot)
	{
	case 1:case 0:
		printf("所起的名字为：");
		for (i = 0; i < ALG.vexnum; i++)
		{
			sprintf(ALG.vertices[i].data, "%c%d", 'v', i + AutoOrNot);
			printf("%-4s", ALG.vertices[i].data);
			ALG.vertices[i].firstarc = NULL;
		}
		putchar('\n');
		break;
	case 65:
		printf("所起的名字为：");
		for (i = 0; i < ALG.vexnum; i++)
		{
			sprintf(ALG.vertices[i].data, "%c", i + AutoOrNot);
			printf("%-4s", ALG.vertices[i].data);
			ALG.vertices[i].firstarc = NULL;
		}
		putchar('\n');
		break;
	default:
		printf("请输入%d个顶点的名字(空格隔开)：", ALG.vexnum);
		for (i = 0; i < ALG.vexnum; i++)
		{
			scanf("%s", ALG.vertices[i].data);
			ALG.vertices[i].firstarc = NULL;
		}
		while (getchar() != '\n');
		break;
	}

	for (k = 0; k < ALG.arcnum; k++)
	{
		switch (ALG.kind)
		{
		case UDG: case DG:
			printf("请输入第%d条弧尾-头的名字：", k + 1);
			scanf("%s", temp);
			i = LocateALGVex(ALG, strtok(temp, "-"));
			j = LocateALGVex(ALG, strtok(NULL, "-"));
			w = 1;
			break;
		case UDN: case DN:
			printf("请输入第%d条弧尾-头-w(权值)：", k + 1);
			scanf("%s", temp);
			i = LocateALGVex(ALG, strtok(temp, "-"));
			j = LocateALGVex(ALG, strtok(NULL, "-"));
			w = atoi(strtok(NULL, "-"));
			break;
		default:
			return ERROR;
		}
		while (getchar() != '\n');

		p = (ArcNode*)malloc(sizeof(ArcNode));
		if (!p) return ERROR;
		*p = { ALG.vertices[i].firstarc, j, w, NULL }; //以下两步为关键！
		ALG.vertices[i].firstarc = p;
		if (IncInfo == 'y' || IncInfo == 'Y')
		{
			printf("请输入顶点信息：");
			p->info = (char*)malloc(sizeof(InfoType) * MAX_ARC_INFO);
			s_gets(p->info, MAX_ARC_INFO);
		}

		if (ALG.kind == UDG || ALG.kind == UDN) //无向的情况
		{
			q = (ArcNode*)malloc(sizeof(ArcNode));
			*q = { ALG.vertices[j].firstarc, i, w, NULL };
			ALG.vertices[j].firstarc = q;
			q->info = p->info; //指向p
		}//if
	}//for
	return OK;
}

int LocateALGVex(ALGraph ALG, char* v)
{
	for (int i = 0; i < ALG.vexnum; i++)
	{
		if (!strcmp(ALG.vertices[i].data, v))
			return i;
	}
	return OVERFLOW;
}

Status ReadALGraph(ALGraph ALG)
{
	ArcNode* p;

	printf("\n顶点%d个，弧%d条\n", ALG.vexnum, ALG.arcnum);
	
	if (ALG.kind == DN || ALG.kind == UDN) printf("[权值-所指顶点(名)]\n");;
	for (int i = 0; i < ALG.vexnum; i++)
	{
		printf("%d.%s", i, ALG.vertices[i].data);
		if (ALG.kind == UDG || ALG.kind == DG)
		{
			for (p = ALG.vertices[i].firstarc; p != NULL; p = p->nextarc)
				printf(" ->%d(%s)", p->adjvex, ALG.vertices[p->adjvex].data);
		}
		else
		{
			
			for (p = ALG.vertices[i].firstarc; p != NULL; p = p->nextarc)
				printf("->[%d, %d(%s)]", p->weight, p->adjvex, ALG.vertices[p->adjvex].data);
		}
		putchar('\n');
	}
	return OK;
}

Status CreateOLG(OLGraph &OLG)
{
	int i, j, k, w, AutoOrNot; //w为权值
	char IncInfo;
	char temp[MAX_VERTEX_NAME * 2 + 5];
	ArcNode*p = NULL, *q = NULL;

	printf("请输入顶点数-弧数-是否含弧的其他信息(Y是,其他否):");
	scanf("%d-%d-%c", &OLG.vexnum, &OLG.arcnum, &IncInfo);
	while (getchar() != '\n');

	printf("自动生成名字(开始v0/v1/手动输入任意字符)：");
	scanf("%d", &AutoOrNot);
	while (getchar() != '\n');
	switch (AutoOrNot)
	{
	case 1:case 0:
		printf("所起的名字：");
		for (i = 0; i < OLG.vexnum; i++)
		{
			sprintf(OLG.xlist[i].data, "%c%d", 'v', i + AutoOrNot);
			printf("%-4s", OLG.xlist[i].data);
			OLG.xlist[i].firstin = OLG.xlist[i].firstout = NULL;
		}
		putchar('\n');
		break;
	default:
		printf("请输入%d个顶点的名字(空格隔开)：", OLG.vexnum);
		for (i = 0; i < OLG.vexnum; i++)
		{
			scanf("%s", OLG.xlist[i].data);
			OLG.xlist[i].firstin = OLG.xlist[i].firstout = NULL;
		}
		while (getchar() != '\n');
		break;
	}

	for (k = 0; k < OLG.arcnum; k++)
	{
		printf("请输入第%d条弧尾-头的名字：", k + 1);
		s_gets(temp, MAX_VERTEX_NAME);
		i = LocateOLGVex(OLG, strtok(temp, "-"));
		j = LocateOLGVex(OLG, strtok(NULL, "-"));
		ArcBox *p = (ArcBox*)malloc(sizeof(ArcBox));
		if (!p) return ERROR;
		*p = { i, j, OLG.xlist[j].firstin, OLG.xlist[i].firstout, NULL };
		OLG.xlist[j].firstin = OLG.xlist[i].firstout = p; //不要在多个->hlink啦！！！
		if (IncInfo == 'Y' || IncInfo == 'y')
		{
			printf("请输入顶点信息：");
			p->info = (char*)malloc(sizeof(InfoType) * MAX_ARC_INFO);
			s_gets(p->info, MAX_ARC_INFO);
		}
	}
}

int LocateOLGVex(OLGraph OLG, char* v)
{
	for (int i = 0; i < OLG.vexnum; i++)
	{
		if (!strcmp(OLG.xlist[i].data, v))
			return i;
	}
	return OVERFLOW;
}

Status ReadOLGraph(OLGraph OLG)
{
	ArcBox* p;

	printf("顶点%d个，弧%d条", OLG.vexnum, OLG.arcnum);

	for (int i = 0; i < OLG.vexnum; i++)
	{
		printf("\n%d.%s(第一入弧:%x): ", i + 1, OLG.xlist[i].data, OLG.xlist[i].firstin);
		for (p = OLG.xlist[i].firstout; p; p = p->tlink)
			printf("%x(%d, %d, 同头%x)->", p, p->tail, p->head, p->hlink);
		printf("\b\b  ");
	}
	putchar('\n');
	return OK;
}

Status DFSTraverse_ALG(ALGraph ALG)
{
	int* visited = (int*)malloc(sizeof(int) * ALG.vexnum);
	if (!visited) return ERROR;

	for (int v = 0; v < ALG.vexnum; v++) visited[v] = 0;
	for (int v = 0; v < ALG.vexnum; v++)
	{
		if (!visited[v]) 
			DFS_ALG(ALG, visited, v);
	}
	putchar('\n');

	return OK;
}

void DFS_ALG(ALGraph ALG, int *visited, int v)
{
	ArcNode* p;

	Visit(ALG.vertices[v]);
	visited[v] = 1; //1表示访问过了

	for (p = ALG.vertices[v].firstarc; p != NULL; p = p->nextarc)
	{
		if (!visited[p->adjvex]) 
			DFS_ALG(ALG, visited, p->adjvex);
	}
}

Status DFSForest(ALGraph ALG, CSTree &T)
{
	int *visited = (int*)malloc(sizeof(int) * ALG.vexnum);
	CSTree p, q;
	if (!visited) return ERROR;
	T = NULL;

	for (int v = 0; v < ALG.vexnum; v++) visited[v] = 0;
	for (int v = 0; v < ALG.vexnum; v++)
	{
		if (!visited[v])
		{
			p = (CSTree)malloc(sizeof(CSNode));
			*p = { ALG.vertices[v], NULL, NULL };
			if (!T) T = p;
			else q->nextsibling = p;
			q = p; //q永远保持在上一个p的位置
			DFSTree(ALG, v, q, visited);
		}
	}

	return OK;
}

Status DFSTree(ALGraph ALG, int v, CSTree &T, int* visited)
{
	ArcNode *arcOfv; //作为循环变量，指向v点各个弧指针
	CSTree p, q;
	int first = 1; //表示这个arcOfv指的是v结点的第条邻接弧，也就是第一个循环
	
	visited[v] = 1;
	for (arcOfv = ALG.vertices[v].firstarc; arcOfv != NULL; arcOfv = arcOfv->nextarc)
	{
		if (!visited[arcOfv->adjvex]) //w = arcOfv->adjvex
		{
			p = (CSTree)malloc(sizeof(CSNode));
			if (!p) return ERROR;
			*p = { ALG.vertices[arcOfv->adjvex], NULL, NULL };
			if (first)
			{
				T->lchild = p;
				first = 0;
			}
			else
			{
				q->nextsibling = p;
			}
			q = p; //同前，q永远保持在上一个p的位置
			DFSTree(ALG, arcOfv->adjvex, q, visited);
		}
	}

	return OK;
}

Status PreTraverse(CSTree T)
{
	if (T)
	{
		Visit(T->data);
		if (PreTraverse(T->lchild))
			if (PreTraverse(T->nextsibling))
				return OK;
		return ERROR;
	}
	return OK;
}

Status InTraverse(CSTree T)
{
	if (T)
	{
		InTraverse(T->lchild);
		Visit(T->data);
		InTraverse(T->nextsibling);
		return OK;
	}
	return OK;
}

Status MiniSpanTree_PRIM(MGraph MG, VertexType target)
{
	int i, j, k;
	char temp[MAX_VERTEX_NAME];
	Closedge closedge;

	k = LocateMGVex(MG, target);
	if (k < 0) return ERROR;
	for (i = 0; i < MG.vexnum; i++)
	{
		strncpy(closedge[i].vexName, target, MAX_VERTEX_NAME);
		closedge[i].lowcost = MG.arcs[k][i].adj;
	}
	closedge[k].lowcost = 0;

	printf("最小生成树为：");
	for (i = 0; i < MG.vexnum - 1; i++)
	{
		k = minimum(closedge, MG.vexnum);
		printf("%s-%s(%d), ", closedge[k].vexName, MG.vexs[k], closedge[k].lowcost);
		closedge[k].lowcost = 0; //事先再closedge里面调到最小
		for (j = 0; j < MG.vexnum; j++)
		{
			if (MG.arcs[k][j].adj < closedge[j].lowcost) //前新k，后closedge的仍是旧k
			{
				closedge[j].lowcost = MG.arcs[k][j].adj;
				strcpy(closedge[j].vexName, MG.vexs[k]);
			}
		}//for j
	}//for k,i
	putchar('\n');

	return OK;
}

int minimum(Closedge closedge, int vexnum)
{
	int k, i;
	for (i = 0, k = 0; i < vexnum; i++)
	{
		if (closedge[i].lowcost != 0 && (closedge[i].lowcost < closedge[k].lowcost || closedge[k].lowcost == 0))
			k = i;
	}
	return k;
}

void ShortestPath_DIJ(MGraph MG, char* v0_name, PathMatrix &P, ShortPathTable &D)
{
	int v, w, i, j;
	int min;
	int v0 = LocateMGVex(MG, v0_name);
	int *finall = (int*)malloc(sizeof(int) * MG.vexnum); //表示已经求得v0到下标v的最短路了
	P = (int**)malloc(sizeof(int*) * MG.vexnum);
	for (i = 0; i < MG.vexnum; i++)
		P[i] = (int*)malloc(sizeof(int) * MG.vexnum);
	D = (int*)malloc(sizeof(int) * MG.vexnum);
	
	//初始化
	for (v = 0; v < MG.vexnum; v++)
	{
		finall[v] = 0;
		D[v] = MG.arcs[v0][v].adj;
		for (i = 0; i < MG.vexnum; i++)
			P[v][i] = 0;
		if (MG.arcs[v0][v].adj < INFINITY)
			P[v][v] = P[v][v0] = 1;
	}
	D[v0] = 0;
	finall[v0] = 1;

	//正式开始
	for (i = 0; i < MG.vexnum - 1; i++)
	{
		min = INFINITY;
		for (w = 0; w < MG.vexnum; w++) //第一步：挑选离v0最近、且还没有final的v，敲定，并得到他这条路的权min
		{
			if ((!finall[w]) && (D[w] < min))
			{
				v = w;
				min = D[v];
			}
		}
		finall[v] = 1; //表示找到v了
		for (w = 0; w < MG.vexnum; w++) //第二步：看看v0到其他点走v这条路会不会更短，更短的话就改走这条路
		{
			if ((!finall[w]) && (min + MG.arcs[v][w].adj < D[w]))
			{
				D[w] = min + MG.arcs[v][w].adj;
				for (j = 0; j < MG.vexnum; j++)
					P[w][j] = P[v][j];
				P[w][w] = 1;
			}
		}//for w
	}//for i
}

Status ReadShortestPath_DIJ(MGraph MG, char* v0_name, PathMatrix P, ShortPathTable D)
{
	int v0 = LocateMGVex(MG, v0_name);
	int *ReadAlready = (int*)malloc(sizeof(int) * MG.vexnum);

	for (int v = 0; v < MG.vexnum; v++)
	{
		for (int i = 0; i < MG.vexnum; i++) ReadAlready[i] = 0;//对于每个v(行)，都要初始化

		printf("%s到%s(权值%d):", MG.vexs[v0], MG.vexs[v], D[v]);
		if (D[v] == INFINITY)
		{
			printf("hhhh到不了呀！\n");
			continue; //权值66666
		}
		for (int w =v0; w >= 0; w = GetNextW(v, w, MG, P, ReadAlready))
		{
			printf("%s->", MG.vexs[w]);
			ReadAlready[w] = 1;
		}
		printf("\b\b  \n");
	}

	return OK;
}

void ShortestPath_FLOYD(MGraph MG, PathNames &P, DistanceMatrix &D)
{
	int u, v, w, i;

	D = (int**)malloc(sizeof(int*) * MG.vexnum);
	for (v = 0; v < MG.vexnum; v++) {
		D[v] = (int*)malloc(sizeof(int) * MG.vexnum);
		for (w = 0; w < MG.vexnum; w++) {
			D[v][w] = MG.arcs[v][w].adj;
			P[v][w] = (int*)malloc(sizeof(int) * MG.vexnum);
			for (u = 0; u < MG.vexnum; u++)
				P[v][w][u] = 0;
			if (D[v][w] != INFINITY)
				P[v][w][w] = P[v][w][v] = 1;
		}
		D[v][v] = 0; //自己到自己路为0
		P[v][v][v] = 1; //自己到自己为1
	}

	for (u = 0; u < MG.vexnum; u++) {
		for (v = 0; v < MG.vexnum; v++) {
			for (w = 0; w < MG.vexnum; w++) {
				if (D[v][w] > D[v][u] + D[u][w]) {
					D[v][w] = D[v][u] + D[u][w];
					for (i = 0; i < MG.vexnum; i++)
						P[v][w][i] = ((P[v][u][i] == 0 && P[u][w][i] == 0) ? 0 : 1);
				} //if
			} //for w
		} //for v
	} //for u
}

void ReadShortestPath_FLOYD(MGraph MG, PathNames P, DistanceMatrix D)
{
	int vi, vj;
	for (vi = 0; vi < MG.vexnum; vi++) {
		for (vj = 0; vj < MG.vexnum; vj++) 
			ReadOnePath_FLOYD(MG, P, D, vi, vj);
	}
}

void ReadOnePath_FLOYD(MGraph MG, PathNames P, DistanceMatrix D, int vi, int vj)
{
	int *ReadAlready = (int*)malloc(sizeof(int) * MG.vexnum);
	for (int i = 0; i < MG.vexnum; i++) ReadAlready[i] = 0;

	printf("从%s到%s(总长%d)：", MG.vexs[vi], MG.vexs[vj], D[vi][vj]);

	if (D[vi][vj] == INFINITY) {
		printf("找不到了耶~~~\n");
		return;
	}
	
	for (int w = vi; w >= 0; w = GetNextW(vj, w, MG, P[vi], ReadAlready)) {
		printf("%s->",MG.vexs[w]);
		ReadAlready[w] = 1;
	}
	printf("\b\b  \n");
}

Status TopologicalSort(ALGraph ALG)
{
	sqStack s;
	VNode currNode;
	ArcNode *p;
	int i, w, count; //count用来算有无环
	int *indegree;

	initStack(s);
	findInDegree(ALG, indegree);
	for (i = 0; i < ALG.vexnum; i++) 
	{
		if (indegree[i] == 0)
			Push(s, ALG.vertices[i]);
	}
	ReadStack(s);
		
	for (count = 0; !EmptyStack(s); count++)
	{
		Pop(s, currNode);
		Visit(currNode);
		for (p = currNode.firstarc; p; p = p->nextarc)
		{
			w = p->adjvex;
			indegree[w]--;
			if (!indegree[w]) 
				Push(s, ALG.vertices[w]);
		}
	}
	if (count < ALG.vexnum) return ERROR;
	else return OK;
}

Status initStack(sqStack &s)
{
	s.base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	if (!s.base) return OVERFLOW;
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(sqStack &s, ElemType e)
{
	if (s.top - s.base >= s.stacksize)
	{
		s.base = (ElemType*)realloc(s.base, sizeof(ElemType) * (s.stacksize + INCREMENT));
		if (!s.base) return OVERFLOW;
		s.top = s.base + s.stacksize;
		s.stacksize += INCREMENT;
	}
	*s.top = e;
	s.top++;

	return OK;
}

Status Pop(sqStack &s, ElemType &e)
{
	if (s.top == s.base) return ERROR;
	e = *(--s.top);
	return OK;
}

Status ReadStack(sqStack s)
{
	if (!s.base) return ERROR;
	ElemType *p;
	for (p = s.base; p != s.top; p++)
		Visit(*p);
	putchar('\n');
	return OK;
}

bool EmptyStack(sqStack s)
{
	if (s.top == s.base) return true;
	else return false;
}

int GetNextW(int v, int w, MGraph MG, PathMatrix P, int* ReadAlready)
{
	int nextW, i; 
	int min; //min是不可少的见下：

	for (i = 0, nextW = 0, min = INFINITY; i < MG.vexnum; i++)
	{    //在上面v这行里那里没被读过；i点在v这行里面；小
		if ((!ReadAlready[i]) && P[v][i] && MG.arcs[w][i].adj < min) { //一个=或不=的血案.初始i = nextW为0啊
			nextW = i;
			min = MG.arcs[w][nextW].adj;
		}
	}
	if (min == INFINITY) //我本来是想搞个若nextW == 0则返回-1，但有一个bug：
		return -1;       //是在最一开始，初始i = nextW = 0时，一定有MG.arcs[w][i].adj == MG.arcs[w][nextW].adj；
	else                 //所以即便v0是符合条件的，也进不去if里面的。所以一旦到了v0，就会返回-1，中断。
		return nextW;    //除了起始点vi==v0，Read函数的第一轮循环打印出来v0，就不会进入这GetNextW了。
}

void Visit(VNode v)
{
	printf("%-4s", v.data);
}

char* s_gets(char* str, int n)
{
	char* ret;

	ret = fgets(str, n, stdin);
	while (*str != '\n' && *str != '\0')
		str++;
	if (*str == '\n') *str = '\0';
	else while (getchar() != '\n');

	str = ret;
	return ret;
}

bool SearchPath(ALGraph ALG, char* vi, char *vj)
{
	bool result;
	int *visited = (int*)malloc(sizeof(int) * ALG.vexnum);
	for (int i = 0; i < ALG.vexnum; i++)
		visited[i] = 0;
	visited[LocateALGVex(ALG, vj)] = 1;

	result =  SearchPath_Each(ALG, LocateALGVex(ALG, vi), LocateALGVex(ALG, vj), visited);
	return result;
}

bool SearchPath_Each(ALGraph ALG, int vi, int vj, int* visited)
{
	int w;
	bool result;
	visited[vi] = 1;
	ArcNode* p;

	for (p = ALG.vertices[vi].firstarc; p != NULL && result != true; p = p->nextarc)
	{
		w = p->adjvex;
		if (w == vj) 
			result = true; //随后就退出
		else if(!visited[w])
			result = SearchPath_Each(ALG, w, vj, visited);
	}
	if (result) 
		Visit(ALG.vertices[w]);
	return result;
}

bool SearchCircle(ALGraph ALG)
{
	int v0, v;
	bool flag = false;
	int *straightLine = (int*)malloc(sizeof(int) * ALG.vexnum);
	for (v0 = 0; v0 < ALG.vexnum; v0++)
	{
		for (v = 0; v < ALG.vexnum; v++) straightLine[v] = 0;
		if (SearchCircle_Each(ALG, straightLine, v0))
		{
			printf("(这是一个从%s开始的环)\n", ALG.vertices[v0].data);
			flag = true;
		}
	}
	return flag;
}

bool SearchCircle_Each(ALGraph ALG, int* (&straightLine), int v)
{
	ArcNode *p;
	straightLine[v] = 1; //表示进入条直系了
	for (p = ALG.vertices[v].firstarc; p != NULL; p = p->nextarc)
	{
		if (straightLine[p->adjvex] || SearchCircle_Each(ALG, straightLine, p->adjvex)) 
		{    //自己到自己了           v深度遍历后面的连着前面的
			Visit(ALG.vertices[p->adjvex]);
			return true;
		}
	}
	straightLine[v] = 0; //v和v的儿孙们都找不到环，就退出直系线，退出这层递归换另一条线试一下
	return false;
}

void findInDegree(ALGraph ALG, int *(&indegree))
{
	int i;
	ArcNode *p;

	indegree = (int*)malloc(sizeof(int) * ALG.vexnum);
	for (i = 0; i < ALG.vexnum; i++)
		indegree[i] = 0;
	for (i = 0; i < ALG.vexnum; i++)
	{
		for (p = ALG.vertices[i].firstarc; p; p = p->nextarc)
			indegree[p->adjvex]++;
	}
}


