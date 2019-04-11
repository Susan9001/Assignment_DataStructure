#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 12500
#define M_ROW 3
#define M_COLUMN 4
#define N_ROW 3
#define N_COLUMN 4
#define MAX_ROW 15 //最多不超过15行

typedef int Status;
typedef int ElemType;

typedef struct _triple
{
	int i;
	int j;
	ElemType e;
}Triple;
typedef struct _RTSMatrix
{
	Triple data[MAXSIZE + 1]; //凡是+1，必定第一个不放东西
	int rpos[MAX_ROW + 1]; //每一行
	int mu, nu, tu;
}RTSMatrix;

Status CreatRTSMatirx(ElemType **M0 , RTSMatrix &M, int m_row, int m_column); //RTSMatrix &N
Status MultSMatrix(RTSMatrix &M, RTSMatrix &N, RTSMatrix &Q);
Status AddSMatrix(RTSMatrix M, RTSMatrix N, RTSMatrix &Q);
Status ReadRTSMatrix(RTSMatrix M);
Status FastTranspose(RTSMatrix M, RTSMatrix &T);

int main()
{
	ElemType MT[M_ROW][M_COLUMN] = { { 2, 0, 0, 5 },{ 0, 0, 0, 0 },{ 2, 0, 0, 0 } };
	ElemType NT[N_ROW][N_COLUMN] = { { 0, 2, 0, 1 },{ 1, 0, 0, 0 },{ -2, 4, 0, 0} };

	RTSMatrix M, N, Q;
	ElemType **M0, **N0;

	M0 = (ElemType**)malloc(sizeof(ElemType*) * M_ROW);
	N0 = (ElemType**)malloc(sizeof(ElemType*) * N_ROW);
	for (int i = 0; i < M_COLUMN; i++) //这都可以？！
		M0[i] = MT[i];
	for (int i = 0; i < N_COLUMN; i++)
		N0[i] = NT[i];
	
	if (CreatRTSMatirx(M0, M, M_ROW, M_COLUMN) && CreatRTSMatirx(N0, N, N_ROW, N_COLUMN))
	{
		printf("M:");
		ReadRTSMatrix(M);
		printf("\nN:");
		ReadRTSMatrix(N);
	}

	/*printf("\n转置后：\n");
	if(FastTranspose(M, T1))
		ReadRTSMatrix(T1);*/

	if (AddSMatrix(M, N, Q))
	{
		printf("加之后：");
		ReadRTSMatrix(Q);
	}
	else
		printf("出错了耶~~\n");

	return 0;
}

Status CreatRTSMatirx(ElemType **M0, RTSMatrix &M, int m_row, int m_column)
{
	int cur_i, cur_j;
	int line_num = 0; //每一行非0的个数，用于统计每行第一个非0元素的位置

	M.tu = 0;
	M.mu = m_row;
	M.nu = m_column;
	
	for (cur_i = 0; cur_i < M.mu; cur_i++)
	{
		for (cur_j = 0; cur_j < M.nu; cur_j++)
		{
			if (M0[cur_i][cur_j])
			{
				M.tu++;
				if (!line_num) //甚至不用first_line了！
					M.rpos[cur_i + 1] = M.tu;
				line_num++;
				if (M.tu > MAXSIZE) return ERROR;
				M.data[M.tu] = { cur_i + 1, cur_j + 1, M0[cur_i][cur_j] };
			} 
		} //for 列
		if (!line_num) 
			M.rpos[cur_i + 1] = M.tu + 1;
		line_num = 0;
	} //for 行

	return OK;
}

Status AddSMatrix(RTSMatrix M, RTSMatrix N, RTSMatrix &Q)
{
	if (M.mu != N.mu || M.nu != N.nu) return ERROR;

	int m = 1, n = 1, q = 1;

	Q.mu = M.mu;
	Q.nu = M.nu;
	while (m <= M.tu && n <= N.tu)
	{
		if (M.data[m].i == N.data[n].i && M.data[m].j == N.data[n].j)
		{
			if (M.data[m].e + N.data[n].e != 0)
				Q.data[q++] = { M.data[m].i, M.data[m].j, (M.data[m].e + N.data[n].e) };
			m++;
			n++;
		}
		else if ((N.data[n].i < M.data[m].i) || (N.data[n].i == M.data[m].i && N.data[n].j < M.data[m].j)) //N在M前面
			Q.data[q++] = N.data[n++];
		else
			Q.data[q++] = M.data[m++];
	}//while
	while (m > M.tu && n <= N.tu)
		Q.data[q++] = N.data[n++];
	while (n > N.tu && m <= M.tu)
		Q.data[q++] = M.data[m++];
	Q.tu = q - 1;

	return OK;
}

Status ReadRTSMatrix(RTSMatrix M)
{
	int p;
	printf("\nmu = %d\tnu = %d\ttu = %d\n", M.mu, M.nu, M.tu);
	printf("i\tj\te\n");
	printf("-------------------\n");
	for (p = 1; p <= M.tu; p++)
		printf("%d\t%d\t%d\n", M.data[p].i, M.data[p].j, M.data[p].e);
	/*for (p = 1; p <= M.mu; p++)
		printf("第%d行：%-3d\n", p, M.rpos[p]);*/

	return OK;
}

Status FastTranspose(RTSMatrix M, RTSMatrix &T)
{
	int p, q, k;

	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if (T.tu)
	{
		int *num = (int*)malloc(sizeof(int) * T.mu);
		for (int j = 0; j < T.mu; j++)
			num[j] = 0;
		for (p = 1; p <= M.tu; p++)
			num[M.data[p].j]++;

		int *col = (int*)malloc(sizeof(int) * T.mu);
		col[1] = 1;
		for (p = 2; p <= T.mu; p++)
			col[p] = col[p - 1] + num[p - 1];

		for (p = 1; p <= M.tu; p++)
		{
			k = M.data[p].j;
			q = col[k];
			T.data[q] = { M.data[p].j, M.data[p].i, M.data[p].e };
			col[k]++;
		}
		return OK;
	}

	else 
		return ERROR;
}
