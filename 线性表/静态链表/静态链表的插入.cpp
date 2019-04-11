
/*获取第一个空闲分量的下标*/
int Malloc_SLL(StaticLinkList space)
{
	int i = space[0].cur;
	if (space[0].cur)
		space[0].cur = space[i].cur;//把下一个分量用来作为备用
	return i;
}

/*在静态链表中的第i个元素前（不是下标i的元素哦）插入一个元素e*/
Status ListInsert(StaticLinkList L, int i, ElementType e)
{
	int j, k, l;

	k = MAX_SIZE - 1;//下标是最后的一个元素，其游标指向第一个有内容的元素哦
	if (i < 0 || i > ListLen(L))
		return ERROR;
	j = Malloc_SLL(L);
	L[j].data = e;
	for (l = 0; l < i - 1; l++)//循环直到k为逻辑上的第i-1个元素
		k = L[k].cur;
	L[j].cur = L[k].cur;
	L[k].cur = j;
}