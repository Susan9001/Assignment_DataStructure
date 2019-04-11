#ifndef TRIPLE_H_INCLUDED
#define TRIPLE_H_INCLUDED

typedef int Status;
typedef int ElemType;
typedef ElemType *Triple;

Status InitTriple( Triple &T, ElemType v1, ElemType v2, ElemType v3 );
Status DestroyTriple(Triple &T);
Status Get(Triple T, int i, ElemType *e);
Status Put(Triple &T, int i, ElemType e);
Status IsAscending(Triple T);
Status IsDescending(Triple T);
Status Max(Triple T, ElemType *e);
Status Min(Triple T, ElemType *e);

#endif