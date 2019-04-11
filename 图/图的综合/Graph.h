#pragma once
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define INFINITY 66666 //���Ȩ��66666
#define MAX_VERTEX_NUM 20 //��󶥵����
#define MAX_VERTEX_NAME 10 //�����������9���ַ�
#define MAX_ARC_INFO 20 //����Ϣ���19���ַ�
#define MAX_MAP_INFO 86 //��ͼ������Ϣ���86���ַ�
#define STACK_INIT_SIZE 100 //ջ��ʼ����
#define INCREMENT 10 //ջ׷������

typedef int Status;
typedef int VRType; //1��0-ͼ��Ȩֵ-��
typedef char InfoType; //�û������Ϣ��ָ��
typedef char VertexType[MAX_VERTEX_NAME]; //������������
typedef enum { DG, DN, UDG, UDN }GraphKind; //ͼ����

/*�ڽӾ���洢��*/
typedef struct ArcCell //������
{
	VRType adj; //�ߵ�1/0��Ȩֵ
	InfoType *info;
}ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct _mgraph //�ڽӾ���
{
	VertexType vexs[MAX_VERTEX_NUM]; //��������
	AdjMatrix arcs; //������
	int vexnum, arcnum; //������Ŀ�ͻ���
	GraphKind kind; //ͼ������
}MGraph;

/*�ڽӱ�洢��*/
typedef struct ArcNode { //�����
	ArcNode* nextarc;
	int adjvex;
	VRType weight; //Ȩֵ(ͼΪ1)
	InfoType *info;
}ArcNode;
typedef struct VNode { //����
	ArcNode* firstarc;
	VertexType data;
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct ALGraph { //�ڽӱ�
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALGraph;

/*ʮ������*/
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

/*�ڽӶ��ر�*/
//�����

/*���Ķ����ʾ*/
typedef VNode ElemType; //�ڽӱ�洢
typedef struct CSNode {
	ElemType data;
	CSNode *lchild;
	CSNode *nextsibling;
}CSNode, *CSTree;

/*����ķ��С������������(���������굽����������ĵ�����֡�����(��Ȩ))*/
typedef struct Closest {
	VertexType vexName;
	VRType lowcost; //���±굽vexName��Ȩ
}Closedge[MAX_VERTEX_NUM];

/*�Ͻ�˹�������·��������*/
typedef int **PathMatrix; //P[v][w]��ʾv0��v���·������w
typedef int *ShortPathTable; //��v0���±�v����̾���֮��

/*�����������·��������*/
typedef int *PathNames[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //��ÿ�����1��ʾ�����棬0��ʾ��������
typedef int **DistanceMatrix;

/*�������*/
typedef VNode ElemType;
typedef struct sqStack {
	ElemType *base;
	ElemType *top;
	int stacksize;
}sqStack;

/*�ڽӾ���*/
Status StartCreateMG(MGraph &MG);
Status CreateMG(MGraph &MG); 
Status ReadMGraph(MGraph MG);
/*�ڽ�����*/
Status StartCreateALG(ALGraph &ALG);
Status CreateALG(ALGraph &ALG);
Status ReadALGraph(ALGraph ALG);
/*ʮ������*/
Status CreateOLG(OLGraph &OLG);
Status ReadOLGraph(OLGraph OLG);
/*�ڽӶ��ر�*/
//�����
/*�������������������(�ڽ�����)*/
Status DFSTraverse_ALG(ALGraph ALG);
void DFS_ALG(ALGraph ALG, int *visited, int v);
Status DFSForest(ALGraph ALG, CSTree &T);
Status DFSTree(ALGraph ALG, int v, CSTree &T, int* visited);
/*���ı����Ȳ���*/
Status PreTraverse(CSTree T);
Status InTraverse(CSTree T);
/*�������������������(�ڽӾ���)*/
//�����
/*��С������֮����ķ�㷨*/
Status MiniSpanTree_PRIM(MGraph MG, VertexType target); 
int minimum(Closedge closedge, int vexnum); //��ѡ����û��Χ�ġ��Ҿ����Ѿ���Χ���������С��
/*��С������֮��³˹�����㷨*/
//�����
/*�Ͻ�˹�������·��*/
void ShortestPath_DIJ(MGraph MG, char* v0_name, PathMatrix &P, ShortPathTable &D);
Status ReadShortestPath_DIJ(MGraph MG, char* v0_name, PathMatrix P, ShortPathTable D);
//����������ҳ�1����w���ڣ�2����w�����3����P[v]��(����v0->v·����)��4��֮ǰû������next_w(�Ҳ����򷵻�-1)
int GetNextW(int v, int w, MGraph MG, PathMatrix P, int* ReadAlready); 
/*�����������·��*/
void ShortestPath_FLOYD(MGraph MG, PathNames &P, DistanceMatrix &D);
void ReadShortestPath_FLOYD(MGraph MG, PathNames P, DistanceMatrix D);
void ReadOnePath_FLOYD(MGraph MG, PathNames P, DistanceMatrix D, int vi, int vj); 
/*�������*/
Status TopologicalSort(ALGraph ALG); //��������
Status TopologicalOrder(ALGraph ALG);
Status CriticalPath(ALGraph ALG); //����ؼ�·��
Status initStack(sqStack &s);
Status Push(sqStack &s, ElemType e);
Status Pop(sqStack &s, ElemType &e);
Status ReadStack(sqStack s);
bool EmptyStack(sqStack s);
/*�������ܺ���*/
char* s_gets(char* str, int n); //��fputs���ƣ�ֻ����ȥ���س������ѳ���n-1���ַ���ȥ��
void Visit(VNode v);
int LocateMGVex(MGraph MG, char* v); //����ȷ��ĳ�����ڵ����顢����Ӧ�ı߶�ά���������λ��
int LocateALGVex(ALGraph ALG, char* v); //��LocateMGVex����
int LocateOLGVex(OLGraph OLG, char* v);
bool SearchPath(ALGraph ALG, char* vi, char *vj); //����ͼ��������������·��(��ȱ���)
bool SearchPath_Each(ALGraph ALG, int vi, int vj, int* visited); 
bool SearchCircle(ALGraph ALG); //�����Ƿ���ڻ�(��ȱ���)
bool SearchCircle_Each(ALGraph ALG, int* (&straightLine), int v);
void findInDegree(ALGraph ALG, int *(&indegree)); //�ڽӱ�����ͼ����ȵ����������ص�indegree����

#endif // !GRAPH_H_INCLUDED
