GetMidNode(LinkList L, ElemType *e)
{
	LinkList mid, search;
	
	while (search->next != NULL)
	{
		if (search->next->next == NULL)//ÆæÊı
		{
			*e = mid->next->data;
			return OK;
		}
		mid = mid->next;
		search = search->next->next;
	}
	*e = mid->next->data;

}