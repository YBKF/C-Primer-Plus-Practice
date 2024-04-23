/**
 * 11.编写一个函数，读入10个字符串或者读到EOF时停止。
 * 该程序为用户提供一个有5个选项的菜单：
 * 打印源字符串列表、以ASCII中的顺序打印字符串、按长度递增顺序打印字符串、
 * 按字符串中第1个单词的长度打印字符串、退出。
 * 菜单可以循环显示，除非用户选择退出选项。
 * 当然，该程序要能真正完成菜单中各选项的功能。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_COUNT 10
#define STR_MAX_LENGTH 100

bool printMenu();
int getselection();
int onOpeartion(int selection, char *pchArr[], const int count);

char *s_gets(char *str, int maxCount);
int getsnlenOfFirstWord(const char *str, int maxCount);
void printAsterisk(int count);

void sortStrListByASCII(char *strArrTarget[], char *strArrSource[], const int count);
void sortStrListByIncreasingLength(char *strArrTarget[], char *strArrSource[], const int count);
void sortStrListByFirstWordLength(char *strArrTarget[], char *strArrSource[], const int count);

int get10Strings(char (*strArr)[STR_MAX_LENGTH]);
void cpyStringsAddr(char *pchArrTarget[], char (*strArrSource)[STR_MAX_LENGTH], const int count);
void printStrings(char *pchArr[], const int count);

void printStrListSource(char *pchArr[], const int count);
void printStrListByASCII(char *pchArr[], const int count);
void printStrListByIncreasingLength(char *pchArr[], const int count);
void printStrListByFirstWordLength(char *pchArr[], const int count);

int main(int argc, char const *argv[])
{
    int i_strCount = 0;
    char strArrInput[STR_COUNT][STR_MAX_LENGTH] = {};
    char *pchArrInput[STR_COUNT];

    int iRetValOperation = 1;

    fputs("Please input 10 strings:\n", stdout);
    i_strCount = get10Strings(strArrInput);
    cpyStringsAddr(pchArrInput, strArrInput, i_strCount);

    while (iRetValOperation)
    {
        printMenu();
        iRetValOperation = onOpeartion(getselection(), pchArrInput, i_strCount);
    }

    // printStrings(pchArr, i_strCount);
    // printStrListByASCII(pchArr, i_strCount);
    // putchar('\n');
    // printStrListByIncreasingLength(pchArr, i_strCount);
    // putchar('\n');
    // printStrListByFirstWordLength(pchArr, i_strCount);

    return 0;
}

// 打印菜单
bool printMenu()
{
    printAsterisk(120);
    fputs("Please select an operation(1~5), 5 to exit:\n\n", stdout);
    fputs("1.Print source string list.\t\t\t\t2.Print string list by the order of ASCII.\n", stdout);
    fputs("3.Print string list by the order of string length.\t4.Print string list by the order of length of the first word.\n", stdout);
    fputs("5.Exit.\n", stdout);
    printAsterisk(120);
    fputs("Input here: ", stdout);
    return true;
}

// 获取输入，并验证
int getselection()
{
    int selection = 0;
    int retVal;

    retVal = scanf("%d", &selection);
    while (getchar() != '\n')
        continue;

    if (retVal != 1 || selection < 1 || selection > 5)
        do
        {
            fputs("Please Re-Input: ", stdout);

            retVal = scanf("%d", &selection);
            while (getchar() != '\n')
                continue;

        } while (retVal != 1 || selection < 1 || selection > 5);

    return selection;
}

// 执行退出操作（即selection == 5）或操作数不合法后将返回false，否则返回true
int onOpeartion(int selection, char *pchArr[], const int count)
{
    if (selection == 5)
        return false;
    else if (selection == 1)
    {
        fputs("\n1.Print source string list:\n", stdout);
        printStrListSource(pchArr, count);
        putchar('\n');
    }
    else if (selection == 2)
    {
        fputs("\n2.Print string list by the order of ASCII:\n", stdout);
        printStrListByASCII(pchArr, count);
        putchar('\n');
    }
    else if (selection == 3)
    {
        fputs("\n3.Print string list by the order of string length:\n", stdout);
        printStrListByIncreasingLength(pchArr, count);
        putchar('\n');
    }
    else if (selection == 4)
    {
        fputs("\n4.Print string list by the order of length of the first word:\n", stdout);
        printStrListByFirstWordLength(pchArr, count);
        putchar('\n');
    }
    else
        return false;

    return true;
}

char *s_gets(char *s, int n)
{
    char *p = s;

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

    *p = '\0';

    if (c == EOF && p == s)
        return NULL;

    return s;
}

/* 读取一个字符串，获取字符串中第一个单词的长度，最大长度不超过maxCount的限制，当在字符串开头读到EOF时则返回-1(EOF) */
int getsnlenOfFirstWord(const char *str, int maxCount)
{
    if (str == NULL || maxCount <= 0)
        return 0;

    int count = 0;

    while (maxCount-- > 0 && str[count] != ' ' && str[count] != '\0')
        count++;

    if (str[count] == EOF && 0 == count)
        return EOF;

    return count;
}

/* 打印指定个数的星号(*)，并在最后换行 */
void printAsterisk(int count)
{
    if (count <= 0)
        return;

    while (count--)
        putchar('*');

    putchar('\n');
}

/* 比较源指针数组中各指针指向的字符串，
并将各指针按照指向的字符串的ASCII码数值从小到大的顺序进行排序（使用strcmp），
最后将排序后的指针列表存储到目标指针数组中 */
void sortStrListByASCII(char *strArrTarget[], char *strArrSource[], const int count)
{
    int iMin;     // 在字符串比较中的小值的下标，用作比较字符串
    int iTar;     // 目标数组的下标
    int iTop = 0; // 用于表示数组新一轮比较的开头位置
    int iSeek;    // 当前被比较的字符串的下标

    bool *isSorted;                                 // 分配用于检查数组中元素是否已被排序的布尔变量的空间
    isSorted = (bool *)calloc(count, sizeof(bool)); // 需要申请并归零
    if (NULL == isSorted)
    {
        puts("Memory allocation failed! At pointer \"isSorted\" in funcation \"sortStrListByASCII\".");
        exit(EXIT_FAILURE);
    }

    /* 选出源数组中strcmp比较值最小的元素，即iMin下标的元素，目的是将其值（字符串地址）赋给目标数组中iTar下标的元素（iTar指示目标数组首元素），
    使用bool数组isSorted各元素用于标记源数组中各对应下标的元素是否已被排序（isSorted中各元素的下标与源数组的各元素的下标一一对应），
    如isSorted[iMin] = true，即表示strArrSource[iMin]元素“已被排序”，则在算法中不再比较strArrSource[iMin]，最后iTar++。 */
    for (iTar = 0; iTar < count; iTar++)
    {
        for (iMin = iTop, iSeek = iTop + 1; iSeek < count; iSeek++)
            if (!isSorted[iSeek] && (strcmp(strArrSource[iMin], strArrSource[iSeek]) > 0))
                iMin = iSeek;

        isSorted[iMin] = true;

        /* 若iTop下标的元素正是刚刚被排序的元素，则将以下一个元素为开头，即iTop++，
         若下一个元素也是排序过的元素则继续iTop++，直到iTop指示的元素不为排序过的元素。
         下一次循环将以iTop下标的元素为开头 */
        while (isSorted[iTop])
            iTop++;

        strArrTarget[iTar] = strArrSource[iMin];
    }

    free(isSorted);
}

/* 比较源指针数组中各指针指向的字符串，
并将各指针按照指向的字符串的长度从短到长的顺序进行排序（使用strnlen），
最后将排序后的指针列表存储到目标指针数组中 */
void sortStrListByIncreasingLength(char *strArrTarget[], char *strArrSource[], const int count)
{
    int iMin;     // 在字符串比较中的小值的下标，用作比较字符串
    int iTar;     // 目标数组的下标
    int iTop = 0; // 用于表示数组新一轮比较的开头位置
    int iSeek;    // 当前被比较的字符串的下标

    int iMinLen, iSeekLen;

    bool *isSorted;                                 // 分配用于检查数组中元素是否已被排序的布尔变量的空间
    isSorted = (bool *)calloc(count, sizeof(bool)); // 需要申请并归零
    if (NULL == isSorted)
    {
        puts("Memory allocation failed! At pointer \"isSorted\" in funcation \"sortStrListByIncreasingLength\".");
        exit(EXIT_FAILURE);
    }

    for (iTar = 0; iTar < count; iTar++)
    {
        for (iMin = iTop, iSeek = iTop + 1; iSeek < count; iSeek++)
        {
            iMinLen = strnlen(strArrSource[iMin], STR_MAX_LENGTH - 1);
            iSeekLen = strnlen(strArrSource[iSeek], STR_MAX_LENGTH - 1);

            if (!isSorted[iSeek] && ((iMinLen - iSeekLen) > 0))
                iMin = iSeek;
        }

        isSorted[iMin] = true;

        /* 若iTop下标的元素正是刚刚被排序的元素，则将以下一个元素为开头，即iTop++，
         若下一个元素也是排序过的元素则继续iTop++，直到iTop指示的元素不为排序过的元素。
         下一次循环将以iTop下标的元素为开头 */
        while (isSorted[iTop])
            iTop++;

        strArrTarget[iTar] = strArrSource[iMin];
    }

    free(isSorted);
}

/* 比较源指针数组中各指针指向的字符串，
并将各指针按照指向的字符串中第一个单词的长度从短到长的顺序进行排序，
最后将排序后的指针列表存储到目标指针数组中 */
void sortStrListByFirstWordLength(char *strArrTarget[], char *strArrSource[], const int count)
{
    int iMin;     // 在字符串比较中的小值的下标，用作比较字符串
    int iTar;     // 目标数组的下标
    int iTop = 0; // 用于表示数组新一轮比较的开头位置
    int iSeek;    // 当前被比较的字符串的下标

    int iMinLen, iSeekLen;

    bool *isSorted;                                 // 分配用于检查数组中元素是否已被排序的布尔变量的空间
    isSorted = (bool *)calloc(count, sizeof(bool)); // 需要申请并归零
    if (NULL == isSorted)
    {
        puts("Memory allocation failed! At pointer \"isSorted\" in funcation \"sortStrListByFirstWordLength\".");
        exit(EXIT_FAILURE);
    }

    for (iTar = 0; iTar < count; iTar++)
    {
        for (iMin = iTop, iSeek = iTop + 1; iSeek < count; iSeek++)
        {
            iMinLen = getsnlenOfFirstWord(strArrSource[iMin], STR_MAX_LENGTH - 1);
            iSeekLen = getsnlenOfFirstWord(strArrSource[iSeek], STR_MAX_LENGTH - 1);

            if (!isSorted[iSeek] && ((iMinLen - iSeekLen) > 0))
                iMin = iSeek;
        }

        isSorted[iMin] = true;

        while (isSorted[iTop])
            iTop++;

        strArrTarget[iTar] = strArrSource[iMin];
    }

    free(isSorted);
}

/* 接受一个字符串数组，将用户输入的字符串依次存储到字符串数组的字符串中，最多输入10个字符串，返回输入完毕的字符串的数量；
如果在输入一个字符串的时候从输入中检测到EOF，则停止当前以及剩余的输入，返回输入完毕的字符串的数量（包括此字符串）。 */
int get10Strings(char (*strArr)[STR_MAX_LENGTH])
{
    int i_strNum = 0;

    while (i_strNum < STR_COUNT)
        if (NULL == s_gets(strArr[i_strNum++], STR_MAX_LENGTH))
        {
            fputs("Got a EOF.\n", stdout);
            break;
        }

    return i_strNum;
}

/* 接受一个char类型的指针数组、一个字符串数组和一个计数用途的整型变量，将字符串数组中每个字符串的首地址一一赋值到指针数组中，赋值数量不超过整型参数规定的数量 */
void cpyStringsAddr(char *pchArrTarget[], char (*strArrSource)[STR_MAX_LENGTH], const int count)
{
    int n = 0;

    while (n < count)
    {
        pchArrTarget[n] = (char *)&strArrSource[n];
        n++;
    }
}

/* 接受一个char类型的指针数组和一个计数用途的整型变量，将按顺序打印每个指针指向的字符串，打印的字符串数量不超过整型参数规定的数量 */
void printStrings(char *pchArr[], const int count)
{
    int n = 0;

    while (n < count)
        puts(pchArr[n++]);
}

/* 接受一个char类型的指针数组和一个计数用途的整型变量，按照源列表顺序打印源字符串列表 */
void printStrListSource(char *pchArr[], const int count)
{
    printStrings(pchArr, count);
}

/* 接受一个char类型的指针数组和一个计数用途的整型变量，以ASCII码数值从小到大的顺序打印源字符串列表 */
void printStrListByASCII(char *pchArr[], const int count)
{
    char **pchSorted;

    pchSorted = (char **)malloc(count * sizeof(char *));
    if (!pchSorted)
    {
        puts("Memory allocation failed! At pointer \"pchSorted\" in funcation \"printStrListByASCII\".");
        exit(EXIT_FAILURE);
    }

    sortStrListByASCII(pchSorted, pchArr, count);

    printStrings(pchSorted, count);

    free(pchSorted);
}

/* 接受一个char类型的指针数组和一个计数用途的整型变量，以字符串的长度从短到长的顺序打印源字符串列表 */
void printStrListByIncreasingLength(char *pchArr[], const int count)
{
    char **pchSorted;

    pchSorted = (char **)malloc(count * sizeof(char *));
    if (!pchSorted)
    {
        puts("Memory allocation failed! At pointer \"pchSorted\" in funcation \"printStrListByIncreasingLength\".");
        exit(EXIT_FAILURE);
    }

    sortStrListByIncreasingLength(pchSorted, pchArr, count);

    printStrings(pchSorted, count);

    free(pchSorted);
}

/* 接受一个char类型的指针数组和一个计数用途的整型变量，以字符串的第一个单词长度从短到长的顺序打印源字符串列表 */
void printStrListByFirstWordLength(char *pchArr[], const int count)
{
    char **pchSorted;

    pchSorted = (char **)malloc(count * sizeof(char *));
    if (!pchSorted)
    {
        puts("Memory allocation failed! At pointer \"pchSorted\" in funcation \"printStrListByFirstWordLength\".");
        exit(EXIT_FAILURE);
    }

    sortStrListByFirstWordLength(pchSorted, pchArr, count);

    printStrings(pchSorted, count);

    free(pchSorted);
}
