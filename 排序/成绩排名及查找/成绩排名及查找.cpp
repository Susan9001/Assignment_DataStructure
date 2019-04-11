#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_NAME 30 //名字最大长度
#define MAX_STU 30 //最大学生数目
#define MAXINT INT_MAX
#define EQ(a, b) ((a)==(b)) //a==b
#define LT(a, b) ((a)< (b)) //a < b
#define LQ(a, b) ((a)<=(b)) //a <= b

typedef int Status;
typedef struct {
	char name[MAX_NAME]; //学生姓名
	double score; //分数
	int ranking; //排名
}Student;
typedef struct {
	Student stu[MAX_STU]; //学生数组
	int num; //学生数
}Class; //班级

Status Create(Class &classA);
void QuickSort(Class &classA); //排序后给名次
void Partition(Class &classA, int low, int high); //排序
Status ReadClass(Class classA);
void ReadStu(Student student);

int main()
{
	Class classA;
	int choice, currrank;
	
	printf("1、录入学生信息  2、给成绩排名  3、查看全部人信息  4、按排名查看某人信息\n");
	while (true)
	{
		printf("\n请输入选项：");
		while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4)
		{
			printf("请正确输入选项哟：");
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
			printf("请输入要查询的排名：");
			if (scanf("%d", &currrank) != 1 || currrank < 1 
				|| currrank > classA.num || currrank != classA.stu[currrank].ranking)
			{
				printf("没有该排名的学生哟~");
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
	char temp[MAX_NAME + 10]; //+10是double型数字和-等分隔符

	printf("1、随机数据测试  2、手动输入数据\n请输入选择：");
	while (scanf("%d", &choice) != 1 || choice < 1 || choice > 2)
	{
		printf("请正确输入哟：");
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
			classA.stu[i].score = 85 + rand() % 15; //85-99分
			classA.stu[i].ranking = 0; //初始化没有排名
		}
		break;
	case 2:
		printf("请输入信息(最后的下一行确认后\"#\"结束, 名字-分数)：\n");
		for (i = 1; i <= MAX_STU; i++)
		{
			gets_s(temp, MAX_NAME + 10);
			if (temp[0] == '#') break; //最后结束
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
	int i, ranking; //ranking表示当前排名

	Partition(classA, 1, classA.num);

	classA.stu[1].ranking = 1;
	for (i = 2, ranking = 1; i <= classA.num; i++)
	{
		if (classA.stu[i].score > classA.stu[i - 1].score) //这是不同的名次
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
		Partition(classA, old_low, low - 1); //现在的low成为pivot了
	if (low + 1 < old_high)
		Partition(classA, low + 1, old_high);
}

Status ReadClass(Class classA)
{
	int i;

	printf("学生共%d人\n", classA.num);
	printf("%-29s%-10s%-4s\n", "姓名", "分数", "排名");
	for (i = 1; i <= classA.num; i++)
		ReadStu(classA.stu[i]);
	return OK;
}

void ReadStu(Student student)
{
	printf("%-29s%-10.1lf", student.name, student.score);
	if (!student.ranking) printf("%-4s\n", "未排名~");
	else printf("%-4d\n", student.ranking);
}