#pragma once
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define INFINITY 66666 //最大权重66666
#define MAX_VERTEX_NUM 20 //最大顶点个数
#define MAX_VERTEX_NAME 10 //顶点名字最多9个字符
#define MAX_ARC_INFO 20 //弧信息最多19个字符
#define MAX_MAP_INFO 86 //地图顶点信息最多86个字符
#define STACK_INIT_SIZE 100 //栈初始容量
#define INCREMENT 10 //栈追加容量

typedef int Status;
typedef int VRType; //1和0-图，权值-网
typedef char InfoType; //该弧相关信息的指针
typedef char VertexType[MAX_VERTEX_NAME]; //顶点名字类型
typedef enum { DG, DN, UDG, UDN }GraphKind; //图类型

/*邻接矩阵存储法*/
typedef struct ArcCell //边数组
{
	VRType adj; //边的1/0或权值
	InfoType *info;
}ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct _mgraph //邻接矩阵
{
	VertexType vexs[MAX_VERTEX_NUM]; //顶点数组
	AdjMatrix arcs; //边数组
	int vexnum, arcnum; //顶点数目和弧数
	GraphKind kind; //图的类型
}MGraph;

/*邻接表存储法*/
typedef struct ArcNode { //弧结点
	ArcNode* nextarc;
	int adjvex;
	VRType weight; //权值(图为1)
	InfoType *info;
}ArcNode;
typedef struct VNode { //点结点
	ArcNode* firstarc;
	VertexType data;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct ALGraph { //邻接表
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALGraph;

/*十字链表*/
typedef struct ArcBox {
	int tail, head;
	ArcBox *hlink, *tlink;
	InfoType *info;
}ArcBox;
typedef struct VexNode {
	VertexType data;
	ArcBox *firstin, *firstout;
}VexNode;
typedef struct OLGraph {
	VexNode xlist[MAX_VERTEX_NUM];
	int vexnum, arcnum;
}OLGraph;

/*邻接多重表*/
//待完成

/*树的二叉表示*/
typedef VNode ElemType; //邻接表存储
typedef struct CSNode {
	ElemType data;
	CSNode *lchild;
	CSNode *nextsibling;
}CSNode, *CSTree;

/*普里姆最小生成树·辅助(包含其他店到在树上最近的店的名字、距离(即权))*/
typedef struct Closest {
	VertexType vexName;
	VRType lowcost; //从下标到vexName的权
}Closedge[MAX_VERTEX_NUM];

/*迪杰斯特拉最短路径·辅助*/
typedef int **PathMatrix; //P[v][w]表示v0到v最短路径上有w
typedef int *ShortPathTable; //放v0到下标v的最短距离之和

/*佛洛依德最短路径·辅助*/
typedef int *PathNames[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //放每个点的1表示在上面，0表示不在上面
typedef int **DistanceMatrix;

/*拓扑相关*/
typedef VNode ElemType;
typedef struct sqStack {
	ElemType *base;
	ElemType *top;
	int stacksize;
}sqStack;

/*邻接矩阵*/
Status StartCreateMG(MGraph &MG);
Status CreateMG(MGraph &MG); 
Status ReadMGraph(MGraph MG);
/*邻接链表*/
Status StartCreateALG(ALGraph &ALG);
Status CreateALG(ALGraph &ALG);
Status ReadALGraph(ALGraph ALG);
/*十字链表*/
Status CreateOLG(OLGraph &OLG);
Status ReadOLGraph(OLGraph OLG);
/*邻接多重表*/
//待完成
/*深度优先搜索及生成树(邻接链表)*/
Status DFSTraverse_ALG(ALGraph ALG);
void DFS_ALG(ALGraph ALG, int *visited, int v);
Status DFSForest(ALGraph ALG, CSTree &T);
Status DFSTree(ALGraph ALG, int v, CSTree &T, int* visited);
/*树的遍历等操作*/
Status PreTraverse(CSTree T);
Status InTraverse(CSTree T);
/*广度优先搜索及生成树(邻接矩阵)*/
//待完成
/*最小生成树之普里姆算法*/
Status MiniSpanTree_PRIM(MGraph MG, VertexType target); 
int minimum(Closedge closedge, int vexnum); //挑选出还没入围的、且距离已经入围的任意点最小的
/*最小生成树之克鲁斯卡尔算法*/
//待完成
/*迪杰斯特拉最短路径*/
void ShortestPath_DIJ(MGraph MG, char* v0_name, PathMatrix &P, ShortPathTable &D);
Status ReadShortestPath_DIJ(MGraph MG, char* v0_name, PathMatrix P, ShortPathTable D);
//以下这个：找出1、跟w相邻；2、跟w最近；3、在P[v]中(即在v0->v路径中)；4、之前没读过的next_w(找不到则返回-1)
int GetNextW(int v, int w, MGraph MG, PathMatrix P, int* ReadAlready); 
/*佛洛依德最短路径*/
void ShortestPath_FLOYD(MGraph MG, PathNames &P, DistanceMatrix &D);
void ReadShortestPath_FLOYD(MGraph MG, PathNames P, DistanceMatrix D);
void ReadOnePath_FLOYD(MGraph MG, PathNames P, DistanceMatrix D, int vi, int vj); 
/*拓扑相关*/
Status TopologicalSort(ALGraph ALG); //拓扑排序
Status TopologicalOrder(ALGraph ALG);
Status CriticalPath(ALGraph ALG); //输出关键路径
Status initStack(sqStack &s);
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
Status ReadStack(sqStack s);
bool EmptyStack(sqStack s);
/*其他功能函数*/
char* s_gets(char* str, int n); //跟fputs相似，只不过去掉回车，并把超过n-1的字符串去掉
void Visit(VNode v);
int LocateMGVex(MGraph MG, char* v); //输入确定某顶点在点数组、即对应的边二维数组里面的位置
int LocateALGVex(ALGraph ALG, char* v); //与LocateMGVex相似
int LocateOLGVex(OLGraph OLG, char* v);
bool SearchPath(ALGraph ALG, char* vi, char *vj); //有向图搜索两个顶点间的路径(深度遍历)
bool SearchPath_Each(ALGraph ALG, int vi, int vj, int* visited); 
bool SearchCircle(ALGraph ALG); //搜索是否存在环(深度遍历)
bool SearchCircle_Each(ALGraph ALG, int* (&straightLine), int v);
void findInDegree(ALGraph ALG, int *(&indegree)); //邻接表有向图找入度的数量，返回到indegree里面

#endif // !GRAPH_H_INCLUDED
