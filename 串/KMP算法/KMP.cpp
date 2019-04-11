#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSTRLEN 255

typedef int Status;
typedef char ElemType;
typedef ElemType SString[MAXSTRLEN + 1]; //0号元素存放长度

Status StrAssign(SString &T, char* chars); //此处规定：'\0'不算在长度里面！！
void get_next(SString T, int *next);
int Index_KMP(SString S, SString T, int pos);

int main()
{
	SString S, T;
	int pos, choice, temp;
	char *chars = "abaabcac";
	char *temp_str;

	printf("1.生成一个值等于一个常量的串T\t2.手动输入一个字符串S\n3.查找T在S中的位置\t4.清除字符串\n");
	while (true)
	{
		printf("\n请输入您的选择：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
		{
			printf("好像输入错误耶~~请重新输入选择：");
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
			printf("请输入：");
			gets_s(temp_str, MAXSTRLEN);
			//fputs(temp_str, stdout);
			if (StrAssign(S, temp_str))
				fputs(S, stdout);
			break;
		case 3:
			printf("从第几个字符开始查找呢：");
			scanf("%d", &pos);
			temp = Index_KMP(S, T, pos);
			if (!temp)
				printf("找不到耶~~\n");
			else
				printf("位置为：%d\n", temp);
			break;
		} //switch
	}//while

	return 0;
}

Status StrAssign(SString &T, char* chars)
{
	int i;

	for (i = 0; chars[i] != '\0'; i++); //加到'\0'；算多了'\0'，则恰好抵消了i初始化为0
	T[0] = i;
	printf("长度 = %d\n", T[0]);

	for (i = 1; i <= T[0] + 1; i++) //要把'\0'也加进去，所以有个小于等于
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
		if (T[tar] == T[k + 1] ) //这个if-else是改进了的；
			next[tar] = next[k + 1];
		else
			next[tar] = k + 1; //未改进前只有这个
	}
*/

	while (pre < T[0]) {
		if (k == 0 || T[pre] == T[k]) {
			printf("pre = %d\tk = %d\t", pre, k);
			pre++;
			k++;
			printf("pre后= %d\tk后 = %d\n ", pre, k);

			next[pre] = k;
			if (T[pre] == T[k]) //提早判断了一次
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
	printf("next数组为：");
	for (i = 1; i <= next[0]; i++)
		printf("%-3d", next[i]);
	putchar('\n');

	for (i = pos, j = 1; i <= S[0] && j <= T[0]; i++)
	{
		while (T[j] != S[i] && j != 1) //直到匹配或者到了1
			j = next[j];
		if (T[j] == S[i]) 
			j++;
	}
	if (j == T[0] + 1)
		return i - (j - 1);
	else 
		return 0;
}
