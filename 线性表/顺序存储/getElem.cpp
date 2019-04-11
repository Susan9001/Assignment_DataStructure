#define ERROR 0
#define OK 1
#define FALSE 0

typedef int Status;

Status getElem(SqList L, int i, ElemType *e)
{
	if (i < 1 || ListLen(L) == 0 || i > ListLen(L))
		return FALSE;
	e = &L[i - 1];
	return OK;
}