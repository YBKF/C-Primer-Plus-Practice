/**
 * 1.重新编写复习题5，
 * 用月份名的拼写代替月份号（别忘了使用strcmp()）。
 * 在一个简单的程序中测试该函数。
 *
 * 复习题5：
 * 编写一个函数，用户提供月份号，
 * 该函数就返回一年中到该月为止（包括该月）的总天数。
 * 假设在所有函数的外部声明了第3题的结构模版和一个该类型结构的数组。
 *
 * 复习题3：
 * 设计一个结构模板存储一个月份名，该月份名的3个字母缩写、该月的天数
 * 以及月份号。
 */
#include <stdio.h>

unsigned int howManyDaysFromBeginningOfAYearTo(char *strMonthWord);

typedef struct month
{
    char name[4];
    unsigned int days;
    unsigned int monthNum;
} MONTH;

MONTH monthSet[12] = {
    {"JAN", 31, 1},
    {"FEB", 28, 2},
    {"MAR", 31, 3},
    {"APR", 30, 4},
    {"MAY", 31, 5},
    {"JUN", 30, 6},
    {"JUL", 31, 7},
    {"AUG", 31, 8},
    {"SEP", 30, 9},
    {"OCT", 31, 10},
    {"NOV", 30, 11},
    {"DEC", 31, 12}};

// TODO 将输入转换为与月份对应的数字（数组下标），使用 for 循环
int main(int argc, char const *argv[])
{
    

    return 0;
}

unsigned int howManyDaysFromBeginningOfAYearTo(char *strMonthWord)
{
}