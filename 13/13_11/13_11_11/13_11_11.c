/**
 * 11.编写一个程序，接受两个命令行参数。第1个参数是一个字符串，第2个参数是一个文件名。
 * 然后该程序查找该文件，打印文件中包含该字符串的所有行。
 * 因为该任务是面向行而不是面向字符的，所以要使用fgets()而不是getc()。
 * 使用标准C库函数strstr()（11.5.7节简要介绍过）在每一行中查找指定字符串。
 * 假设文件中的所有行都不超过255个字符。
 */
#ifndef __USE_XOPEN2K8
#define __USE_XOPEN2K8
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH_MAX 255
#define LINE_SIZE_MAX (LINE_LENGTH_MAX + 1)

int main(int argc, char const *argv[])
{
    // 检查命令行参数数量
    if (argc != 3)
    {
        if (argc < 3)
            fputs("ERROR: Too few arguments.\n", stderr);
        else
            fputs("ERROR: Too many arguments.\n", stderr);

        exit(EXIT_FAILURE);
    }

    // 检查字符串长度
    if (strnlen(argv[1], LINE_LENGTH_MAX) >= LINE_LENGTH_MAX)
    {
        fputs("ERROR: The string to find is too long.\n", stderr);
        exit(EXIT_FAILURE);
    }

    // 检查文件名长度（假定不包含其他路径名）
    // 文件名（包括空字符）最大长度为 FILENAME_MAX
    if (strnlen(argv[2], FILENAME_MAX) >= FILENAME_MAX)
    {
        fputs("ERROR: Filename too long.\n", stderr);
        exit(EXIT_FAILURE);
    }
    const char *str_find = argv[1];
    const char *filename = argv[2];

    FILE *fp;
    // 打开文件
    if ((fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line_temp[LINE_SIZE_MAX] = {}; // 临时字符串

    // 打印文件中包含该字符串的所有行
    // 首先获取一行读取到临时字符串中，然后检查临时字符串中是否找到要查找的字符串
    while (fgets(line_temp, LINE_SIZE_MAX, fp) != NULL)
        if (strstr(line_temp, str_find) != NULL)
            fputs(line_temp, stdout);

    if (ferror(fp))
    {
        fprintf(stderr, "ERROR: An error occurred while reading file: %s\n", filename);
        exit(EXIT_FAILURE);
    };

    return 0;
}
