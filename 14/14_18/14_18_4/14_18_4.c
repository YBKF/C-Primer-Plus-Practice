/**
 * 4.编写一个程序，创建一个有两个成员的结构模板：
 * a.第1个成员是社会保险号，第2个成员是一个有3个成员的结构，
 * 第1个成员代表名，第2个成员代表中间名，第3个成员表示姓。
 * 创建并初始化一个内含5个该类型结构的数组。该程序以下面的格式打印数据：
 *
 * Dribble, Flossie M.–– 302039823
 *
 * 如果有中间名，只打印它的第1个字母，后面加一个点（.）；
 * 如果没有中间名，则不用打印点。
 * 编写一个程序进行打印，把结构数组传递给这个函数。
 *
 * b.修改a部分，传递结构的值而不是结构的地址。
 */
#include <stdio.h>

#define NAME_MAX_LENGTH 15
#define NAME_MAX_SIZE (NAME_MAX_LENGTH + 1)
#define SSN_LENGTH 9
#define SSN_STR_SIZE (SSN_LENGTH + 1)

typedef struct _name
{
    const char first[NAME_MAX_SIZE];
    const char mid[NAME_MAX_SIZE];
    const char last[NAME_MAX_SIZE];
} NAME;

typedef struct _id
{
    char SSN[SSN_STR_SIZE];
    NAME name;
} ID;

int main()
{

    return 0;
}
