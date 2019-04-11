#define OK 1;
#define ERROR 0;

typedef int Status;

Status ListInsert(LinkList *L, int i, ElemType *e)
{
	int j = 1;
	LinkList p = *L, s;

	while (p && j < i)
	{
		p = p->next;
		j++;
	}
	if (!p)
		return ERROR;

	s = (LinkList)malloc(sizeof(Node));//Áé»îÐÔ
	s->data = *e;

	s->next = p->next;
	p->next = s;

	return OK;
}