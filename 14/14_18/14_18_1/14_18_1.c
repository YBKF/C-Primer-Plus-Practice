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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_MONTH_SIZE (10)
#define STR_MONTH_LENGTH (STR_MONTH_SIZE - 1)

char *s_gets(char *str, int maxCount);
unsigned int howManyDaysFromBeginningOfAYearTo(const char *strMonthWord);

typedef struct month
{
    char name[4];
    unsigned int days;
    unsigned int monthNum;
} MONTH;

// enum MonthNumber
// {
//     January = 1,
//     February,
//     March,
//     April,
//     May,
//     June,
//     July,
//     August,
//     September,
//     October,
//     November,
//     December
// };

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
int main()
{
    char strMonthName[STR_MONTH_SIZE];
    unsigned int uiDays;

    fprintf(stdout, "Please enter the name of a month:\n");
    s_gets(strMonthName, STR_MONTH_LENGTH);

    if ((uiDays = howManyDaysFromBeginningOfAYearTo(strMonthName)) == 0)
    {
        fprintf(stderr, "Please enter a correct name of a month.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "How many days are there from the beginning of a year to %s?\n", strMonthName);
    fprintf(stdout, "%u days.\n", uiDays);

    return 0;
}

char *s_gets(char *str, int maxCount)
{
    char *ret_val;
    char *find;

    ret_val = fgets(str, maxCount, stdin);
    if (ret_val != NULL)
    {
        find = strchr(str, '\n');
        if (find)
            *find = '\0';
        else
            while (getchar() != '\n')
                continue;
    }

    return ret_val;
}

/**
 * january
 * february
 * march
 * april
 * may
 * june
 * july
 * august
 * september
 * october
 * november
 * december
 */
unsigned int howManyDaysFromBeginningOfAYearTo(const char *strMonthWord)
{
    if (strMonthWord == NULL)
        return 0;

    int iMonNum = 0;
    unsigned int uiTotal = 0;
    int iMonthNameLength = strlen(strMonthWord);

    char strMonthLowered[STR_MONTH_SIZE];

    for (int i = 0; i < iMonthNameLength; i++)
        strMonthLowered[i] = tolower(strMonthWord[i]);

    if (strcmp(strMonthLowered, "january") == 0)
        iMonNum = 1;
    else if (strcmp(strMonthLowered, "february") == 0)
        iMonNum = 2;
    else if (strcmp(strMonthLowered, "march") == 0)
        iMonNum = 3;
    else if (strcmp(strMonthLowered, "april") == 0)
        iMonNum = 4;
    else if (strcmp(strMonthLowered, "may") == 0)
        iMonNum = 5;
    else if (strcmp(strMonthLowered, "june") == 0)
        iMonNum = 6;
    else if (strcmp(strMonthLowered, "july") == 0)
        iMonNum = 7;
    else if (strcmp(strMonthLowered, "august") == 0)
        iMonNum = 8;
    else if (strcmp(strMonthLowered, "september") == 0)
        iMonNum = 9;
    else if (strcmp(strMonthLowered, "october") == 0)
        iMonNum = 10;
    else if (strcmp(strMonthLowered, "november") == 0)
        iMonNum = 11;
    else if (strcmp(strMonthLowered, "december") == 0)
        iMonNum = 12;
    else
        return 0;

    for (int i = 0; i < iMonNum; i++)
        uiTotal += monthSet[i].days;

    return uiTotal;
}