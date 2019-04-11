//单链表整表建立
//头法
void CreatListHead(LinkList *L, int n)
{
	LinkList p;//p是中介节点
	int i;

	srand(time(0));

	//声明一个指针指向节点
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

//尾法
void CreatListTail(LinkList *L, int n)
{
	//两个中介节点，每次生成就给s，r则是当前单链表的尾巴
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
		r = s;//尾s同体，即s已经是尾部r了
	}
}