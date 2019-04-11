#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define MAX_STR_SIZE 100
#define MAX_TREE_SIZE 100
#define BLANK '#'
#define END '$'

typedef int Status;
typedef char ElemType;

/*顺序二叉树*/
typedef struct _SqBiTree {
	ElemType elem[MAX_TREE_SIZE];
	int last; //元素个数，也是最后一个元素的下标
}SqBiTree;

/*线索二叉树(在此规定：全部的左右tag为0即表示普通二叉树)*/
typedef enum PointerTag { 
	Link = 0, Thread = 1 
};
typedef struct _biTNode {
	ElemType data;
	struct _biTNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiTNode, BiThrNode, *BiTree, *BiThrTree;

/*赫夫曼树和赫夫曼编码*/
typedef struct _HTNode {
	int weight;
	int parent;
	int lchild;
	int	rchild;
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;

/*链队列(用于层序遍历)*/
typedef BiTNode* QElemType;
typedef struct _nQueue {
	QElemType data;
	_nQueue* next;
}NQueue;
typedef struct _linkQueue {
	NQueue* head; //队头空
	NQueue* rear;
}LinkQueue;

/*普通二叉树生成和遍历修改*/
Status PreCreateBiTree(BiTree &T);
Status PreTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
Status InTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
Status PostTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
Status LevelTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
//层序遍历所需要的队列操作
Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);
/*线索二叉树*/
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrNode* p, BiThrNode* (&pre));
Status InTraverse_Thr(BiThrTree Thrt);
/*赫夫曼树相关*/
void HuffmanCodeTest(); //打包了赫夫曼树相关的所有内容
int GetStrWeight(char* str, int* (&weight), char* (&eachLetter)); //根据字符串，返回有多少种字母及权重数组
int PutInWeight(int* (&weight), char* (&eacn_line));//输入并返回有多少种字母和对应的权值
Status HuffmanCoding(HuffmanTree &HTree, HuffmanCode &HCode, int* weight, int n);
Status Select(HuffmanTree HTree, int end, int &s1, int &s2); //找出HTree下标从1到end之间相加之和最小的俩
Status ReadHCode(HuffmanCode HCode, int* weight, char* eachLetter,int n);
/*其他功能*/
Status Visit(BiTNode* (&p));
Status ReverseBiTree(BiTree &T); //反转二叉树（通过先序遍历算法?）
int CountLeaves(BiTree T); //计算叶子结点数，想试试static 
int CountDepth(BiTree T); //计算二叉树深度
Status CreateSqBiTree(SqBiTree &sa); //创建顺序存储的二叉树
Status SqTurnLink(SqBiTree sa, BiTree &T, int i); //二叉树顺序转链表

int main()
{
	BiTree T = NULL, Thrt = NULL;
	SqBiTree sa;
	int choice;

	printf("1.先序输入二叉树 2.先序遍历     3.中序遍历     4.后序遍历\n");
	printf("5.构建中序线索   6.左右子树反转 7.计算叶结点数 8.计算层数\n");
	printf("9.层序输入二叉树顺序存储，转化为链式二叉树     10.层序遍历\n");
	printf("11.赫夫曼编码    12.退出\n");

	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 11)
		{
			printf("\n好像输入错误耶~~请重新输入选择：");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //消除回车

		switch (choice)
		{
		case 1:
			if (T) free(T);
			printf("请按先序输入(#号空叶，$号结束)：");
			if (PreCreateBiTree(T))
			{
				printf("先/中/后序：");
				PreTraverse(T, Visit);
				printf(", ");
				InTraverse(T, Visit);
				printf(", ");
				PostTraverse(T, Visit);
			}
			putchar('\n');
			break;
		case 2:
			printf("先序遍历：");
			PreTraverse(T, Visit);
			putchar('\n');
			break;
		case 3:
			printf("中序遍历：");
			InTraverse(T, Visit);
			putchar('\n');
			break;
		case 4:
			printf("后序遍历：");
			PostTraverse(T, Visit);
			putchar('\n');
			break;
		case 5:
			if (InOrderThreading(Thrt, T))
			{
				printf("中序线索构建成功：");
				InTraverse_Thr(Thrt);
			}
			putchar('\n');
			break;
		case 6:
			if (ReverseBiTree(T))
			{
				printf("hhhh反转成功！\n");
				printf("先/中/后序：");
				PreTraverse(T, Visit);
				printf(", ");
				InTraverse(T, Visit);
				printf(", ");
				PostTraverse(T, Visit);
			}
			putchar('\n');
			break;
		case 7:
			printf("得到的叶子数为：%d\n", CountLeaves(T));
			break;
		case 8:
			printf("当前深度为：%d\n", CountDepth(T));
			break;
		case 9:
			if (CreateSqBiTree(sa))
			{
				if (T) free(T);
				SqTurnLink(sa, T, 0);
				printf("先/中/后序：");
				PreTraverse(T, Visit);
				printf(", ");
				InTraverse(T, Visit);
				printf(", ");
				PostTraverse(T, Visit);
			}
			break;
		case 10:
			printf("层序遍历：");
			LevelTraverse(T, Visit);
			putchar('\n');
			break;
		case 11:
			HuffmanCodeTest();
			break;
		case 12:
			return 0;
		}
	}

	return 0;
}

void HuffmanCodeTest()
{
	char* str = (char*)malloc(sizeof(char) * (MAX_STR_SIZE + 1));
	char* each_letter; //输入字符串
	int* weight;
	int n; //字符个数
	int choice;
	HuffmanCode HCode = NULL;
	HuffmanTree HTree = NULL;

	printf("1.手动输入权值\t2.输入字符串，并根据字符频率进行编码\t3.退出");
	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
		{
			printf("\n好像输入错误耶~~请重新输入选择：");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //消除回车

		switch (choice)
		{
		case 1:
			n = PutInWeight(weight, each_letter);
			break;
		case 2:
			printf("请用大写输入字符串(不超过100个字哦~)：");
			gets_s(str, MAX_STR_SIZE + 1);
			n = GetStrWeight(str, weight, each_letter);
			break;
		case 3:
			return;
		}
		if (HuffmanCoding(HTree, HCode, weight, n))
			ReadHCode(HCode, weight, each_letter, n);
	}

	return;
}

int PutInWeight(int* (&weight), char* (&each_line))
{
	int n; //字符个数

	printf("请输入字符个数：");
	scanf("%d", &n);
	each_line = (char*)malloc(sizeof(char) * n);
	weight = (int*)malloc(sizeof(int) * n);
	printf("请输入%d个字符的权值(格式为字母-权值)：\n", n);
	for (int i = 0; i < n; i++)
	{
		while (getchar() != '\n');
		scanf("%c-%d", &each_line[i], &weight[i]);
	}
	
	return n;
}

int GetStrWeight(char* str, int* (&weight), char* (&each_letter))
{
	int i, j, count = 0;
	char *str_ptr; 
	int temp[26] = { 0 }; 

	for (str_ptr = str; *str_ptr != '\0'; str_ptr++)
	{
		if(*str_ptr >= 'A' && *str_ptr <= 'Z')
			temp[*str_ptr - 'A']++;
	}

	for (i = 0, j = 0; i < 26; i++) //数字母个数
		if (temp[i]) count++;
	weight = (int*)malloc(sizeof(int) * count);
	each_letter = (char*)malloc(sizeof(char) * count);

	for (i = 0, j = 0; i < 26; i++)
	{
		if (temp[i])
		{
			weight[j] = temp[i];
			each_letter[j] = i + 'A';
			j++;
		}
	}

	return count;
}

Status HuffmanCoding(HuffmanTree &HTree, HuffmanCode &HCode, int* weight, int n)
{
	if (n <= 1) return ERROR;

	int i;
	int all_code = n + (n - 1);

	HTree = (HuffmanTree)malloc(sizeof(HTNode) * (all_code + 1));
	HCode = (HuffmanCode)malloc(sizeof(char*) * n);
	if (!HTree || !HCode) return ERROR;

	for (i = 1; i <= n; i++)
		HTree[i] = { weight[i - 1], 0, 0, 0 }; //这一步，-1，啊呀！
	for (; i <= all_code; i++)
	{
		int s1, s2; //挑选两个和最小的
		Select(HTree, i - 1, s1, s2);
		HTree[i] = { HTree[s1].weight + HTree[s2].weight, 0, s1, s2 };
		printf("%d、s1 = %d, s2 = %d, 合成权重：%d\n", i, HTree[i].lchild, HTree[i].rchild, HTree[i].weight);
		HTree[s1].parent = HTree[s2].parent = i;
	}

	for (i = 1; i <= n; i++)
	{
		char* temp_code = (char*)malloc(n * sizeof(char));
		temp_code[n - 1] = '\0';
		int start = n - 2;
		int child, parent;
		for (child = i, parent = HTree[i].parent; HTree[child].parent; child = parent, parent = HTree[child].parent)
		{ //每次都拿parent开刀
			if (HTree[parent].lchild == child)
				temp_code[start] = '0';
			else
				temp_code[start] = '1';
			start--;
		}
		HCode[i] = (char*)malloc(sizeof(char) * (n - 1 - start));
		strncpy(HCode[i], temp_code + start + 1, n - 1 - start);
	}
}

Status Select(HuffmanTree HTree, int end, int &s1, int &s2)
{
	int i;
	int min_add, s1_i_add, s2_i_add; //s1s2、s1和i、s2和i的weight分别加起来
	for (s1 = 1; s1 <= end; s1++) //找到第一个parent为0的
	{
		if (HTree[s1].parent == 0)
		{
			for (s2 = s1 + 1; s2 <= end; s2++)
				if (HTree[s2].parent == 0) break;
			break;
		}
	}

	for (i = s2 + 1; i <= end; i++) //循环里面，要保持s1在s2前面
	{
		while (HTree[i].parent != 0) i++;

		min_add = HTree[s1].weight + HTree[s2].weight;
		s1_i_add = HTree[s1].weight + HTree[i].weight;
		s2_i_add = HTree[s2].weight + HTree[i].weight;

		if (s1_i_add < min_add && s1_i_add <= s2_i_add) //s1_i_add最小
		{
			s2 = i;
		}
		else if (s2_i_add < min_add && s2_i_add <= s1_i_add) //s2_i_add最小
		{
			s1 = s2;
			s2 = i;
		}
	}

	return OK;
}

Status ReadHCode(HuffmanCode HCode, int* weight, char *each_letter,int n)
{
	if (!HCode) return ERROR;
	printf("%-5s%-5s%s\n", "字母", "权重", "赫夫曼编码");
	printf("---------------------\n");
	for (int i = 1; i <= n; i++)
	{
		printf("%-5c%-6d", each_letter[i - 1], weight[i - 1]);
		fputs(HCode[i], stdout);
		putchar('\n');
	}
	return OK;
}

Status Visit(BiTNode* (&p))
{
	if (!p) return ERROR;
	printf("%c", p->data);
	return OK;
}

Status CreateSqBiTree(SqBiTree &sa)
{
	printf("请按层序输入：");
	gets_s(sa.elem, MAX_TREE_SIZE);
	for (sa.last = 0; sa.last < MAX_TREE_SIZE && sa.elem[sa.last] != '\0'; sa.last++);
	for (int i = sa.last; i < MAX_STR_SIZE; i++)
		sa.elem[i] = END;
	return OK;
}

Status SqTurnLink(SqBiTree sa, BiTree &T, int i)
{
	if (sa.elem[i] == END || sa.elem[i] == BLANK || sa.elem[i] == '\0')
	{
		T = NULL;
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T)return ERROR;
		T->data = sa.elem[i];
		SqTurnLink(sa, T->lchild, 2 * (i + 1) - 1);
		SqTurnLink(sa, T->rchild, 2 * (i + 1));
	}
	return OK;
}

Status ReverseBiTree(BiTree &T)
{
	if (T)
	{
		BiTNode* temp = T->lchild;
		T->lchild = T->rchild;
		T->rchild = temp;
		ReverseBiTree(T->rchild);
		ReverseBiTree(T->lchild);
	}
	return OK;
}

int CountLeaves(BiTree T)
{
	static int count = 0;
	if (T)
	{
		if ((!T->lchild) && (!T->rchild))
		{
			count++;
		}
		else
		{
			CountLeaves(T->lchild);
			CountLeaves(T->rchild);
		}
	}
	return count;
}

int CountDepth(BiTree T)
{
	if (!T) return 0;
	
	int depthL = CountDepth(T->lchild);
	int depthR = CountDepth(T->rchild);
	
	return (depthL > depthR ? (depthL + 1) : (depthR + 1));
}

Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!Thrt) return ERROR;

	Thrt->LTag = Link;
	Thrt->RTag = Thread;

	if (!T)
	{
		Thrt->lchild = Thrt->rchild = Thrt;
	}
	else
	{
		Thrt->lchild = T;
		BiThrNode* pre = Thrt;
		InThreading(T, pre);
		pre->RTag = Thread;
		pre->rchild = Thrt;
		Thrt->rchild = pre;
	}
	return OK;
}

void InThreading(BiThrNode* p, BiThrNode* (&pre)) //pre是最后要吐出来到InOrderThreading里的，所以取了他的地址
{
	if (p) //总体结构是中序遍历的
	{
		InThreading(p->lchild, pre);
		if ((!p->LTag) && (	!p->lchild))
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if ((!pre->RTag) && (!pre->rchild))
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p; //这一步不可少，因为最后的pre是最后一个元素要输出到InOrderThreading去的
		InThreading(p->rchild, pre);
	}
}

Status InTraverse_Thr(BiThrTree Thrt)
{
	BiThrNode* p = Thrt->lchild;

	while (p != Thrt)
	{
		while (p->LTag == Link) //当有左孩子时，
		{
			p = p->lchild; //可以通过不断判断有没有左孩子，找到最左
		}
		printf("%c", p->data); //现在没有左孩子，可以打印了
		while (p->RTag != Link && p->rchild != Thrt) //当无左孩子，又无右孩子时：则打印根节点
		{
			p = p->rchild; //这两步是找到根结点并打印
			printf("%c", p->data);
		}
		p = p->rchild; //否则访问其右孩子
	}

	return OK;
}

Status PreCreateBiTree(BiTree &T)
{
	ElemType e;
	scanf("%c", &e);

	if (e == BLANK || e == END)
	{
		T = NULL;
	}
	else
	{
		T = (BiTree)malloc(sizeof(BiTNode));
		if (!T) return ERROR;
		T->data = e;
		T->LTag = T->RTag = Link;
		PreCreateBiTree(T->lchild);
		PreCreateBiTree(T->rchild);
	}

	return OK;
}

Status PreTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)))
{
	//printf("先序遍历：");
	if (T)
	{
		if ((*fp)(T))
		{
			PreTraverse(T->lchild, fp);
			PreTraverse(T->rchild, fp);
		}
		else
		{
			return ERROR;
		}
	}
	return OK;
}

Status InTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)))
{
	if (T)
	{
		InTraverse(T->lchild, fp);
		if (!(*fp)(T)) return ERROR;
		InTraverse(T->rchild, fp);
	}
	return OK;
}

Status PostTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)))
{
	if (T)
	{
		PostTraverse(T->lchild, fp);
		PostTraverse(T->rchild, fp);
		if (!(*fp)(T)) return ERROR;
	}
	return OK;
}

Status LevelTraverse(BiTree & T, Status(*fp)(BiTNode *(&p)))
{
	BiTree p = T;
	LinkQueue Q;

	if (!InitQueue(Q)) return ERROR;
	
	EnQueue(Q, p);
	do 
	{
		DeQueue(Q, p);
		(*fp)(p);
		EnQueue(Q, p->lchild);
		EnQueue(Q, p->rchild);
	} while (Q.rear != Q.head);

	return OK;
}

Status InitQueue(LinkQueue &Q)
{
	Q.head = (NQueue*)malloc(sizeof(NQueue));
	if (!Q.head) return ERROR;
	Q.rear = Q.head;
	Q.rear->next = NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{
	if (!e) return OK; //新增：e为空

	NQueue* p = (NQueue*)malloc(sizeof(NQueue));
	if (!p) return ERROR;
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;

	return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{
	if (Q.head == Q.rear) return ERROR;

	NQueue* temp = Q.head->next;
	if (temp == Q.rear) Q.rear = Q.head;
	e = Q.head->next->data;
	Q.head->next = Q.head->next->next;
	free(temp);
	
	return OK;
}
