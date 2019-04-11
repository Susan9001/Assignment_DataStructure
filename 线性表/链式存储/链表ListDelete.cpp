#define ERROE 0;
#define OK 1;

typedef int Status;
Status ListDelete(LinkList *L, int i, ElemType e)
{
	int j = 1;
	LinkList p = *L, s;//p从head开始
	s = (LinkList)malloc(sizeof(Node));

	//先寻找
	while (p->next && j < i)
	{
		p = p->next;
		j++;//循环执行了i-1次，也就是说p只到了ai-1(?)
	}
	if (!p->next)
		return ERROE;

	//等到p还在ai-1(?)并且next指向ai节点(就是待删除的那个）的时候
	e = p->next->data;
	p->next = p->next->next;
	return e;

}