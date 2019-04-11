#define MAX_TREE_SIZE 100

typedef int ElemType;
typedef struct CTNode //���ӽڵ�
{
	int child; //���ӽڵ���±�
	struct CTNode *next; //ָ����һ�����ӽڵ��ָ��
}CTNode;
//typedef CTNode *ChildPtr;
typedef struct CTBox //��ͷ�ṹ
{
	ElemType data; //�������
	int parent;
	CTNode* firstChild;
}CTBox;
typedef struct CTREE
{
	CTBox nodes[MAX_TREE_SIZE]; //�������
	int root; //����λ��
	int n; //�ڵ���
}CTree;
