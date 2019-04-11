//单链表整表删除
#define OK 1
#define ERROR 0

void DeleteList(LinkList *L, int n)
{
	LinkList p, q;
	int i;

	p = (*L)->next;

	while (!p->next)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(p);
	(*L)->next = NULL;//表示这是一个空表了
	
	return OK;
}