#define MAX_TREE_SIZE 100

typedef int ElemType;
typedef struct CTNode //孩子节点
{
	int child; //孩子节点的下标
	struct CTNode *next; //指向下一个孩子节点的指针
}CTNode;
//typedef CTNode *ChildPtr;
typedef struct CTBox //表头结构
{
	ElemType data; //结点数据
	int parent;
	CTNode* firstChild;
}CTBox;
typedef struct CTREE
{
	CTBox nodes[MAX_TREE_SIZE]; //结点数据
	int root; //根的位置
	int n; //节点数
}CTree;
