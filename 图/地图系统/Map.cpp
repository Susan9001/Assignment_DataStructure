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

	printf("��ӭ�������ϴ�ѧ��\n");
	CreateMap(map);
	AllShortestPath_FLOYD(map, AP, AD, 'y');

	printf("1.�鿴��ͼ  2.�鿴�ص���  3.�������·��  4.�˳�\n");
	while (true) {
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
			printf("ops!����ȷ����ѡ��");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		switch (choice) {
		case 1:
			ReadMap(map);
			break;
		case 2:
			printf("������Ҫ���ҵĵص������ţ�");
			s_gets(nameNum, MAX_VERTEX_NAME);
			v = LocateSpot(map, nameNum);
			if (v < 0)
				printf("�Ҳ����õص�Ү~~\n");
			else
				ShowSpotInfo(map, v);
			break;
		case 3:
			printf("�����������ص�����ֻ��߱��(��ʼ-����)��");
			s_gets(nameNum, MAX_VERTEX_NAME * 2);
			vi = LocateSpot(map, strtok(nameNum, "-"));
			vj = LocateSpot(map, strtok(NULL, "-"));
			if (vi >= 0 && vj >= 0)
				ReadOnePath_FLOYD(map, AP[vi][vj], AD[vi], vi, vj);
			else
				printf("����ȷ�����룡\n");
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
		{100, "����", "�˳�\"�ߴ�׹���\"" }, {101, "Ժϵ¥", "����˼��"}, 
		{102,"ʵ��¥", "����ũд�롢��ѧ��������balabala�������ĵط�"},
		{103, "����", "��ʵ����˵����������һ����ô�����������������ܺ�����������"}, 
		{104, "���¥", "��С��̨��С��ƺ������ɹ̫���Ľ�ѧ¥���������ĸ���¥�˳�\"�ߴ�±�\""},
		{105, "ͼ���", "���ҵĿյ������õ���ǵģ�����ѧϰ��ͬʱ�������̾�յ�hhh"}, {106, "������", "�ߴ����ǾƵ�"},
		{107, "������", "���ý��ͣ�"}, {108, "����", "�Եĵط�"}, {109, "����", "�ߴ����Ǽ��ݳ�Ʒר����"}
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
	map = { MAX_VERTEX_NUM, 0, UDN }; //spotnum, arcnum, ������
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
	printf("���\t");
	for (int i = 0; i < map.spotnum; i++)
		printf("%d\t", map.spots[i].id);
	printf("\n����\t");
	for (int i = 0; i < map.spotnum; i++)
		printf("%s\t", map.spots[i].name);

	for (int i = 0; i < map.spotnum; i++) {
		printf("\n\n%s\t", map.spots[i].name);
		for (int j = 0; j < map.spotnum; j++) {
			if ((int)map.arcs[i][j].adj == INFINITY)
				printf("%c\t", '#');
			else if ((int)(map.arcs[i][j].adj + 0.9) == (int)(map.arcs[i][j].adj) ) //ʵ��������������.0��
				printf("%d\t", (int)map.arcs[i][j].adj);
			else 
				printf("%.1lf\t", map.arcs[i][j].adj);
		}
	}
	printf("\n\n����%d��·%d��\n", map.spotnum,map.arcnum);
	return OK;
}

Status ShowSpotInfo(Map map, int v)
{
	int *ReadAlready = (int*)malloc(sizeof(int) * map.spotnum);
	if (!ReadAlready) return ERROR;

	printf("��ţ�%-4d  ���ƣ�%-7s\n��飺", map.spots[v].id, map.spots[v].name);
	fputs(map.spots[v].info, stdout);
	printf("\n��֮���ڵĵص㣺");
	for (int i = 0; i < map.spotnum; i++) ReadAlready[i] = 0;
	for (int w = 0; w <map.spotnum; w++) {
		if (map.arcs[v][w].adj < INFINITY && map.arcs[v][w].adj != 0) 
			printf("%s(����%.1lf), ", map.spots[w].name, map.arcs[v][w].adj);
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
	return -1; //�Ҳ�����
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
		AD[v][v] = 0; //�Լ����Լ�·Ϊ0
		AP[v][v][v] = 1; //�Լ����Լ�Ϊ1
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

	printf("��%s��%s(�ܳ�%.1lf)��", map.spots[vi].name, map.spots[vj].name, D[vj]);
	if (D[vj] == INFINITY) {
		printf("��Ǹ��û��·Ү~~\n");
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
	int min; //min�ǲ����ٵļ��£�

	for (i = 0, nextW = 0, min = INFINITY; i < map.spotnum; i++)
	{    //������v����������û��������i����v�������棻С
		if ((!ReadAlready[i]) && (!P || P[i]) && map.arcs[w][i].adj < min) { //һ��=��=��Ѫ��.��ʼi = nextWΪ0��
			nextW = i;
			min = map.arcs[w][nextW].adj;
		}
	}
	if ((int)min == INFINITY) //�ұ�����������nextW == 0�򷵻�-1������һ��bug��
		return -1;       //������һ��ʼ����ʼi = nextW = 0ʱ��һ����map.arcs[w][i].adj == map.arcs[w][nextW].adj��
	else                 //���Լ���v0�Ƿ��������ģ�Ҳ����ȥif����ġ�����һ������v0���ͻ᷵��-1���жϡ�
		return nextW;    //������ʼ��vi==v0��Read�����ĵ�һ��ѭ����ӡ����v0���Ͳ��������GetNextW�ˡ�
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