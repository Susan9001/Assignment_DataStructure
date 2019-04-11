#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_NAME 30 //������󳤶�
#define MAX_STU 30 //���ѧ����Ŀ
#define MAXINT INT_MAX
#define EQ(a, b) ((a)==(b)) //a==b
#define LT(a, b) ((a)< (b)) //a < b
#define LQ(a, b) ((a)<=(b)) //a <= b

typedef int Status;
typedef struct {
	char name[MAX_NAME]; //ѧ������
	double score; //����
	int ranking; //����
}Student;
typedef struct {
	Student stu[MAX_STU]; //ѧ������
	int num; //ѧ����
}Class; //�༶

Status Create(Class &classA);
void QuickSort(Class &classA); //����������
void Partition(Class &classA, int low, int high); //����
Status ReadClass(Class classA);
void ReadStu(Student student);

int main()
{
	Class classA;
	int choice, currrank;
	
	printf("1��¼��ѧ����Ϣ  2�����ɼ�����  3���鿴ȫ������Ϣ  4���������鿴ĳ����Ϣ\n");
	while (true)
	{
		printf("\n������ѡ�");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
		{
			printf("����ȷ����ѡ��Ӵ��");
			while (getchar() != '\n');
		}
		while (getchar() != '\n');

		switch (choice)
		{
		case 1:
			Create(classA);
			ReadClass(classA);
			break;
		case 2:
			QuickSort(classA);
			ReadClass(classA);
			break;
		case 3:
			ReadClass(classA);
			break;
		case 4:
			printf("������Ҫ��ѯ��������");
			if (scanf("%d", &currrank) != 1 || currrank < 1 
				|| currrank > classA.num || currrank != classA.stu[currrank].ranking)
			{
				printf("û�и�������ѧ��Ӵ~");
				while (getchar() != '\n');
				break;
			}
			while (getchar() != '\n');		
			do 
			{
				ReadStu(classA.stu[currrank]);
				currrank++;
			} while (classA.stu[currrank].ranking == classA.stu[currrank - 1].ranking);
		}//switch
	}//while true

	return 0;
}

Status Create(Class &classA)
{
	char currClass[][MAX_NAME] = {
		{"Winter is Coming"}, {"Tyrion Lannister"}, {"Tywin Lannister"}, {"Putin the Emperor"},
		{"Dr. Who"}, {"Benedict Cumberbatch"}, {"Underwood the politician"}, {"Don Vito Corleone"},
		{"Jamie Lannister"}, {"Cersei Lannister"}, {"Frog the Elder"}
	};
	int i, j, choice;
	char temp[MAX_NAME + 10]; //+10��double�����ֺ�-�ȷָ���

	printf("1��������ݲ���  2���ֶ���������\n������ѡ��");
	while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2)
	{
		printf("����ȷ����Ӵ��");
		while (getchar() != '\n');
	}
	while (getchar() != '\n');

	switch (choice)
	{
	case 1:
		srand(time(NULL));
		classA.num = 11;
		for (i = 1; i <= classA.num; i++)
		{
			strncpy(classA.stu[i].name, currClass[i - 1], MAX_NAME);
			classA.stu[i].score = 85 + rand() % 15; //85-99��
			classA.stu[i].ranking = 0; //��ʼ��û������
		}
		break;
	case 2:
		printf("��������Ϣ(������һ��ȷ�Ϻ�\"#\"����, ����-����)��\n");
		for (i = 1; i <= MAX_STU; i++)
		{
			gets_s(temp, MAX_NAME + 10);
			if (temp[0] == '#') break; //������
			strncpy(classA.stu[i].name, strtok(temp, "-"), MAX_NAME);
			classA.stu[i].score = atof(strtok(NULL, "-"));
			classA.stu[i].ranking = 0;
		}
		classA.num = i - 1;
		break;
	}

	return OK;
}

void QuickSort(Class &classA)
{
	int i, ranking; //ranking��ʾ��ǰ����

	Partition(classA, 1, classA.num);

	classA.stu[1].ranking = 1;
	for (i = 2, ranking = 1; i <= classA.num; i++)
	{
		if (classA.stu[i].score > classA.stu[i - 1].score) //���ǲ�ͬ������
			ranking = i;
		classA.stu[i].ranking = ranking;
	}
}

void Partition(Class &classA, int low, int high)
{
	double pivotkey = classA.stu[low].score;
	int old_low = low, old_high = high;
	classA.stu[0] = classA.stu[low];

	while (low < high)
	{
		while (low < high && LQ(pivotkey, classA.stu[high].score)) high--;
		classA.stu[low] = classA.stu[high];
		while (low < high && LQ(classA.stu[low].score, pivotkey)) low++;
		classA.stu[high] = classA.stu[low];
	}
	classA.stu[low] = classA.stu[0];

	if (old_low < low - 1)
		Partition(classA, old_low, low - 1); //���ڵ�low��Ϊpivot��
	if (low + 1 < old_high)
		Partition(classA, low + 1, old_high);
}

Status ReadClass(Class classA)
{
	int i;

	printf("ѧ����%d��\n", classA.num);
	printf("%-29s%-10s%-4s\n", "����", "����", "����");
	for (i = 1; i <= classA.num; i++)
		ReadStu(classA.stu[i]);
	return OK;
}

void ReadStu(Student student)
{
	printf("%-29s%-10.1lf", student.name, student.score);
	if (!student.ranking) printf("%-4s\n", "δ����~");
	else printf("%-4d\n", student.ranking);
}