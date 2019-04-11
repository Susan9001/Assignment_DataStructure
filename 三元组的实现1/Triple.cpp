#include <stdio.h>
#include <stdlib.h>
#include "Triple.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

Status InitTriple(Triple &T, ElemType v1, ElemType v2, ElemType v3 )
{
	//先分配空间，变成指针数组(?)
	T = (ElemType*) malloc (3 * sizeof(ElemType));

	if(!T)
		exit(OVERFLOW);

	T[0] = v1;
	T[1] = v2;
	T[2] = v3;
	//printf("成功！\n");
	return OK;
}

Status DestroyTriple(Triple &T)
{
	free(T);
	T = NULL;
	return OK;
}

Status Get(Triple T, int i, ElemType *e)
{
	if(i < 1 || i > 3)
		return ERROR;
	*e = T[i - 1];
	return OK;
}

Status Put(Triple &T, int i, ElemType e)
{
	if (i < 1 || i > 3)
		return ERROR;
	T[i - 1] = e;
	return OK;
}

Status IsAscending(Triple T)
{
	return ((T[0] <= T[1]) && (T[1] <= T[2]));
}

Status IsDescending(Triple T)
{
	return ((T[0] >= T[1]) && (T[1] >= T[2]));
}

Status Max(Triple T, ElemType *e)
{
	ElemType temp;
	temp = (T[0] >= T[1]) ? T[0] : T[1];
	*e = (temp >= T[2]) ? temp : T[2];
	return OK;
}

Status Min(Triple T, ElemType *e)
{
	ElemType temp;
	temp = (T[0] <= T[1]) ? T[0] : T[1];
	*e = (temp <= T[2]) ? temp : T[2];
	return OK;
}