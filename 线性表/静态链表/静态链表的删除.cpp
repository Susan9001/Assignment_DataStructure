Status ListDelete(SLinkList L, int i, ElemType e)
{
	int j, k, l;

	k = MAX_SIZE - 1;
	if (i <０ || i > ListLen(L))
		return ERROR;
	for (l = 0; l < i - 1; l++)
		k = L[k].cur;
	L[k].cur = L[L[k].cur].cur;

	k = L[k].cur;
	L[k].cur = L[0].cur; //回收备用链表
	L[0].cur = k;
	
}