#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSTRLEN 255

typedef int Status;
typedef char ElemType;
typedef ElemType SString[MAXSTRLEN + 1]; //0��Ԫ�ش�ų���

Status StrAssign(SString &T, char* chars); //�˴��涨��'\0'�����ڳ������棡��
void get_next(SString T, int *next);
int Index_KMP(SString S, SString T, int pos);

int main()
{
	SString S, T;
	int pos, choice, temp;
	char *chars = "abaabcac";
	char *temp_str;

	printf("1.����һ��ֵ����һ�������Ĵ�T\t2.�ֶ�����һ���ַ���S\n3.����T��S�е�λ��\t4.����ַ���\n");
	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
		{
			printf("�����������Ү~~����������ѡ��");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			if(StrAssign(T, chars))
				fputs(T, stdout);
			break;
		case 2:
			while (getchar() != '\n');
			temp_str = (char*)malloc(sizeof(char) * MAXSTRLEN);
			printf("�����룺");
			gets_s(temp_str, MAXSTRLEN);
			//fputs(temp_str, stdout);
			if (StrAssign(S, temp_str))
				fputs(S, stdout);
			break;
		case 3:
			printf("�ӵڼ����ַ���ʼ�����أ�");
			scanf("%d", &pos);
			temp = Index_KMP(S, T, pos);
			if (!temp)
				printf("�Ҳ���Ү~~\n");
			else
				printf("λ��Ϊ��%d\n", temp);
			break;
		} //switch
	}//while

	return 0;
}

Status StrAssign(SString &T, char* chars)
{
	int i;

	for (i = 0; chars[i] != '\0'; i++); //�ӵ�'\0'�������'\0'����ǡ�õ�����i��ʼ��Ϊ0
	T[0] = i;
	printf("���� = %d\n", T[0]);

	for (i = 1; i <= T[0] + 1; i++) //Ҫ��'\0'Ҳ�ӽ�ȥ�������и�С�ڵ���
		T[i] = chars[i - 1];
	return OK;
}

void get_next(SString T, int *next)
{
	int tar = 1, k = 0, pre = 1;
	next[tar] = 0;

/*	for (tar = 2; tar <= T[0]; tar++)
	{
		pre = tar - 1;
		k = next[pre];
		
		//printf("tar = %d, T[pre] = %c, T[k] = %c\n", tar, T[pre], T[k]);
		while (T[pre] != T[k] && k != 0)
		{
			k = next[k];
		}
		printf("k + 1 = %d\n", k + 1);
		if (T[tar] == T[k + 1] ) //���if-else�ǸĽ��˵ģ�
			next[tar] = next[k + 1];
		else
			next[tar] = k + 1; //δ�Ľ�ǰֻ�����
	}
*/

	while (pre < T[0]) {
		if (k == 0 || T[pre] == T[k]) {
			printf("pre = %d\tk = %d\t", pre, k);
			pre++;
			k++;
			printf("pre��= %d\tk�� = %d\n ", pre, k);

			next[pre] = k;
			if (T[pre] == T[k]) //�����ж���һ��
				next[pre] = next[k];
		}
		else k = next[k];
	}
}

int Index_KMP(SString S, SString T, int pos)
{
	int i, j;
	int* next;

	next = (int*)malloc(sizeof(int) * T[0]);
	next[0] = T[0];
	get_next(T, next);
	printf("next����Ϊ��");
	for (i = 1; i <= next[0]; i++)
		printf("%-3d", next[i]);
	putchar('\n');

	for (i = pos, j = 1; i <= S[0] && j <= T[0]; i++)
	{
		while (T[j] != S[i] && j != 1) //ֱ��ƥ����ߵ���1
			j = next[j];
		if (T[j] == S[i]) 
			j++;
	}
	if (j == T[0] + 1)
		return i - (j - 1);
	else 
		return 0;
}
