#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;
typedef struct OLNode
{
	int i;
	int j;
	ElemType e;
	struct OLNode *right, *down;
}OLNode, *OLink;
typedef struct CrossList
{
	OLink *rhead, *chead;
	int mu, nu, tu;
}CrossLink;

Status CreateSMatrix_OL(CrossLink &M);
Status ReadSMatirx_OL(CrossLink M);
Status AddSMatrix_OL(CrossLink &A, CrossLink B);

int main()
{
	CrossLink M, N;

	printf("第一个矩阵：\n");
	if(CreateSMatrix_OL(M))
		ReadSMatirx_OL(M);

	printf("\n第二个矩阵：\n");
	if (CreateSMatrix_OL(N))
		ReadSMatirx_OL(N);

	if (AddSMatrix_OL(M, N))
	{
		printf("\n相加了之后：\n");
		ReadSMatirx_OL(M);
	}
	else
	{
		printf("不成功~~\n");
	}

	return 0;
}

Status CreateSMatrix_OL(CrossLink &M)
{
	int k, i, j;
	char flag;

	printf("请输入该矩阵行、列、几个非零元素(mu-nu-tu):");
	scanf("%d-%d-%d", &M.mu, &M.nu, &M.tu);
	M.rhead = (OLNode**)malloc((M.mu + 1) * sizeof(OLNode*));
	M.chead = (OLNode**)malloc((M.nu + 1) * sizeof(OLNode*));
	if (!M.rhead || !M.chead) return ERROR;

	for (k = 0; k < M.mu + 1; k++) M.rhead[k] = NULL;
	for (k = 0; k < M.nu + 1; k++) M.chead[k] = NULL;

	printf("进行输入~~(行-列-元素,第一行一定非空哦~)\n");
	for (k = 0; k < M.tu; k++)
	{
		OLNode *p = (OLNode*)malloc(sizeof(OLNode));
		if (!p) return ERROR;

		printf("第%d个非零元素：", k + 1);
		scanf("%d-%d-%d",&(p->i), &(p->j), &(p->e));
		if (p->i == 0) return OK;

		if (M.rhead[p->i] == NULL || M.rhead[p->i]->j > p->j)
		{
			p->right = M.rhead[p->i];
			M.rhead[p->i] = p;
		}
		else 
		{
			OLNode *q;
			for (q = M.rhead[p->i]; (q->right) && q->right->j < p->j; q = q->right);
			p->right = q->right;
			q->right = p;
		}

		if (M.chead[p->j] == NULL || M.chead[p->j]->i > p->i)
		{
			p->down = M.chead[p->j];
			M.chead[p->j] = p;
		}
		else
		{
			OLNode *q;
			for (q = M.chead[p->j]; (q->down) && q->down->i < p->i; q = q->down);
			p->down = q->down;
			q->down = p;
		}
	}//for k

	return OK;
}

Status ReadSMatirx_OL(CrossLink M)
{
	if (!M.tu) return ERROR;

	int i, j, k = 0;
	OLNode *rh, *p;

	for (k = 1; k <= M.mu; k++)
	{
		if (M.rhead[k])
		{
			printf("第%d行：", k);
			for (p = M.rhead[k]; p->right; p = p->right)
				printf("%d(%d), ", p->e, p->j);
			printf("%d(%d)\n", p->e, p->j);
		}
	}

	return OK;
}

Status AddSMatrix_OL(CrossLink &A, CrossLink B)
{
	if (A.mu != B.mu || A.nu != B.nu) return ERROR;

	OLNode *pa, *pb, *pre;
	OLNode **hl = (OLNode**)malloc(sizeof(OLNode*) * A.nu);
	if (!hl) return ERROR;
	for (int j = 1; j <= A.nu; j++) hl[j] = A.chead[j];
	//OLNode *hl;
	
	for (int k = 1; k <= B.mu; k++)
	{
		pb = B.rhead[k];
		pa = A.rhead[k];
		pre = NULL;

		while (pb)
		{
			if (!pa || pa->j > pb->j) //添加
			{
				OLNode *p = (OLNode*)malloc(sizeof(OLNode));
				if (!p) return ERROR;
				p->j = pb->j;
				p->i = pb->i;
				p->e = pb->e;
				A.tu++;
				
				/*搞行(right)*/
				p->right = pa; //这一步写在这里更加简约！
				if (!pre) A.rhead[k] = p; 
				else pre->right = p; //把新的跟前面的进行联系	
				pre = p; //链表插入操作必备：把pre指针移到新插的地方
				
				/*搞列(down)*/
				if (!A.chead[p->j] || A.chead[p->j]->i > p->i)
				{
					p->down = A.chead[p->j];
					A.chead[p->j] = p;
				}
				else
				{
					for (; hl[p->j]->down != NULL && hl[p->j]->down->i < p->i ; hl[p->j] = hl[p->j]->down);
					p->down = hl[p->j]->down;
					hl[p->j]->down = p;
					hl[p->j] = p;
					/*for (hl = A.chead[p->j]; hl->down != NULL && hl->down->i < p->i; hl = hl->down);
					p->down = hl->down;
					hl->down = p;*/
				}
				pb = pb->right;
			}
			else if (pa->j < pb->j)
			{
				pre = pa; //1、不能pre = pre->right，因为一开始为NULL 2、顺序！
				pa = pa->right;
			}
			else if (pa->j == pb->j && pa->e + pb->e != 0)
			{
				pa->e += pb->e;
				pre = pa; //1、不能pre = pre->right，因为一开始为NULL 2、顺序！
				pa = pa->right;
				pb = pb->right;			
			}
			else //(pa->j == pb->j && pa->e + pb->e == 0)，删pa
			{
				OLNode* p = pa;
				pa = pa->right; //pa先走一步了，留下p代表原a
				pb = pb->right;
				A.tu--;
				
				/*搞行(right)*/
				if (!pre) A.rhead[k] = A.rhead[k]->right;
				else pre->right = p->right;		
				
				/*搞列(down)*/
				if (A.chead[p->j] == p)
				{
					A.chead[p->j] = p->down;
				}
				else
				{
					for ( ; hl[p->j]->down != NULL && hl[p->j]->down->i < p->i; hl[p->j] = hl[p->j]->down);
					hl[p->j]->down = p->down;
					/*for (hl = A.chead[p->j];  hl->down != NULL && hl->down->i < p->i; hl = hl->down);
					hl->down = p->down;*/
				}
				free(p);
			}//last else
		}//while pb
	}//for k

	return OK;
}