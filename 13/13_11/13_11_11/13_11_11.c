/**
 * 11.编写一个程序，接受两个命令行参数。第1个参数是一个字符串，第2个参数是一个文件名。
 * 然后该程序查找该文件，打印文件中包含该字符串的所有行。
 * 因为该任务是面向行而不是面向字符的，所以要使用fgets()而不是getc()。
 * 使用标准C库函数strstr()（11.5.7节简要介绍过）在每一行中查找指定字符串。
 * 假设文件中的所有行都不超过255个字符。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH_MAX 255

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
        fputs("ERROR: The to find is too long.\n", stderr);
        exit(EXIT_FAILURE);
    }

    // 检查文件名长度（假定不包含其他路径名）
    // 文件名（包括空字符）最大长度为 FILENAME_MAX
    if (strnlen(argv[2], FILENAME_MAX) >= FILENAME_MAX)
    {
        fputs("ERROR: Filename too long.\n", stderr);
        exit(EXIT_FAILURE);
    }

    // 打印文件中包含该字符串的所有行

    return 0;
}
