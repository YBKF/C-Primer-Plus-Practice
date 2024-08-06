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

char *s_gets(char *s, int n);
Student *getStudentByName(const Name *name, Student *studentList, int maxCount, unsigned int *puiStatus);
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

    fprintf(stdout, "[Name]\nEnter the name of the student you want to search,\n");
    fprintf(stdout, "Enter [Ctrl] + [z] at the start of a line to stop.\n");

    // 输入开始
    while (s_gets(strFullName, NAME_FULL_MAX_SIZE) != NULL)
    {
        // fprintf(stdout, "#%s#\n", strFullName);

        /* NAME_FIRST_MAX_LENGTH (15)
           NAME_LAST_MAX_LENGTH (15) */
        if (sscanf(strFullName, "%15s %15s", nameBuf.first, nameBuf.last) != 2)
        {
            fprintf(stderr, "ERROR: Unknown input: \"%s\", please retry.\n", strFullName);
            fprintf(stderr, "\n[Name]\nEnter [Ctrl] + [z] at the start of a line to stop.\n");
            continue;
        }

        unsigned int uiStatus = 1;
        if (NULL == (stuSel = getStudentByName(&nameBuf, students, CSIZE, &uiStatus)) && uiStatus == 2)
        {
            fprintf(stderr, "\
ERROR: An error occurred while getting a student named \"%s %s\",\
or there is no infomation about \"%s %s\".\n",
                    nameBuf.first, nameBuf.last, nameBuf.first, nameBuf.last);
            exit(EXIT_FAILURE);
        }
        else if (uiStatus == 1)
        {
            fprintf(stderr, "\
WARNING: There is no infomation about \"%s %s\".\n",
                    nameBuf.first, nameBuf.last);
            continue;
        }

        fprintf(stdout, "\n[Grade]\nEnter the %d grades about \"%s %s\":\n",
                GRADE_COUNT, stuSel->name.first, stuSel->name.last);
        for (int i = 0; i < GRADE_COUNT; i++)
        {
            double stuGrade;

            if (scanf("%lf", &stuGrade) != 1)
            {
                fprintf(stderr, "WARNING: Unknown input.\n");
                stuGrade = .0;
            }

            stuSel->grade[i] = stuGrade;
        }
        while (getchar() != '\n')
            continue;

        calculateStudentAverageGrade(stuSel, GRADE_COUNT);

        fprintf(stdout, "\n[Name]\nEnter the name of the student you want to search,\n");
        fprintf(stdout, "Enter [Ctrl] + [z] at the start of a line to stop.\n");
    }
    // 输入结束

    if (ferror(stdin))
    {
        fprintf(stderr, "ERROR: An error occurred while reading the input stream.\n");
        return EXIT_FAILURE;
    }
    // else if (feof(stdin))
    //     fprintf(stdout, "Got an EOF.\n");

    for (int i = 0; i < CSIZE; i++)
    {
        fprintf(stdout, "\
Name:   %s %s\n",
                students[i].name.first, students[i].name.last);
        fprintf(stdout, "\
Grade:  ");
        for (int j = 0; j < GRADE_COUNT; j++)
            fprintf(stdout, "%2.2lf ", students[i].grade[j]);
        fprintf(stdout, "\
\n");
        fprintf(stdout, "\
Aver:   %2.2lf\n",
                students[i].aver);
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
 * 从标准输入中读取字符，并将读取到的字符存入 s，
 * 直到读到新的一行或读取了 n-1 个字符又或是读取到文件结尾（EOF），
 * 功能类似于 gets() 但可以设置最大读取字符数。
 * 读取结束后，在字符串结尾添加一个空字符并返回 s 的地址，
 * 如果还未向 s 存入任何字符便读到文件结尾（EOF）则返回NULL且不向字符串结尾添加空字符。
 * 一旦在读取过程中出现错误则返回NULL。
 */
char *s_gets(char *s, int n)
{
    char *p = s;
    FILE *stream = stdin;

    if (s == NULL || n <= 0)
        return NULL;

    int c = 0;

    while (--n > 0 && (c = getchar()) != EOF)
        if (c == '\n')
            break;
        else
            *p++ = c;

    if (n == 0)
        while (getchar() != '\n')
            continue;

    if (c == EOF && (p == s || ferror(stream)))
        return NULL;

    *p = '\0';

    return s;
}

/**
 * - [in] name
 * - [in] studentList
 * - [in] maxCount
 */
Student *getStudentByName(const Name *name, Student *studentList, int maxCount, unsigned int *puiStatus)
{
    if (name == NULL || studentList == NULL)
    {
        fprintf(stderr, "ERROR: Found a null pointer at function getStudentByName.\n");
        if (puiStatus != NULL)
            *puiStatus = 2;
        return NULL;
    }

    if (maxCount <= 0)
    {
        if (puiStatus != NULL)
            *puiStatus = 2;
        return NULL;
    }

    for (int i = 0; i < maxCount; i++)
        if (strcmp(name->first, studentList[i].name.first) == 0 && strcmp(name->last, studentList[i].name.last) == 0)
        {
            if (puiStatus != NULL)
                *puiStatus = 0;
            return &studentList[i];
        }

    if (puiStatus != NULL)
        *puiStatus = 1;
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
