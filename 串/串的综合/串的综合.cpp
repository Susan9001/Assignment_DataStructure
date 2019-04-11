#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 255
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;
typedef struct HString 
{
	char* ch;
	int length;
}HString;

Status InitStr(HString &T);
Status StrAssign(HString &T, char* chars); //����һ��ֵ����chars������T
int BFSearch(HString Small, HString Big); //�Ҵ����Ҳ���������-1
int StrCompare(HString S, HString T);
Status ClearString(HString &S);
Status Concat(HString &T, HString S1, HString S2);
Status SubString(HString &Sub, HString S, int pos, int len);
Status StrInsert(HString &T, HString S, int pos); //�ڴ�S�ĵ�pos���ַ�ǰ����T
Status Replace(HString &S, HString T, HString V); //�ڴ�S���ҵ��ַ���T�����任ΪV

int main()
{
	HString T, S1, S2, Sub, V;
	int pos, len, choice, temp;
	char* chars = "China!";
	char* temp_str;

	InitStr(S1);
	printf("1.����һ��ֵ����һ�������Ĵ�S2\t2.�ֶ�����һ���ַ���S1\n3.�Ƚ������ַ���\t4.����ַ���\n");
	printf("5.���������ַ�����T\t6.��ȡ�Ӵ�\t7.�滻\n8.�ѳ�����S2�嵽S1��ָ��λ��ǰ   9.�鿴S1\t10.����S1��S2��λ��\n");
	while (true)
	{
		printf("\n����������ѡ��");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 10)
		{
			printf("�����������Ү~~����������ѡ��");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			if (StrAssign(S2, chars))
				fputs(S2.ch, stdout);
			break;
		case 2:
			while (getchar() != '\n');
			temp_str = (char*)malloc(sizeof(char) * MAXSTRLEN);
			printf("�����룺");
			gets_s(temp_str, MAXSTRLEN);
			//fputs(temp_str, stdout);
			if(StrAssign(S1, temp_str))
				fputs(S1.ch, stdout);
			break;
		case 3:
			if (!StrCompare(S1, S2)) printf("��ͬ��");
			else printf("����ͬ~~");
			break;
		case 4:
			if(ClearString(S1))
				printf("����ɹ���");
			break;
		case 5:
			Concat(T, S1, S2);
			fputs(T.ch, stdout);
			break;
		case 6:
			printf("����Ҫ��ȡS1�ַ�����ʲô�ִ�(��ʽ����ʼλ��-����)��");
			scanf("%d-%d", &pos, &len);
			if (SubString(Sub, S1, pos, len) != 1)
				printf("������Ү~~\n");
			else
				fputs(Sub.ch, stdout);
			break;
		case 7:
			while (getchar() != '\n');
			temp_str = (char*)malloc(sizeof(char) * MAXSTRLEN);
			printf("������Ҫ�滻��ʲô�ַ�����");
			gets_s(temp_str, MAXSTRLEN);
			StrAssign(T, temp_str);
			if (BFSearch(T, S1) == -1)
				printf("�Ҳ���Ү~~\n");

			temp_str = (char*)malloc(sizeof(char) * MAXSTRLEN);
			printf("�������µ��ַ�����");
			gets_s(temp_str, MAXSTRLEN);
			StrAssign(V, temp_str);

			if (Replace(S1, T, V))
				fputs(S1.ch, stdout);

			break;
		case 8:
			printf("����Ҫ�嵽ʲôλ��ǰ��");
			scanf("%d", &pos);
			if (StrInsert(S1, S2, pos) != 1)
				printf("������Ү~~\n");
			else
				fputs(S1.ch, stdout);
			break;
		case 9:
			if (!S1.ch) 
				printf("�գ�");
			else 
				fputs(S1.ch, stdout);
			break;
		case 10:
			temp = BFSearch(S2, S1);
			if (temp < 0)
				printf("�Ҳ���~");
			else
				printf("��S1�ĵ�%d��λ��", temp);
			break;
		} //switch
		//putchar('\n');
	} //while

	return 0;
}

Status InitStr(HString &T)
{
	T.ch = NULL;
	T.length = 0;
	return OK;
}

Status StrAssign(HString &T, char* chars) //Ĭ�ϲ�����'\n'
{
	int count = 0;

	//if (T.ch) free(T.ch);
	while (chars[count] != '\0')
		count++;
	count++; //��ʱcount = len(��'\0')
	//printf("count = %d\n", count);

	T.ch = (char*)malloc(count * sizeof(char));
	if (!T.ch) return OVERFLOW;
	for (int i = 0; i < count; i++)
		T.ch[i] = chars[i];
	T.length = count;

	return OK;
}

int StrCompare(HString S, HString T)
{
	for (int i = 0; i < S.length && i < T.length; i++)
	{
		if (S.ch[i] != T.ch[i]) 
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}

Status SubString(HString &Sub, HString S, int pos, int len)
{
	if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos) //�⸴��һ��'\0'Ҳ����
		return ERROR;
	//if (Sub.ch) free(Sub.ch);
	int i;
	if (!len)
	{
		Sub.ch = NULL;
		Sub.length = 0;
	}
	else
	{
		Sub.ch = (char*)malloc(sizeof(char) * (len + 1));
		for (i = 0; i < len; i++)
			Sub.ch[i] = S.ch[pos + i - 1];
		Sub.ch[i] = '\0';
		Sub.length = len + 1; //Ҫ��'\0'Ҳ������
	}
	return OK;
}

int BFSearch(HString Small, HString Big)
{
	if (Big.length < Small.length) return ERROR;

	int i, j;
	HString Sub;

	for (i = 0; i < Big.length - 1; i++)
	{
		if (Big.ch[i] == Small.ch[0])
		{
			if(!SubString(Sub, Big, i + 1, Small.length - 1))
				return -1;
			//Sub.length -= 1;
			if (StrCompare(Sub, Small) == 0)
				return i + 1;
		}
	}
	return -1;
}

Status ClearString(HString &S)
{
	if (S.ch)
	{
		//free(S.ch);
		S.ch = NULL;
	}
	S.length = 0;
	return OK;
}

Status Concat(HString &T, HString S1, HString S2)
{
	//if (T.ch) free(T.ch);
	int i;

	T.ch = (char*)malloc(sizeof(char) * (S1.length + S2.length - 1)); //һ��Ҫȥ��һ��'\0'
	if (!T.ch) return OVERFLOW;
	T.length = S1.length + S2.length - 1;

	for (i = 0; i < S1.length - 1 && S1.ch[i] != '\0'; i++)
		T.ch[i] = S1.ch[i];
	for ( ; i < T.length; i++)
		T.ch[i] = S2.ch[i - (S1.length - 1)];

	return OK;
}


Status StrInsert(HString &S, HString T, int pos)
{
	if (pos < 1 || pos > S.length) return ERROR;
	S.ch = (char*)realloc(S.ch, sizeof(char) * (S.length + T.length - 1));
	if (!S.ch) return OVERFLOW;

	int i;
	for (i = S.length - 1; i >= pos - 1; i--)
		S.ch[i + T.length] = S.ch[i];
	for (i = 0; i < T.length - 1; i++)
		S.ch[pos - 1 + i] = T.ch[i];
	S.length += (T.length - 1); //-1�ǲ�Ҫ'\0'

	return OK;
}

Status Replace(HString &S, HString T, HString V)
{
	if (T.length > S.length)
	{
		printf("��������T��S������~\n");
		return ERROR;
	}

	int i, j;
	int add_len, sub_len; //V��T�����̣�����

	for (i = 0; i < S.length - T.length + 1; i++)
	{
		HString Sub;
		SubString(Sub, S, i + 1, T.length - 1);
		if (StrCompare(Sub, T) == 0)
		{
			if (T.length < V.length)
			{
				add_len = V.length - T.length;
				S.ch = (char*)realloc(S.ch, (S.length + add_len) * sizeof(char));
				if (!S.ch) return OVERFLOW;
				S.length += add_len;
				for (j = S.length - add_len - 1; j >= i + T.length - 1; j--)
					S.ch[j + add_len] = S.ch[j]; //���Ų
			}
			else if (T.length > V.length)
			{
				sub_len = T.length - V.length;
				for (j = i + T.length - 1; j < S.length; j++)
					S.ch[j - sub_len] = S.ch[j]; //��ǰŲ
				S.length -= sub_len;
			}
			for (j = 0; j < V.length - 1; j++)
				S.ch[i + j] = V.ch[j];
			i += (V.length - 2); //-2��һ����V��'\0'����һ���ǵ���i++
		} //ifƥ��ɹ�
	} //for i

	return 1;
}