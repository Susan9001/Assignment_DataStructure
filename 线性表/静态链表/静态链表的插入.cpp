
/*��ȡ��һ�����з������±�*/
int Malloc_SLL(StaticLinkList space)
{
	int i = space[0].cur;
	if (space[0].cur)
		space[0].cur = space[i].cur;//����һ������������Ϊ����
	return i;
}

/*�ھ�̬�����еĵ�i��Ԫ��ǰ�������±�i��Ԫ��Ŷ������һ��Ԫ��e*/
Status ListInsert(StaticLinkList L, int i, ElementType e)
{
	int j, k, l;

	k = MAX_SIZE - 1;//�±�������һ��Ԫ�أ����α�ָ���һ�������ݵ�Ԫ��Ŷ
	if (i < 0 || i > ListLen(L))
		return ERROR;
	j = Malloc_SLL(L);
	L[j].data = e;
	for (l = 0; l < i - 1; l++)//ѭ��ֱ��kΪ�߼��ϵĵ�i-1��Ԫ��
		k = L[k].cur;
	L[j].cur = L[k].cur;
	L[k].cur = j;
}