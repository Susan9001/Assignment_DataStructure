#define ERROE 0;
#define OK 1;

typedef int Status;
Status ListDelete(LinkList *L, int i, ElemType e)
{
	int j = 1;
	LinkList p = *L, s;//p��head��ʼ
	s = (LinkList)malloc(sizeof(Node));

	//��Ѱ��
	while (p->next && j < i)
	{
		p = p->next;
		j++;//ѭ��ִ����i-1�Σ�Ҳ����˵pֻ����ai-1(?)
	}
	if (!p->next)
		return ERROE;

	//�ȵ�p����ai-1(?)����nextָ��ai�ڵ�(���Ǵ�ɾ�����Ǹ�����ʱ��
	e = p->next->data;
	p->next = p->next->next;
	return e;

}