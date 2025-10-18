/**
 * 10.编写一个程序，通过一个函数指针数组实现菜单。
 * 例如，选择菜单中的 a，将激活由该数组第 1 个元素指向的函数。
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STR_SENTENCE_LENGTH_MAX (15)
#define STR_SENTENCE_SIZE_MAX (STR_SENTENCE_LENGTH_MAX + 1)

#define FP_COUNT (4)

#define CHAR_START ('a')
#define CHAR_END (CHAR_START + FP_COUNT - 1)

typedef void (*FP_VOID_VOID)();

char *s_gets(char *str, int n);
void printErrorInfo(const char *errInfo);

char toLowerCase(char chSource);

char *chConvertToLowerCase(char *chSource);
char *strToLowerCase(const char *strSource, char *strTarget);
int isOnlyOneCharInString(const char *strSource);
int checkInputOption(const char *strOption);

void printMenu();

void functionA();
void functionB();
void functionC();
void functionD();

int main()
{
    FP_VOID_VOID fpArr[FP_COUNT] = {functionA, functionB, functionC, functionD};

    while (1)
    {
        printMenu();

        char strOption[STR_SENTENCE_SIZE_MAX];
        char *pchRetVal = s_gets(strOption, STR_SENTENCE_SIZE_MAX);
        if (pchRetVal == NULL)
            break;

        char chOption = checkInputOption(strOption);

        if (chOption == EOF)
        {
            fprintf(stderr, "\
[ERROR]     Invalid input option.\n");
            continue;
        }

        if (chOption == 'q')
            break;

        fpArr[chOption - CHAR_START]();
    }

    return 0;
}

char *s_gets(char *str, int n)
{
    char *ret_val;

    if (!(ret_val = fgets(str, n, stdin)))
        return ret_val;

    char *find;

    if (find = strchr(str, '\n'))
        *find = '\0';
    else
        while (getchar() != '\n')
            continue;

    return ret_val;
}

void printErrorInfo(const char *errInfo)
{
    if (NULL == errInfo)
    {
        fprintf(stderr, "\
[ERROR] No more infomation.\n");
        return;
    }

    fprintf(stderr, "\
[ERROR] %s\n",
            errInfo);
}

char toLowerCase(char chSource)
{
    if (!isalpha(chSource) || islower(chSource))
    {
        return chSource;
    }

    return tolower(chSource);
}

char *chConvertToLowerCase(char *chSource)
{
    if (NULL == chSource)
    {
        printErrorInfo("Param is null pointer.");
        return NULL;
    }

    *chSource = toLowerCase(*chSource);

    return chSource;
}

// TODO 更保险一些的设计，此函数应添加 strSource 字符串的长度及 strTarget 数组的大小为参数，函数中根据两个参数之间的逻辑关系执行不同策略，
//      若 strSource 字符串长度大于 strTarget 数组大小 - 1，应最多复制 strTarget 大小 - 1 个数的字符，并在 strTarget 最后加入 '\0'，
//      若 strSource 字符串长度小于或等于 strTarget 数组大小 - 1，应复制 strSource 长度个数的字符，并在复制完的最后一个字符的位置的下一个位置添加 '\0'。
char *strToLowerCase(const char *strSource, char *strTarget)
{
    if (NULL == strSource || NULL == strTarget)
    {
        printErrorInfo("Param is null pointer.");
        return NULL;
    }

    char *strTargetBase = strTarget;

    while (*strSource != '\0')
    {
        *strTarget++ = tolower(*strSource++);
    }

    return strTargetBase;
}

int isOnlyOneCharInString(const char *strSource)
{
    if (NULL == strSource)
    {
        printErrorInfo("Param is null pointer.");
        return 0;
    }

    if (*strSource == '\0')
    {
        return 0;
    }

    if (*(strSource + 1) != '\0')
    {
        return 0;
    }

    return (*strSource);
}

int checkInputOption(const char *strOption)
{
    if (NULL == strOption)
    {
        printErrorInfo("Param is null pointer.");
        return EOF;
    }

    int chOption = isOnlyOneCharInString(strOption);
    if (chOption == '\0')
    {
        return EOF;
    }

    chOption = toLowerCase(chOption);
    if (strchr("abcdq", chOption) == 0)
    {
        return EOF;
    }

    return chOption;
}

void printMenu()
{
    fprintf(stdout, "\
Enter a letter to choose a function to active:\n\
    a) functionA\n\
    b) functionB\n\
    c) functionC\n\
    d) functionD\n\
    q) quit\n");
}

void functionA()
{
    fprintf(stdout, "\
functionA() invoked.\n");
}

void functionB()
{
    fprintf(stdout, "\
functionB() invoked.\n");
}

void functionC()
{
    fprintf(stdout, "\
functionC() invoked.\n");
}

void functionD()
{
    fprintf(stdout, "\
functionD() invoked.\n");
}
