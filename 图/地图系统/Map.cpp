#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Map.h"

void MapSystem()
{
	Map map;
	AllPath AP, AP_More;
	DistanceMatrix AD, AD_More;
	int v, vi, vj;
	int choice;
	char nameNum[MAX_VERTEX_NAME];

	printf("欢迎来到暨南大学！\n");
	CreateMap(map);
	AllShortestPath_FLOYD(map, AP, AD, 'y');

	printf("1.查看地图  2.查看地点简介  3.查找最短路径  4.退出\n");
	while (true) {
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
			printf("ops!请正确输入选择：");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		switch (choice) {
		case 1:
			ReadMap(map);
			break;
		case 2:
			printf("请输入要查找的地点名或编号：");
			s_gets(nameNum, MAX_VERTEX_NAME);
			v = LocateSpot(map, nameNum);
			if (v < 0)
				printf("找不到该地点耶~~\n");
			else
				ShowSpotInfo(map, v);
			break;
		case 3:
			printf("请输入两个地点的名字或者编号(起始-结束)：");
			s_gets(nameNum, MAX_VERTEX_NAME * 2);
			vi = LocateSpot(map, strtok(nameNum, "-"));
			vj = LocateSpot(map, strtok(NULL, "-"));
			if (vi >= 0 && vj >= 0)
				ReadOnePath_FLOYD(map, AP[vi][vj], AD[vi], vi, vj);
			else
				printf("请正确地输入！\n");
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}

Status CreateMap(Map &map)
{
	int i, j;
	MapType spotsArr[] = {
		{100, "正门", "人称\"暨大白拱门\"" }, {101, "院系楼", "顾名思义"}, 
		{102,"实验楼", "给码农写码、化学生过柱子balabala···的地方"},
		{103, "镜湖", "其实我能说看起来更像一条河么？春天杨柳依依，很合适情侣漫步"}, 
		{104, "恒大楼", "带小阳台、小草坪，可以晒太阳的教学楼。跟本部的富力楼人称\"暨大德比\""},
		{105, "图书馆", "他家的空调好像不用电费是的，所以学习的同时可以免费叹空调hhh"}, {106, "宿舍区", "暨大七星酒店"},
		{107, "体育场", "不用解释！"}, {108, "饭堂", "吃的地方"}, {109, "超市", "暨大七星级奢侈品专卖店"}
	};
	/*AdjMatrix roads = { 
		// 0            1            2            3            4             5            6           7             8            9
		{ { 0 },       { 3 },       { 3 },       { 4 },       { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ INFINITY } },
		{ { 3 },       { 0 },       { INFINITY },{ 2 },       { INFINITY },{ INFINITY },{ INFINITY },{ 5 },       { INFINITY },{ INFINITY } },
		{ { 3 },       { INFINITY },{ 0 },       { 2 },       { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ INFINITY } },
		{ { 4 },       { 2 },       { 2 },       { 0 },       { 1 },       { 0.5 },     { INFINITY },{ 3.5 },     { INFINITY },{ INFINITY } },
		{ { INFINITY },{ INFINITY },{ INFINITY },{ 1 },       { 0 },       { 0.5 },     { 2 },       { INFINITY },{ 2 },       { INFINITY } },
		{ { INFINITY },{ INFINITY },{ INFINITY },{ 0.5 },     { 0.5 },     { 0 },       { INFINITY },{ 2.5 },     { INFINITY },{ 5 } },
		{ { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ 2 },       { INFINITY },{ 0 },       { INFINITY },{ INFINITY },{ 3 } },
		{ { INFINITY },{ 5 },       { INFINITY },{ 3.5 },     { INFINITY },{ 2.5 },     { INFINITY },{ 0 },       { INFINITY },{ 1 } },
		{ { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ 2 },       { INFINITY },{ INFINITY },{ INFINITY },{ 0 },       { INFINITY } },
		{ { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ 5 },       { 3 },       { 1 },       { INFINITY },{ 0 } },
	};*/

	AdjMatrix roads = {
      // 0            1            2            3            4             5            6           7             8   
/*0*/{ { 0 }},
/*1*/{ { 3 },       { 0 }},
/*2*/{ { 3 },       { INFINITY },{ 0 }},
/*3*/{ { 4 },       { 2 },       { 2 },       { 0 } },
/*4*/{ { INFINITY },{ INFINITY },{ INFINITY },{ 1 },       { 0 }},
/*5*/{ { INFINITY },{ INFINITY },{ INFINITY },{ 0.5 },     { 0.5 },     { 0 } },
/*6*/{ { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ 2 },       { INFINITY },{ 0 } },
/*7*/{ { INFINITY },{ 6 },       { INFINITY },{ 3.5 },     { INFINITY },{ 2.5 },     { INFINITY },{ 0 } },
/*8*/{ { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ 2 },       { INFINITY },{ INFINITY },{ INFINITY },{ 0 } },
/*9*/{ { INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ INFINITY },{ 3 },       { 3 },       { 1 },       { INFINITY },{ 0 } },
	};
	map = { MAX_VERTEX_NUM, 0, UDN }; //spotnum, arcnum, 无向网
	for (i = 0; i < map.spotnum; i++) {
		map.spots[i].id = spotsArr[i].id;
		strcpy(map.spots[i].name, spotsArr[i].name);
		strcpy(map.spots[i].info, spotsArr[i].info);
		for (j = 0; j < i + 1 ; j++) {
			map.arcs[i][j].adj = roads[i][j].adj;
			map.arcs[j][i] = map.arcs[i][j];
			if (map.arcs[i][j].adj < INFINITY && map.arcs[i][j].adj != 0) 
				map.arcnum++;
		}
	}
	
	return OK;
}

Status ReadMap(Map map)
{
	printf("编号\t");
	for (int i = 0; i < map.spotnum; i++)
		printf("%d\t", map.spots[i].id);
	printf("\n地名\t");
	for (int i = 0; i < map.spotnum; i++)
		printf("%s\t", map.spots[i].name);

	for (int i = 0; i < map.spotnum; i++) {
		printf("\n\n%s\t", map.spots[i].name);
		for (int j = 0; j < map.spotnum; j++) {
			if ((int)map.arcs[i][j].adj == INFINITY)
				printf("%c\t", '#');
			else if ((int)(map.arcs[i][j].adj + 0.9) == (int)(map.arcs[i][j].adj) ) //实际是整数，则不用.0了
				printf("%d\t", (int)map.arcs[i][j].adj);
			else 
				printf("%.1lf\t", map.arcs[i][j].adj);
		}
	}
	printf("\n\n景点%d处路%d条\n", map.spotnum,map.arcnum);
	return OK;
}

Status ShowSpotInfo(Map map, int v)
{
	int *ReadAlready = (int*)malloc(sizeof(int) * map.spotnum);
	if (!ReadAlready) return ERROR;

	printf("编号：%-4d  名称：%-7s\n简介：", map.spots[v].id, map.spots[v].name);
	fputs(map.spots[v].info, stdout);
	printf("\n与之相邻的地点：");
	for (int i = 0; i < map.spotnum; i++) ReadAlready[i] = 0;
	for (int w = 0; w <map.spotnum; w++) {
		if (map.arcs[v][w].adj < INFINITY && map.arcs[v][w].adj != 0) 
			printf("%s(距离%.1lf), ", map.spots[w].name, map.arcs[v][w].adj);
		ReadAlready[w] = 1;
	}
	printf("\b\b \n");

	return OK;
}

int LocateSpot(Map map, char* nameNum)
{
	static int count = 0;
	for (int i = 0; i < map.spotnum; i++) {
		if (!strcmp(nameNum, map.spots[i].name) || atoi(nameNum) == map.spots[i].id)
			return i;
	}
	return -1; //找不到了
}

Status AllShortestPath_FLOYD(Map map, AllPath &AP, DistanceMatrix &AD, char MoreOrNot)
{
	int u, v, w, i;

	AD = (DistanceMatrix)malloc(sizeof(ShortestPathTable) * map.spotnum);
	if (!AD) return ERROR;
	for (v = 0; v < map.spotnum; v++) {
		AD[v] = (ShortestPathTable)malloc(sizeof(double) * map.spotnum);
		if (!AD[v]) return ERROR;
		for (w = 0; w < map.spotnum; w++) {
			AD[v][w] = map.arcs[v][w].adj;
			AP[v][w] = (Path)malloc(sizeof(int) * map.spotnum);
			if (!AP[v][w]) return ERROR;
			for (u = 0; u < map.spotnum; u++)
				AP[v][w][u] = 0;
			if (AD[v][w] != INFINITY)
				AP[v][w][w] = AP[v][w][v] = 1;
		}
		AD[v][v] = 0; //自己到自己路为0
		AP[v][v][v] = 1; //自己到自己为1
	}

	for (u = 0; u < map.spotnum; u++) {
		for (v = 0; v < map.spotnum; v++) {
			for (w = 0; w < map.spotnum; w++) {
				if (AD[v][w] > AD[v][u] + AD[u][w] || (AD[v][w] == AD[v][u] + AD[u][w] && toupper(MoreOrNot) == 'Y')) {
					AD[v][w] = AD[v][u] + AD[u][w];
					for (i = 0; i < map.spotnum; i++)
						AP[v][w][i] = ((AP[v][u][i] == 0 && AP[u][w][i] == 0) ? 0 : 1);
				} //if
			} //for w
		} //for v
	} //for u

	return OK;
}

Status ReadShortestPath_FLOYD(Map map, AllPath AP, DistanceMatrix AD)
{
	int vi, vj;
	for (vi = 0; vi < map.spotnum; vi++) {
		for (vj = 0; vj < map.spotnum; vj++)
			if (!ReadOnePath_FLOYD(map, AP[vi][vj], AD[vi], vi, vj)) return ERROR;;
	}
	return OK;
}

Status ReadOnePath_FLOYD(Map map, Path P, ShortestPathTable D, int vi, int vj)
{
	int *ReadAlready = (int*)malloc(sizeof(int) * map.spotnum);
	if (!ReadAlready) return ERROR;
	for (int i = 0; i < map.spotnum; i++) ReadAlready[i] = 0;

	printf("从%s到%s(总长%.1lf)：", map.spots[vi].name, map.spots[vj].name, D[vj]);
	if (D[vj] == INFINITY) {
		printf("抱歉，没有路耶~~\n");
		return OK;
	}
	for (int w = vi; w >= 0; w = GetNextW(w, map, P, ReadAlready)) {
		printf("%s->", map.spots[w].name);
		ReadAlready[w] = 1;
	}
	printf("\b\b  \n");

	return OK;
}

int GetNextW(int w, Map map, Path P, int* ReadAlready)
{
	int nextW, i;
	int min; //min是不可少的见下：

	for (i = 0, nextW = 0, min = INFINITY; i < map.spotnum; i++)
	{    //在上面v这行里那里没被读过；i点在v这行里面；小
		if ((!ReadAlready[i]) && (!P || P[i]) && map.arcs[w][i].adj < min) { //一个=或不=的血案.初始i = nextW为0啊
			nextW = i;
			min = map.arcs[w][nextW].adj;
		}
	}
	if ((int)min == INFINITY) //我本来是想搞个若nextW == 0则返回-1，但有一个bug：
		return -1;       //是在最一开始，初始i = nextW = 0时，一定有map.arcs[w][i].adj == map.arcs[w][nextW].adj；
	else                 //所以即便v0是符合条件的，也进不去if里面的。所以一旦到了v0，就会返回-1，中断。
		return nextW;    //除了起始点vi==v0，Read函数的第一轮循环打印出来v0，就不会进入这GetNextW了。
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