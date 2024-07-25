/**
 * 2.编写一个函数，提示用户输入日、月和年。
 * 月份可以是月份号、月份名或月份名缩写。
 * 然后该程序应返回一年中到用户指定日子（包括这一天）的总天数。
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MONTH_NAME_SIZE (10)
#define MONTH_NAME_LENGTH (MONTH_NAME_SIZE - 1)
#define MONTH_NAME_ABBR_SIZE (5)

typedef struct month
{
    const char *name;
    const char *abbr;
    unsigned int number;
    unsigned int days;
} MONTH;

typedef struct date
{
    int year;
    MONTH month;
    unsigned int day;
} DATE;

char *s_gets(char *str, int maxCount);
MONTH *monthArrCpy(MONTH *monthTarget, const MONTH *monthSource, const int iCount);
int isLeapYear(int iYear);
void transStrToLowerCase(char *str);
int parseStrMonth2IntNum(const char *strMonth, const MONTH *monthArr);
unsigned int getDaysFromTheBeginningOfAYearTo(DATE *date, const MONTH *monthArr);

int start();

const MONTH monthArr[12] = {
    {"January", "JAN", 1, 31},
    {"February", "FEB", 2, 28},
    {"March", "MAR", 3, 31},
    {"April", "APR", 4, 30},
    {"May", "MAY", 5, 31},
    {"June", "JUN", 6, 30},
    {"July", "JUL", 7, 31},
    {"August", "AUG", 8, 31},
    {"September", "SEP", 9, 30},
    {"October", "OCT", 10, 31},
    {"November", "NOV", 11, 30},
    {"December", "DEC", 12, 31}};

int main()
{
    if (start() == 0)
        return EXIT_FAILURE;

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

MONTH *monthArrCpy(MONTH *monthTarget, const MONTH *monthSource, const int iCount)
{
    if (monthTarget == NULL || monthSource == NULL)
    {
        fputs("ERROR: Found a null pointer at monthArrCpy", stderr);
        return NULL;
    }

    if (iCount < 0)
    {
        fputs("ERROR: Count of the MONTH array less than 0.\n", stderr);
        return NULL;
    }

    for (int i = 0; i < iCount; i++)
        monthTarget[i] = monthSource[i];

    return monthTarget;
}
int isLeapYear(int iYear)
{
    if (iYear < 0)
    {
        fputs("ERROR: Only support AD.\n", stderr);
        return 0;
    }

    if (iYear % 100)
    {
        if (iYear % 400)
            return 1;
    }
    else if (iYear % 4)
    {
        return 1;
    }

    return 0;
}

void transStrToLowerCase(char *str)
{
    if (str == NULL)
    {
        fputs("ERROR: Found a null pointer at transStrToLowerCase", stderr);
        return;
    }

    int iStrLength = strlen(str);

    for (int i = 0; i < iStrLength; i++)
        str[i] = tolower(str[i]);
}

int parseStrMonth2IntNum(const char *strMonth, const MONTH *monthArr)
{
    if (strMonth == NULL)
    {
        fputs("ERROR: Found a null pointer at parseStrMonth2IntNum", stderr);
        return 0;
    }

    char strMonthBuf[MONTH_NAME_SIZE];
    int iParsed = 0;

    strcpy(strMonthBuf, strMonth);

    transStrToLowerCase(strMonthBuf);

    /* 如果检测到第一个字符为数字字符且字符串长度小于等于 2U 则表示，输入为数字字符且通过长度检测，然后转换为整型后检测是否小于等于 12，通过后返回检测值；
    第一个字符检测到字母且字符串长度小于等于 3U 则表示，输入的字符串可能为月份名称的缩写，然后将字符串与月份表中的各个月份名称缩写匹配，返回匹配到的对应的值；
    第一个字符检测到字母且字符串长度大于 3U 则表示，输入的字符串可能为月份名称的全称，然后将字符串与月份表中的各个月份名称全称匹配，返回匹配到的对应的值；
    若不属于以上的各个情况或检测中遇到错误则返回 0 */
    if (isdigit(*strMonthBuf) && (strlen(strMonthBuf) <= 2U))
    {
        iParsed = atoi(strMonthBuf);
        if (iParsed <= 12)
            return (iParsed - 1); // 用作数组下标需 - 1
        else
            return 0;
    }
    else if (isalpha(*strMonthBuf))
    {
        unsigned int uiNum = 0;
        if (strlen(strMonthBuf) <= 3U)
        {
            for (uiNum = 0; uiNum < 12; uiNum++)
            {
                char strMonthAbbrBuf[MONTH_NAME_ABBR_SIZE];
                strcpy(strMonthAbbrBuf, monthArr[uiNum].abbr);
                transStrToLowerCase(strMonthAbbrBuf);
                if (strcmp(strMonthAbbrBuf, strMonthBuf) == 0)
                    return uiNum;
            }
            // abbr 匹配不成功的情况，return 0
            return 0;
        }
        else
        {
            for (uiNum = 0; uiNum < 12; uiNum++)
            {
                char strMonthNameBuf[MONTH_NAME_SIZE];
                strcpy(strMonthNameBuf, monthArr[uiNum].name);
                transStrToLowerCase(strMonthNameBuf);
                if (strcmp(strMonthNameBuf, strMonthBuf) == 0)
                    return uiNum;
            }
            // abbr 匹配不成功的情况，return 0
            return 0;
        }
    }
    else
        return 0;
}

unsigned int getDaysFromTheBeginningOfAYearTo(DATE *date, const MONTH *monthArr)
{
    if (date == NULL || monthArr == NULL)
    {
        fputs("ERROR: Found a null pointer at getDaysFromTheBeginningOfAYearTo", stderr);
        return 0;
    }

    unsigned int uiTotalDays = 0;

    if (date->month.number == 1) // isOnlyJanuary = TRUE
    {
        uiTotalDays = date->day;
    }
    else
    {
        for (unsigned int ui = 0; ui < (date->month.number - 1); ui++)
            uiTotalDays += monthArr[ui].days;
        uiTotalDays += date->day;
    }

    return uiTotalDays;
}

int start()
{
    DATE dateSelected;
    char strMonth[MONTH_NAME_SIZE];
    char strMonthLowered[MONTH_NAME_SIZE];
    int iMonthParsed = 0;
    unsigned int uiDays = 0;

    fputs("Please enter a date(Y/M/D),\n", stdout);

    fputs("Year: ", stdout);
    if (scanf("%d", &dateSelected.year) != 1)
    {
        fputs("ERROR: An error occurred while entering the number of a year.\n", stderr);
        return 0;
    }
    while (getchar() != '\n')
        continue;

    MONTH monthArrDummy[12];
    monthArrCpy(monthArrDummy, monthArr, 12); // Init monthArrDummy

    if (isLeapYear(dateSelected.year))
        monthArrDummy[1].days = 29;

    fputs("Month: ", stdout);
    s_gets(strMonth, MONTH_NAME_SIZE);

    if ((iMonthParsed = parseStrMonth2IntNum(strMonth, monthArrDummy)) == 0)
    {
        fputs("ERROR: An error occurred while parsing the month string.\n", stderr);
        return 0;
    }

    dateSelected.month = monthArr[iMonthParsed];

    fputs("Day: ", stdout);
    if (scanf("%u", &dateSelected.day) != 1)
    {
        fputs("ERROR: An error occurred while entering the number of a year.\n", stderr);
        return 0;
    }
    while (getchar() != '\n')
        continue;

    if (dateSelected.day > dateSelected.month.days)
    {
        fprintf(stderr, "ERROR: Days entered beyond %s.\n", dateSelected.month.name);
        return 0;
    }
    fputs("Done.\n", stdout);
    uiDays = getDaysFromTheBeginningOfAYearTo(&dateSelected, monthArrDummy);

    fprintf(stdout, "We have %u days from the early %d to %s %u.\n", uiDays, dateSelected.year, dateSelected.month.name, dateSelected.day);

    return 1;
