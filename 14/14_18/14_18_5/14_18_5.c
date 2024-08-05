/**
 * 5.编写一个程序满足下面的要求。
 * a.外部定义一个有两个成员的结构模板name：
 * 一个字符串储存名，一个字符串储存姓。
 *
 * b.外部定义一个有3个成员的结构模板student：
 * 一个name类型的结构，一个grade数组储存3个浮点型分数，一个变量储存3个分数平均数。
 *
 * c.在main()函数中声明一个内含CSIZE（CSIZE = 4）个student类型结构的数组，
 * 并初始化这些结构的名字部分。用函数执行d、e、f和g中描述的任务。
 *
 * d.以交互的方式获取每个学生的成绩，提示用户输入学生的姓名和分数。
 * 把分数储存到grade数组相应的结构中。
 * 可以在main()函数或其他函数中用循环来完成。
 *
 * e.计算每个结构的平均分，并把计算后的值赋给合适的成员。
 *
 * f.打印每个结构的信息。
 *
 * g.打印班级的平均分，即所有结构的数值成员的平均值。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_FIRST_MAX_LENGTH (15)
#define NAME_FIRST_MAX_SIZE (NAME_FIRST_MAX_LENGTH + 1)
#define NAME_LAST_MAX_LENGTH (15)
#define NAME_LAST_MAX_SIZE (NAME_LAST_MAX_LENGTH + 1)
#define NAME_FULL_MAX_SIZE (NAME_FIRST_MAX_LENGTH + NAME_LAST_MAX_LENGTH + 3)
#define GRADE_COUNT (3)
#define CSIZE (4)

typedef struct _student Student;
typedef struct _name Name;

Student *getStudentByName(const Name *name, Student *studentList, int maxCount);
double calculateStudentAverageGrade(Student *student, const int gradeCount);

struct _name
{
    char first[NAME_FIRST_MAX_SIZE];
    char last[NAME_LAST_MAX_SIZE];
};

struct _student
{
    Name name;
    double grade[GRADE_COUNT];
    double aver;
};

int main(int argc, char const *argv[])
{
    Student students[CSIZE] = {
        {{"Brain", "Kernighan"}},
        {{"Dennis", "Ritchie"}},
        {{"Andrew", "Koenig"}},
        {{"Stephen", "Prata"}}};

    Name nameBuf;
    char strFullName[NAME_FULL_MAX_SIZE];

    Student *stuSel;
    double lfClassAver = .0;
    int iScanfRetVal;

    fprintf(stdout, "Enter the name of the student you want to search,\n");
    fprintf(stdout, "Enter [Ctrl] + [z] at the start of a line to stop.\n");
    // TODO 能连续接受两个字符串，且一旦检测到EOF便结束输入
    while (fgets(strFullName, NAME_FULL_MAX_SIZE, stdin) != NULL)
    {
        while (getchar() != '\n')
            continue;

        sscanf(strFullName, )
    }

    while ((iScanfRetVal = scanf("%*s", NAME_FIRST_MAX_LENGTH, nameBuf.first) == 1) && scanf("%*s", NAME_LAST_MAX_LENGTH, nameBuf.last) == 1)
    {
        while (getchar() != '\n')
            continue;

        if (NULL == (stuSel = getStudentByName(&nameBuf, students, CSIZE)))
        {
            fprintf(stderr, "\
ERROR: An error occurred while getting a student named \"%s %s\",\
or there is no infomation about \"%s %s\".\n",
                    nameBuf.first, nameBuf.last, nameBuf.first, nameBuf.last);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < GRADE_COUNT; i++)
        {
            fprintf(stdout, "Enter the %d grades about the student:\n", GRADE_COUNT);
            double stuGrade;

            if (scanf("%lf", &stuGrade) != 1)
                stuGrade = .0;
            while (getchar() != '\n')
                continue;

            stuSel->grade[i] = stuGrade;
        }
        calculateStudentAverageGrade(stuSel, GRADE_COUNT);

        fprintf(stdout, "Enter the name of the student you want to search,\n");
        fprintf(stdout, "Enter [Ctrl] + [z] at the start of a line to stop.\n");
    }

    if (feof(stdin))
        return 0;
    else if (ferror(stdin))
    {
        fprintf(stderr, "ERROR: An error occurred while reading the input stream.\n");
        return EXIT_FAILURE;
    }

    if (iScanfRetVal == EOF)
        return 0;

    for (int i = 0; i < CSIZE; i++)
    {
        fprintf(stdout, "\
Name:   %s %s\n",
                stuSel->name.first, stuSel->name.last);
        fprintf(stdout, "\
Grade:  ");
        for (int i = 0; i < GRADE_COUNT; i++)
            fprintf(stdout, "%2.2lf ", stuSel->grade[i]);
        fprintf(stdout, "\
\n");
        fprintf(stdout, "\
Aver:   %2.2lf\n",
                stuSel->aver);
        fprintf(stdout, "\n\
\n");
    }

    for (int i = 0; i < CSIZE; i++)
        lfClassAver += students[i].aver;

    if (CSIZE >= 0)
        lfClassAver /= CSIZE;

    fprintf(stdout, "\
Class Average: %2.2lf",
            lfClassAver);

    return 0;
}

/**
 * - [in] name
 * - [in/out] studentList
 * - [in] maxCount
 */
Student *getStudentByName(const Name *name, Student *studentList, int maxCount)
{
    if (name == NULL || studentList == NULL)
    {
        fprintf(stderr, "ERROR: Found a null pointer at function getStudentByName.\n");
        return NULL;
    }

    if (maxCount <= 0)
        return NULL;

    for (int i = 0; i < maxCount; i++)
        if (strcmp(name->first, studentList[i].name.first) == 0 && strcmp(name->last, studentList[i].name.last) == 0)
            return &studentList[i];

    return NULL;
}

/**
 * - [in/out] student
 * - [in] gradeCount
 */
double calculateStudentAverageGrade(Student *student, const int gradeCount)
{
    if (student == NULL)
    {
        fprintf(stderr, "ERROR: Found a null pointer at function calculateStudentAverageGrade.\n");
        return .0;
    }

    if (gradeCount <= 0)
        return .0;

    double lfTotalGrade = 0;

    for (int i = 0; i < gradeCount; i++)
        lfTotalGrade += student->grade[i];

    student->aver = (lfTotalGrade / gradeCount);

    return student->aver;
}
