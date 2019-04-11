#define FALSE 0
#define ERROR 0
#define OK 1

typedef int ListInsert(SqList L, int i, ElemType e)
{
	register int j, temp;

	if (ListLen(L) == 0 || ListLen(L) == MAX || i-1 > ListLen(L) || i < 1)
		//表示有效长度已经满了或者为0、i大了了或者小于1，return不正常
		return FALSE;

	if (i - 1 < ListLen(L))//插入的不是ListLen(L)位置，就不用都往后挪啦
	{
		for (j = ListLen(L); j > i - 1; j--)//调换位置，前面的覆盖后面的
			L[j] = L[j - 1];
	}

	L[i - 1] = e;
	ListLen(L)++;
	return OK;
}