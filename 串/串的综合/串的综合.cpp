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
Status StrAssign(HString &T, char* chars); //生成一个值等于chars常量的T
int BFSearch(HString Small, HString Big); //找串。找不到，返回-1
int StrCompare(HString S, HString T);
Status ClearString(HString &S);
Status Concat(HString &T, HString S1, HString S2);
Status SubString(HString &Sub, HString S, int pos, int len);
Status StrInsert(HString &T, HString S, int pos); //在串S的第pos个字符前插入T
Status Replace(HString &S, HString T, HString V); //在串S中找到字符串T并将其换为V

int main()
{
	HString T, S1, S2, Sub, V;
	int pos, len, choice, temp;
	char* chars = "China!";
	char* temp_str;

	InitStr(S1);
	printf("1.生成一个值等于一个常量的串S2\t2.手动输入一个字符串S1\n3.比较两个字符串\t4.清除字符串\n");
	printf("5.连接两个字符串至T\t6.获取子串\t7.替换\n8.把常量串S2插到S1的指定位置前   9.查看S1\t10.查找S1在S2中位置\n");
	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 10)
		{
			printf("好像输入错误耶~~请重新输入选择：");
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
			printf("请输入：");
			gets_s(temp_str, MAXSTRLEN);
			//fputs(temp_str, stdout);
			if(StrAssign(S1, temp_str))
				fputs(S1.ch, stdout);
			break;
		case 3:
			if (!StrCompare(S1, S2)) printf("相同！");
			else printf("不相同~~");
			break;
		case 4:
			if(ClearString(S1))
				printf("清除成功！");
			break;
		case 5:
			Concat(T, S1, S2);
			fputs(T.ch, stdout);
			break;
		case 6:
			printf("请问要获取S1字符串的什么字串(格式：起始位置-长度)：");
			scanf("%d-%d", &pos, &len);
			if (SubString(Sub, S1, pos, len) != 1)
				printf("出错了耶~~\n");
			else
				fputs(Sub.ch, stdout);
			break;
		case 7:
			while (getchar() != '\n');
			temp_str = (char*)malloc(sizeof(char) * MAXSTRLEN);
			printf("请输入要替换掉什么字符串：");
			gets_s(temp_str, MAXSTRLEN);
			StrAssign(T, temp_str);
			if (BFSearch(T, S1) == -1)
				printf("找不到耶~~\n");

			temp_str = (char*)malloc(sizeof(char) * MAXSTRLEN);
			printf("请输入新的字符串：");
			gets_s(temp_str, MAXSTRLEN);
			StrAssign(V, temp_str);

			if (Replace(S1, T, V))
				fputs(S1.ch, stdout);

			break;
		case 8:
			printf("请问要插到什么位置前：");
			scanf("%d", &pos);
			if (StrInsert(S1, S2, pos) != 1)
				printf("出错了耶~~\n");
			else
				fputs(S1.ch, stdout);
			break;
		case 9:
			if (!S1.ch) 
				printf("空！");
			else 
				fputs(S1.ch, stdout);
			break;
		case 10:
			temp = BFSearch(S2, S1);
			if (temp < 0)
				printf("找不到~");
			else
				printf("在S1的第%d个位置", temp);
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

Status StrAssign(HString &T, char* chars) //默认不包含'\n'
{
	int count = 0;

	//if (T.ch) free(T.ch);
	while (chars[count] != '\0')
		count++;
	count++; //此时count = len(算'\0')
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
	if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos) //光复制一个'\0'也不行
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
		Sub.length = len + 1; //要把'\0'也算上了
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

	T.ch = (char*)malloc(sizeof(char) * (S1.length + S2.length - 1)); //一定要去掉一个'\0'
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
	S.length += (T.length - 1); //-1是不要'\0'

	return OK;
}

Status Replace(HString &S, HString T, HString V)
{
	if (T.length > S.length)
	{
		printf("出错啦！T比S还还长~\n");
		return ERROR;
	}

	int i, j;
	int add_len, sub_len; //V比T长（短）多少

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
					S.ch[j + add_len] = S.ch[j]; //向后挪
			}
			else if (T.length > V.length)
			{
				sub_len = T.length - V.length;
				for (j = i + T.length - 1; j < S.length; j++)
					S.ch[j - sub_len] = S.ch[j]; //往前挪
				S.length -= sub_len;
			}
			for (j = 0; j < V.length - 1; j++)
				S.ch[i + j] = V.ch[j];
			i += (V.length - 2); //-2中一个是V的'\0'，另一个是抵消i++
		} //if匹配成功
	} //for i

	return 1;
}