//������������
//ͷ��
void CreatListHead(LinkList *L, int n)
{
	LinkList p;//p���н�ڵ�
	int i;

	srand(time(0));

	//����һ��ָ��ָ��ڵ�
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;

	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand();
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

//β��
void CreatListTail(LinkList *L, int n)
{
	//�����н�ڵ㣬ÿ�����ɾ͸�s��r���ǵ�ǰ�������β��
	LinkList s, r;
	int i;

	srand(time(0));

	r = (LinkList)malloc(sizeof(Node));
	r = *L;

	for (i = 0; i < n; i++)
	{
		s = (LinkList)malloc(sizeof(Node));
		s->data = rand();
		r->next = s;
		r = s;//βsͬ�壬��s�Ѿ���β��r��
	}
}