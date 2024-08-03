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

#define NAME_MAX_LENGTH (15)
#define NAME_MAX_SIZE (NAME_MAX_LENGTH + 1)
#define CSIZE (4)

typedef struct _student Student;
typedef struct _name Name;

struct _name
{
    const char first[NAME_MAX_SIZE];
    const char last[NAME_MAX_SIZE];
};

struct _student
{
    Name name;
    double grade[3];
    double aver;
};

int main(int argc, char const *argv[])
{
    Student students[CSIZE] = {
        {{"Brain", "Kernighan"}},
        {{"Dennis", "Ritchie"}},
        {{"Andrew", "Koenig"}},
        {{"Stephen", "Prata"}}};

    return 0;
}
