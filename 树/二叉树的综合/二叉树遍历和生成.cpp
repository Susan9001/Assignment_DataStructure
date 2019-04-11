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

/*˳�������*/
typedef struct _SqBiTree {
	ElemType elem[MAX_TREE_SIZE];
	int last; //Ԫ�ظ�����Ҳ�����һ��Ԫ�ص��±�
}SqBiTree;

/*����������(�ڴ˹涨��ȫ��������tagΪ0����ʾ��ͨ������)*/
typedef enum PointerTag { 
	Link = 0, Thread = 1 
};
typedef struct _biTNode {
	ElemType data;
	struct _biTNode *lchild, *rchild;
	PointerTag LTag, RTag;
}BiTNode, BiThrNode, *BiTree, *BiThrTree;

/*�շ������ͺշ�������*/
typedef struct _HTNode {
	int weight;
	int parent;
	int lchild;
	int	rchild;
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;

/*������(���ڲ������)*/
typedef BiTNode* QElemType;
typedef struct _nQueue {
	QElemType data;
	_nQueue* next;
}NQueue;
typedef struct _linkQueue {
	NQueue* head; //��ͷ��
	NQueue* rear;
}LinkQueue;

/*��ͨ���������ɺͱ����޸�*/
Status PreCreateBiTree(BiTree &T);
Status PreTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
Status InTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
Status PostTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
Status LevelTraverse(BiTree &T, Status(*fp)(BiTNode* (&p)));
//�����������Ҫ�Ķ��в���
Status InitQueue(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);
/*����������*/
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T);
void InThreading(BiThrNode* p, BiThrNode* (&pre));
Status InTraverse_Thr(BiThrTree Thrt);
/*�շ��������*/
void HuffmanCodeTest(); //����˺շ�������ص���������
int GetStrWeight(char* str, int* (&weight), char* (&eachLetter)); //�����ַ����������ж�������ĸ��Ȩ������
int PutInWeight(int* (&weight), char* (&eacn_line));//���벢�����ж�������ĸ�Ͷ�Ӧ��Ȩֵ
Status HuffmanCoding(HuffmanTree &HTree, HuffmanCode &HCode, int* weight, int n);
Status Select(HuffmanTree HTree, int end, int &s1, int &s2); //�ҳ�HTree�±��1��end֮�����֮����С����
Status ReadHCode(HuffmanCode HCode, int* weight, char* eachLetter,int n);
/*��������*/
Status Visit(BiTNode* (&p));
Status ReverseBiTree(BiTree &T); //��ת��������ͨ����������㷨?��
int CountLeaves(BiTree T); //����Ҷ�ӽ������������static 
int CountDepth(BiTree T); //������������
Status CreateSqBiTree(SqBiTree &sa); //����˳��洢�Ķ�����
Status SqTurnLink(SqBiTree sa, BiTree &T, int i); //������˳��ת����

int main()
{
	BiTree T = NULL, Thrt = NULL;
	SqBiTree sa;
	int choice;

	printf("1.������������� 2.�������     3.�������     4.�������\n");
	printf("5.������������   6.����������ת 7.����Ҷ����� 8.�������\n");
	printf("9.�������������˳��洢��ת��Ϊ��ʽ������     10.�������\n");
	printf("11.�շ�������    12.�˳�\n");

	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 11)
		{
			printf("\n�����������Ү~~����������ѡ��");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //�����س�

		switch (choice)
		{
		case 1:
			if (T) free(T);
			printf("�밴��������(#�ſ�Ҷ��$�Ž���)��");
			if (PreCreateBiTree(T))
			{
				printf("��/��/����");
				PreTraverse(T, Visit);
				printf(", ");
				InTraverse(T, Visit);
				printf(", ");
				PostTraverse(T, Visit);
			}
			putchar('\n');
			break;
		case 2:
			printf("���������");
			PreTraverse(T, Visit);
			putchar('\n');
			break;
		case 3:
			printf("���������");
			InTraverse(T, Visit);
			putchar('\n');
			break;
		case 4:
			printf("���������");
			PostTraverse(T, Visit);
			putchar('\n');
			break;
		case 5:
			if (InOrderThreading(Thrt, T))
			{
				printf("�������������ɹ���");
				InTraverse_Thr(Thrt);
			}
			putchar('\n');
			break;
		case 6:
			if (ReverseBiTree(T))
			{
				printf("hhhh��ת�ɹ���\n");
				printf("��/��/����");
				PreTraverse(T, Visit);
				printf(", ");
				InTraverse(T, Visit);
				printf(", ");
				PostTraverse(T, Visit);
			}
			putchar('\n');
			break;
		case 7:
			printf("�õ���Ҷ����Ϊ��%d\n", CountLeaves(T));
			break;
		case 8:
			printf("��ǰ���Ϊ��%d\n", CountDepth(T));
			break;
		case 9:
			if (CreateSqBiTree(sa))
			{
				if (T) free(T);
				SqTurnLink(sa, T, 0);
				printf("��/��/����");
				PreTraverse(T, Visit);
				printf(", ");
				InTraverse(T, Visit);
				printf(", ");
				PostTraverse(T, Visit);
			}
			break;
		case 10:
			printf("���������");
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
	char* each_letter; //�����ַ���
	int* weight;
	int n; //�ַ�����
	int choice;
	HuffmanCode HCode = NULL;
	HuffmanTree HTree = NULL;

	printf("1.�ֶ�����Ȩֵ\t2.�����ַ������������ַ�Ƶ�ʽ��б���\t3.�˳�");
	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
		{
			printf("\n�����������Ү~~����������ѡ��");
			while (getchar() != '\n');
		}
		while (getchar() != '\n'); //�����س�

		switch (choice)
		{
		case 1:
			n = PutInWeight(weight, each_letter);
			break;
		case 2:
			printf("���ô�д�����ַ���(������100����Ŷ~)��");
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
	int n; //�ַ�����

	printf("�������ַ�������");
	scanf("%d", &n);
	each_line = (char*)malloc(sizeof(char) * n);
	weight = (int*)malloc(sizeof(int) * n);
	printf("������%d���ַ���Ȩֵ(��ʽΪ��ĸ-Ȩֵ)��\n", n);
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

	for (i = 0, j = 0; i < 26; i++) //����ĸ����
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
		HTree[i] = { weight[i - 1], 0, 0, 0 }; //��һ����-1����ѽ��
	for (; i <= all_code; i++)
	{
		int s1, s2; //��ѡ��������С��
		Select(HTree, i - 1, s1, s2);
		HTree[i] = { HTree[s1].weight + HTree[s2].weight, 0, s1, s2 };
		printf("%d��s1 = %d, s2 = %d, �ϳ�Ȩ�أ�%d\n", i, HTree[i].lchild, HTree[i].rchild, HTree[i].weight);
		HTree[s1].parent = HTree[s2].parent = i;
	}

	for (i = 1; i <= n; i++)
	{
		char* temp_code = (char*)malloc(n * sizeof(char));
		temp_code[n - 1] = '\0';
		int start = n - 2;
		int child, parent;
		for (child = i, parent = HTree[i].parent; HTree[child].parent; child = parent, parent = HTree[child].parent)
		{ //ÿ�ζ���parent����
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
	int min_add, s1_i_add, s2_i_add; //s1s2��s1��i��s2��i��weight�ֱ������
	for (s1 = 1; s1 <= end; s1++) //�ҵ���һ��parentΪ0��
	{
		if (HTree[s1].parent == 0)
		{
			for (s2 = s1 + 1; s2 <= end; s2++)
				if (HTree[s2].parent == 0) break;
			break;
		}
	}

	for (i = s2 + 1; i <= end; i++) //ѭ�����棬Ҫ����s1��s2ǰ��
	{
		while (HTree[i].parent != 0) i++;

		min_add = HTree[s1].weight + HTree[s2].weight;
		s1_i_add = HTree[s1].weight + HTree[i].weight;
		s2_i_add = HTree[s2].weight + HTree[i].weight;

		if (s1_i_add < min_add && s1_i_add <= s2_i_add) //s1_i_add��С
		{
			s2 = i;
		}
		else if (s2_i_add < min_add && s2_i_add <= s1_i_add) //s2_i_add��С
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
	printf("%-5s%-5s%s\n", "��ĸ", "Ȩ��", "�շ�������");
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
	printf("�밴�������룺");
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

void InThreading(BiThrNode* p, BiThrNode* (&pre)) //pre�����Ҫ�³�����InOrderThreading��ģ�����ȡ�����ĵ�ַ
{
	if (p) //����ṹ�����������
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
		pre = p; //��һ�������٣���Ϊ����pre�����һ��Ԫ��Ҫ�����InOrderThreadingȥ��
		InThreading(p->rchild, pre);
	}
}

Status InTraverse_Thr(BiThrTree Thrt)
{
	BiThrNode* p = Thrt->lchild;

	while (p != Thrt)
	{
		while (p->LTag == Link) //��������ʱ��
		{
			p = p->lchild; //����ͨ�������ж���û�����ӣ��ҵ�����
		}
		printf("%c", p->data); //����û�����ӣ����Դ�ӡ��
		while (p->RTag != Link && p->rchild != Thrt) //�������ӣ������Һ���ʱ�����ӡ���ڵ�
		{
			p = p->rchild; //���������ҵ�����㲢��ӡ
			printf("%c", p->data);
		}
		p = p->rchild; //����������Һ���
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
	//printf("���������");
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
	if (!e) return OK; //������eΪ��

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
