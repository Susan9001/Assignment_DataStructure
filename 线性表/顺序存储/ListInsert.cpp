#define FALSE 0
#define ERROR 0
#define OK 1

typedef int ListInsert(SqList L, int i, ElemType e)
{
	register int j, temp;

	if (ListLen(L) == 0 || ListLen(L) == MAX || i-1 > ListLen(L) || i < 1)
		//��ʾ��Ч�����Ѿ����˻���Ϊ0��i�����˻���С��1��return������
		return FALSE;

	if (i - 1 < ListLen(L))//����Ĳ���ListLen(L)λ�ã��Ͳ��ö�����Ų��
	{
		for (j = ListLen(L); j > i - 1; j--)//����λ�ã�ǰ��ĸ��Ǻ����
			L[j] = L[j - 1];
	}

	L[i - 1] = e;
	ListLen(L)++;
	return OK;
}