#define OK 1;
#define Error 0;

typedef int Status;
//����Ǵ�ģ�����
Status GetElement(SqList L, int i, ElemType *e)
{
	int j;
	LinkList ptr;//������һ��ָ��

	ptr = L->nect;
	j = i;

	while (ptr && j < i)//��û�е�β��NULL�� && ��û���ҵ�
	{
		ptr = ptr->next;
		j++;
	}

	if (!ptr)//����β����ptr = NULL) 
		return ERROR;

	*e = ptr->data;
	return OK;
}