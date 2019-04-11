#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100 //最多可以放多少个元素
#define LIST_INCREMENT 10
#define CLASS_NUM 3
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int Status;

/*课程结构体*/
typedef struct {
	int classId; //课程编号
	char name[50];
	double scores;
}Course;

/*学生结构体*/
typedef struct {
	int stuId;
	char name; 
	Course course[CLASS_NUM]; //每个学生都要学CLASS_NUM门课程
}Student, ElemType;

/*班级结构体(学生信息顺序表)*/
typedef struct {
	ElemType *elem;
	int length; //现在已有多少个学生
	int listsize; //最多可以放多少个学生
} SqList; 

Status InitList_Sq(SqList &L);
Status StartList_Sq(SqList &L); //输入所有学生的信息
Status StartStu(Student* curStu); //输入指定学生的信息
Status ReadList_Sq(SqList L);    //查看所有学生的信息
Status ReadStu(Student* curStu); //查看指定学生的信息
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
		printf("\n1.查看所有成绩\t2.查看某人成绩\t3.更新某人成绩\t \n");
		printf("4.某人退学(删除信息)\t5.插班\t6.退出\n");
		printf("\n请输入你的选择：");
		while (scanf("%d", &choice) != 1 || choice > 6 || choice < 0)
		{
			printf("输入错了耶\n");
			while (getchar() != '\n');
		}

		switch (choice)
		{
		case 1:
			ReadList_Sq(L);
			break;
		case 2:
			printf("请问要查看第几位的成绩呢：");
			scanf("%d", &stuId);
			if (stuId < 0 || stuId > L.length)
			{
				printf("没有那么多人哟~~\n");
				break;
			}
			else ReadStu(&L.elem[stuId - 1]);
			break;
		case 3:
			printf("请问要改第几位同学的哪一科成绩(学号-科目号-新成绩)：");
			scanf("%d-%d-%lf", &stuId, &classId, &new_scores);
			if (stuId < 0 || stuId > L.length || classId < 0 || classId > CLASS_NUM)
			{
				printf("哟，您是不小心输错了吧S~~\n");
				break;
			}
			ChangeList_Sq(L, stuId, classId, new_scores);
			ReadStu(&L.elem[stuId - 1]);
			break;
		case 4:
			printf("请问第几位同学要退学呢(序号)：");
			scanf("%d", &stuId);
			DeleteList_Sq(L, stuId);
			break;
		case 5:
			printf("请问新同学要插到哪位同学前面呢(序号)：");
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

	printf("请输入(输入N或n则表示退出)：\n");
	for (i = 0; i < LIST_INIT_SIZE && k != 1; i++)
	{
		currStu = &L.elem[i];
		currStu->stuId = i + 1;
		currStu->name = 'A' + i;
		printf("第%d名同学：小%c( )\b\b", currStu->stuId, currStu->name);
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
	int k= 0; //退出的信号
	double currScores;
	Course course0[CLASS_NUM] = { { 1, "数据结构" },{ 2, "数字逻辑" },{ 3, "Java" } };

	for (int j = 0; j < CLASS_NUM && k != 1; j++)
	{
		currStu->course[j] = course0[j]; //不知道局域变量行不行```
		printf("%d、%s的成绩：", currStu->course[j].classId, currStu->course[j].name);
		scanf("%lf", &currScores);
		currStu->course[j].scores = currScores;
		if (currScores < 0) //退出
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
	printf("第%d位同学:小%c\n", currStu->stuId, currStu->name);
	for (int j = 0; j < CLASS_NUM; j++)
	{
		if (currStu->course[j].scores < 0) return OK;
		printf("%d、%s：%.2lf分\n", currStu->course[j].classId,
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

	printf("放在第%d名同学：小%c前面\n", targetStu->stuId, targetStu->name);
	targetStu = &L.elem[studId - 1];
	targetStu->stuId = studId;
	targetStu->name = 'A' + L.length-1;
	StartStu(targetStu);

	return OK;
}
