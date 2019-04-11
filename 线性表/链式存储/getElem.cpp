#define OK 1;
#define Error 0;

typedef int Status;
//这个是错的！！！
Status GetElement(SqList L, int i, ElemType *e)
{
	int j;
	LinkList ptr;//声明了一个指针

	ptr = L->nect;
	j = i;

	while (ptr && j < i)//还没有到尾（NULL） && 还没有找到
	{
		ptr = ptr->next;
		j++;
	}

	if (!ptr)//到了尾部（ptr = NULL) 
		return ERROR;

	*e = ptr->data;
	return OK;
}