#define STACK_INIT_SIZE 100
#define INCREMENT 10

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;
typedef struct sqStack
{
	ElemType *base;
	ElemType *top;
	int stackSize;
}sqStack;


Status initStack(sqStack &s)
{
	s.base = (ElemType*)malloc(sizeof(ElemType));
	if (!s.base) return ERROR;
	s.top = s.base;
	s.stackSize = STACK_INIT_SIZE;

	return OK;
}

Status Push(sqStack &s, ElemType e)
{
	if (s.top - s.base <= s.stackSize)
	{
		s.base = (ElemType*)realloc(sizeof(ElemType));
		if (!s.base) return OVERFLOW;
		
		/*×¢ÒâË³Ðò*/
		s.top = s.base + s.stackSize;
		s.stackSize += INCREMENT;
	}

	*(s.top) = e;
	s.top++;

	return OK;
}

Status Pop(sqStack &s, ElemType &e)
{
	if (s.top == s.base) return ERROR;
	e = *(s.top);
	s.top--;

	return OK;
}