#pragma once
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define INFINITY 66666 //最大权重66666
#define MAX_VERTEX_NUM 10 //顶点个数
//#define ARC_NUM 17 //边数
#define MAX_VERTEX_NAME 10 //顶点名字最多9个字符
#define MAX_SPOTS_INFO 86 //地图顶点信息最多86个字符
#define MAX_ARC_INFO 30 //路的信息

typedef int Status;
typedef double VRType; //，权值-网
typedef char InfoType; //该弧相关信息的指针
/*地图用邻接矩阵*/
typedef struct MapType //地图
{
	int id;
	char name[MAX_VERTEX_NAME];
	char info[MAX_SPOTS_INFO];
}MapType;
typedef enum { DG, DN, UDG, UDN }GraphKind; //图类型
typedef struct ArcCell //边数组
{
	VRType adj; //边的1/0或权值
	InfoType *info;
}ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct _mgraph //邻接矩阵
{
	int spotnum, arcnum; //顶点数目和弧数
	GraphKind kind; //图的类型
	MapType spots[MAX_VERTEX_NAME]; //地图结构的数组指针
	AdjMatrix arcs; //边数组
} Map;

/*佛洛依德最短路径·辅助*/
typedef int *Path; //默认了起点v0、表示v0到某点v的路(1在路上，否则不在)
typedef Path AllPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //放每个点的1表示在上面，0表示不在上面
typedef double* ShortestPathTable;
typedef ShortestPathTable *DistanceMatrix;

/*地图功能*/
void MapSystem(); //管理整个Map系统
Status CreateMap(Map &map);
Status ReadMap(Map map);
Status ShowSpotInfo(Map map, int v);
int LocateSpot(Map map, char* nameNum);
/*佛洛依德最短路径*/
Status AllShortestPath_FLOYD(Map map, AllPath &AP, DistanceMatrix &AD, char MoreOrNot);
Status ReadShortestPath_FLOYD(Map map, AllPath AP, DistanceMatrix AD);
Status ReadOnePath_FLOYD(Map map, Path P, ShortestPathTable D, int vi, int vj);
/*其他功能函数*/
char* s_gets(char* str, int n); //跟fputs相似，只不过去掉回车，并把超过n-1的字符串去掉
//以下这个：找出1、跟w相邻；2、跟w最近；3、在P[v]中(即在v0->v路径中)；4、之前没读过的next_w(找不到则返回-1)
int GetNextW(int w, Map map, Path P, int* ReadAlready); //若P传入NULL则不用判断在某个路径中

#endif // !MAP_H_INCLUDED

