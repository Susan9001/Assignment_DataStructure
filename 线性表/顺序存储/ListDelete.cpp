#define OK 1;
#define Error 0;

typedef int Status;

Status ListDelete(SqList L, int i, ElemType e)
{
	register int temp, j;

	if (ListLen(L) == 0)
		return Error;
	if (i - 1 < 0 || i > ListLen[L])
		return Error;

	*e = L[i - 1];
	if (i < ListLen[L])
	{
		for (j = i - 1; j < ListLen(L) - 1; j++)
			L[j] = L[j + 1];
	}

	ListLen(L)--;
	return OK;
}