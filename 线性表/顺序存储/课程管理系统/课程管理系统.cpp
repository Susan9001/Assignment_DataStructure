#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100 //�����ԷŶ��ٸ�Ԫ��
#define LIST_INCREMENT 10
#define CLASS_NUM 3
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

/*�γ̽ṹ��*/
typedef struct {
	int classId; //�γ̱��
	char name[50];
	double scores;
}Course;

/*ѧ���ṹ��*/
typedef struct {
	int stuId;
	char name; 
	Course course[CLASS_NUM]; //ÿ��ѧ����ҪѧCLASS_NUM�ſγ�
}Student, ElemType;

/*�༶�ṹ��(ѧ����Ϣ˳���)*/
typedef struct {
	ElemType *elem;
	int length; //�������ж��ٸ�ѧ��
	int listsize; //�����ԷŶ��ٸ�ѧ��
} SqList; 

Status InitList_Sq(SqList &L);
Status StartList_Sq(SqList &L); //��������ѧ������Ϣ
Status StartStu(Student* curStu); //����ָ��ѧ������Ϣ
Status ReadList_Sq(SqList L);    //�鿴����ѧ������Ϣ
Status ReadStu(Student* curStu); //�鿴ָ��ѧ������Ϣ
Status ChangeList_Sq(SqList &L, int stuId, int classId, double new_scores);
Status DeleteList_Sq(SqList &L, int stuId);
Status InsList_Sq(SqList &L, int studId);

int main()
{
	SqList L;
	int stuId, classId, choice = 0;
	double new_scores;

	InitList_Sq(L);
	StartList_Sq(L);

	while (choice != 6)
	{
		printf("\n1.�鿴���гɼ�\t2.�鿴ĳ�˳ɼ�\t3.����ĳ�˳ɼ�\t \n");
		printf("4.ĳ����ѧ(ɾ����Ϣ)\t5.���\t6.�˳�\n");
		printf("\n���������ѡ��");
		while (scanf("%d", &choice) != 1 || choice > 6 || choice < 0)
		{
			printf("�������Ү\n");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			ReadList_Sq(L);
			break;
		case 2:
			printf("����Ҫ�鿴�ڼ�λ�ĳɼ��أ�");
			scanf("%d", &stuId);
			if (stuId < 0 || stuId > L.length)
			{
				printf("û����ô����Ӵ~~\n");
				break;
			}
			else ReadStu(&L.elem[stuId - 1]);
			break;
		case 3:
			printf("����Ҫ�ĵڼ�λͬѧ����һ�Ƴɼ�(ѧ��-��Ŀ��-�³ɼ�)��");
			scanf("%d-%d-%lf", &stuId, &classId, &new_scores);
			if (stuId < 0 || stuId > L.length || classId < 0 || classId > CLASS_NUM)
			{
				printf("Ӵ�����ǲ�С������˰�S~~\n");
				break;
			}
			ChangeList_Sq(L, stuId, classId, new_scores);
			ReadStu(&L.elem[stuId - 1]);
			break;
		case 4:
			printf("���ʵڼ�λͬѧҪ��ѧ��(���)��");
			scanf("%d", &stuId);
			DeleteList_Sq(L, stuId);
			break;
		case 5:
			printf("������ͬѧҪ�嵽��λͬѧǰ����(���)��");
			scanf("%d", &stuId);
			InsList_Sq(L, stuId);
			break;
		default:
			break;
		}
	}

	return 0;
}

Status InitList_Sq(SqList &L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) return OVERFLOW;

	L.length = 0;
	L.listsize = LIST_INIT_SIZE;

	return OK;
}

Status StartList_Sq(SqList &L)
{
	int i = 0, k = 0;
	char choice;
	Student* currStu;

	printf("������(����N��n���ʾ�˳�)��\n");
	for (i = 0; i < LIST_INIT_SIZE && k != 1; i++)
	{
		currStu = &L.elem[i];
		currStu->stuId = i + 1;
		currStu->name = 'A' + i;
		printf("��%d��ͬѧ��С%c( )\b\b", currStu->stuId, currStu->name);
		if(i != 0) while (getchar() != '\n');
		choice = getchar();
		if(choice != 'N' && choice != 'n') StartStu(currStu);
		else break;
	}
	L.length = i;

	return OK;
}

Status StartStu(Student* currStu)
{
	int k= 0; //�˳����ź�
	double currScores;
	Course course0[CLASS_NUM] = { { 1, "���ݽṹ" },{ 2, "�����߼�" },{ 3, "Java" } };

	for (int j = 0; j < CLASS_NUM && k != 1; j++)
	{
		currStu->course[j] = course0[j]; //��֪����������в���```
		printf("%d��%s�ĳɼ���", currStu->course[j].classId, currStu->course[j].name);
		scanf("%lf", &currScores);
		currStu->course[j].scores = currScores;
		if (currScores < 0) //�˳�
			k = 1;
	}
	putchar('\n');
	return OK;
}

Status ReadList_Sq(SqList L)
{
	int i = 0, k = 0;
	double currScores;
	Student* currStu;

	for (i = 0; i < L.length && k != 1; i++)
	{
		currStu = &L.elem[i];
		if (L.elem[i].course[0].scores < 0) return OK; 
		else ReadStu(currStu);
	}
	
	return OK;
}

Status ReadStu(Student* currStu)
{
	printf("��%dλͬѧ:С%c\n", currStu->stuId, currStu->name);
	for (int j = 0; j < CLASS_NUM; j++)
	{
		if (currStu->course[j].scores < 0) return OK;
		printf("%d��%s��%.2lf��\n", currStu->course[j].classId,
			currStu->course[j].name, currStu->course[j].scores);
	}
	putchar('\n');
	return OK;
}

Status ChangeList_Sq(SqList &L, int stuId, int classId, double new_scores)
{
	Student* currStu = &L.elem[stuId - 1];
	Course* currCourse = &currStu->course[classId - 1];
	currCourse->scores = new_scores;

	return OK;
}

Status DeleteList_Sq(SqList &L, int stuId)
{
	int i = 0;

	for (i = stuId; i <= L.length-1; i++)
	{
		L.elem[i-1] = L.elem[i];
		L.elem[i-1].stuId--;
	}
	L.length--;

	return OK;
}

Status InsList_Sq(SqList &L, int studId)
{
	if (L.length <= L.listsize)
	{
		ElemType* newbase;
		newbase = (ElemType*)realloc(L.elem, (L.listsize + LIST_INCREMENT) * sizeof(ElemType));
		if (!newbase) return ERROR;
		L.elem = newbase;
		L.listsize += LIST_INCREMENT;
	}

	Student* targetStu = &L.elem[studId - 1];
	Student* currStu;
	for (currStu = &L.elem[L.length-1]; currStu >= targetStu; currStu--)
	{
		currStu->stuId++;
		*(currStu + 1) = *currStu;
	}
	L.length++;

	printf("���ڵ�%d��ͬѧ��С%cǰ��\n", targetStu->stuId, targetStu->name);
	targetStu = &L.elem[studId - 1];
	targetStu->stuId = studId;
	targetStu->name = 'A' + L.length-1;
	StartStu(targetStu);

	return OK;
}
