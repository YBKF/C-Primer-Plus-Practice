/*
16.编写一个程序读取输入，直至读到文件结尾，然后把字符串打印出来。
该程序识别和实现下面的命令行参数：
-p 按原样打印
-u 把输入全部转换成大写
-l 把输入全部转换成小写
如果没有命令行参数，则让程序像是使用了-p参数那样运行。
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_FILE_LENGTH (2147483647)
#define COM_FILE_LENGTH (65535)

// char *splitArg(const char *argv);

int checkingArg(const char *arg);
int getcTrans(const int option, FILE *file);
char *getsTrans(char *strSave, const int option, int maxCount, FILE *file);
// char *getsTrans_t(char *strSave, const int option, int maxCount, FILE *file);

int main(int argc, char const *argv[])
{
    char str[COM_FILE_LENGTH] = {};

    /* 无命令行参数时的默认选项，为兼容参数检查函数的-1返回值使用符号整型 */
    int option = 'p';

    /* 首先检测命令行参数数量是否小于等于1，即argc是否小于等于2，仅在命令行参数小于等于1时才继续执行 */
    if (argc > 2)
    {
        fputs("Only one parameter supported.\n", stderr);
        exit(EXIT_FAILURE);
    }

    /* 当存在一个命令行参数时，对此参数进行检查并进行处理 */
    if (argc == 2)
    {
        option = checkingArg(argv[1]);

        // 命令行参数不匹配格式时，输出错误信息并退出
        if (option == EOF)
        {
            fputs("ERROR: Cannot match this parameter.\n", stderr);
            exit(EXIT_FAILURE);
        }
    }

    fputs("Enter something:\n", stdout);

    /* 开始读取输入 */
    getsTrans(str, option, COM_FILE_LENGTH, stdin);
    fputs("\nOutput:\n", stdout);
    fputs(str, stdout);

    return 0;
}

/* 检查并处理命令行参数。
仅在字符串（命令行）参数arg匹配 '-' + '任意单个字符' 的格式时，返回'-'后的字符，在不匹配时返回EOF */
int checkingArg(const char *arg)
{
    if (*arg == '-' && arg[2] == '\0')
        return arg[1];
    else
        return EOF;
}

/* 从文件中（通常是键盘）读取一个字符，根据参数选项对输入进行转换并返回转换后的字符。
若参数选项无法识别则报错并返回EOF。
允许的参数选项：
p 按原样打印
u 把输入全部转换成大写
l 把输入全部转换成小写 */
int getcTrans(const int option, FILE *file)
{
    int retVal = getc(file);

    if (option == 'p')
        /* Do nothing. */;
    else if (option == 'u')
        retVal = toupper(retVal);
    else if (option == 'l')
        retVal = tolower(retVal);
    else
    {
        fputs("Cannot match this parameter.\n", stderr);
        return EOF;
    }

    return retVal;
}

/* 从文件中（通常是键盘）读取输入，根据参数选项对输入进行转换并将转换后的字符存储进字符串中，直至文件结尾。
返回值为第一个参数，若参数选项无法识别则报错并返回NULL空指针。
允许的参数选项：
p 按原样打印
u 把输入全部转换成大写
l 把输入全部转换成小写 */
char *getsTrans(char *strSave, const int option, int maxCount, FILE *file)
{
    char *pcSeek = strSave;

    if (strSave == NULL || maxCount <= 0)
        return NULL;

    int retVal_getc;

    if (option == 'p')
    {
        while ((--maxCount > 0) && (retVal_getc = getc(file)) != EOF)
            *pcSeek++ = retVal_getc;
    }
    else if (option == 'u')
    {
        while ((--maxCount > 0) && (retVal_getc = getc(file)) != EOF)
            *pcSeek++ = toupper(retVal_getc);
    }
    else if (option == 'l')
    {
        while ((--maxCount > 0) && (retVal_getc = getc(file)) != EOF)
            *pcSeek++ = tolower(retVal_getc);
    }
    else
    {
        fputs("Cannot match this parameter.\n", stderr);
        return NULL;
    }

    if (maxCount == 0)
        while (getchar() != '\n')
            continue;

    // 在字符串结尾处添加'\0'
    *pcSeek = '\0';

    return strSave;
}

/* 从文件中（通常是键盘）读取输入，根据参数选项对输入进行转换并将转换后的字符存储进字符串中，直至文件结尾。
返回值为第一个参数，若参数选项无法识别则报错并返回NULL空指针。
允许的参数选项：
p 按原样打印
u 把输入全部转换成大写
l 把输入全部转换成小写 */
// char *getsTrans_t(char *strSave, const int option, int maxCount, FILE *file)
// {
//     if (strSave == NULL || maxCount <= 0)
//         return NULL;

//     int retVal_getc;
//     int num = 0;

//     // 结束输入后须在结尾处添加'\0'，所以 maxCount - 1 为'\0'留一个字符的位置
//     if (option == 'p')
//         while ((num < maxCount - 1) && (retVal_getc = getc(file)) != EOF)
//         {
//             strSave[num] = retVal_getc;
//             num++;
//         }
//     else if (option == 'u')
//         while ((num < maxCount - 1) && (retVal_getc = getc(file)) != EOF)
//         {
//             strSave[num] = toupper(retVal_getc);
//             num++;
//         }
//     else if (option == 'l')
//         while ((num < maxCount - 1) && (retVal_getc = getc(file)) != EOF)
//         {
//             strSave[num] = tolower(retVal_getc);
//             num++;
//         }
//     else
//     {
//         fputs("Cannot match this parameter.\n", stderr);
//         return NULL;
//     }

//     if (num + 1 == maxCount)
//         while (getc(file) != '\n')
//             continue;

//     // 在字符串结尾处添加'\0'
//     strSave[num] = '\0';

//     return strSave;
// }

/* 返回'-'（连接号）后的字符地址。
字符串开头只有一个连接号，则返回此连接号向后一个字符的地址，
若字符串开头有两个或两个以上连续的连接号，则返回开头第二个连接号向后一个字符的地址。 */
// char *splitArg(const char *arg)
// {
//     char *addrResult = arg;

//     if (*arg == '-')
//     {
//         if (*(arg + 1) == '-')
//             addrResult = (arg + 2);
//         else
//             addrResult = (arg + 1);
//     }
//     else
//     {
//         fputs("Cannot found a parameter matched.\n", stderr);
//         exit(EXIT_FAILURE);
//     }

//     return addrResult;
// }