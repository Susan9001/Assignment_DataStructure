#pragma once
#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define INFINITY 66666 //���Ȩ��66666
#define MAX_VERTEX_NUM 10 //�������
//#define ARC_NUM 17 //����
#define MAX_VERTEX_NAME 10 //�����������9���ַ�
#define MAX_SPOTS_INFO 86 //��ͼ������Ϣ���86���ַ�
#define MAX_ARC_INFO 30 //·����Ϣ

typedef int Status;
typedef double VRType; //��Ȩֵ-��
typedef char InfoType; //�û������Ϣ��ָ��
/*��ͼ���ڽӾ���*/
typedef struct MapType //��ͼ
{
	int id;
	char name[MAX_VERTEX_NAME];
	char info[MAX_SPOTS_INFO];
}MapType;
typedef enum { DG, DN, UDG, UDN }GraphKind; //ͼ����
typedef struct ArcCell //������
{
	VRType adj; //�ߵ�1/0��Ȩֵ
	InfoType *info;
}ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct _mgraph //�ڽӾ���
{
	int spotnum, arcnum; //������Ŀ�ͻ���
	GraphKind kind; //ͼ������
	MapType spots[MAX_VERTEX_NAME]; //��ͼ�ṹ������ָ��
	AdjMatrix arcs; //������
} Map;

/*�����������·��������*/
typedef int *Path; //Ĭ�������v0����ʾv0��ĳ��v��·(1��·�ϣ�������)
typedef Path AllPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //��ÿ�����1��ʾ�����棬0��ʾ��������
typedef double* ShortestPathTable;
typedef ShortestPathTable *DistanceMatrix;

/*��ͼ����*/
void MapSystem(); //��������Mapϵͳ
Status CreateMap(Map &map);
Status ReadMap(Map map);
Status ShowSpotInfo(Map map, int v);
int LocateSpot(Map map, char* nameNum);
/*�����������·��*/
Status AllShortestPath_FLOYD(Map map, AllPath &AP, DistanceMatrix &AD, char MoreOrNot);
Status ReadShortestPath_FLOYD(Map map, AllPath AP, DistanceMatrix AD);
Status ReadOnePath_FLOYD(Map map, Path P, ShortestPathTable D, int vi, int vj);
/*�������ܺ���*/
char* s_gets(char* str, int n); //��fputs���ƣ�ֻ����ȥ���س������ѳ���n-1���ַ���ȥ��
//����������ҳ�1����w���ڣ�2����w�����3����P[v]��(����v0->v·����)��4��֮ǰû������next_w(�Ҳ����򷵻�-1)
int GetNextW(int w, Map map, Path P, int* ReadAlready); //��P����NULL�����ж���ĳ��·����

#endif // !MAP_H_INCLUDED

