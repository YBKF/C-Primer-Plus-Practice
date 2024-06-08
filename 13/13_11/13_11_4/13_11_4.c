/**
 * 4.编写一个程序，按顺序在屏幕上显示命令行中列出的所有文件。使用argc控制循环。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *print_file_text(FILE *fp, const char *filename);

int main(int argc, const char *argv[])
{
    // 检查参数数量
    if (argc < 2)
    {
        fputs("Too few arguments.\n", stderr);
        exit(EXIT_FAILURE);
    }

    // 检查所有文件的名称（包括长度）
    for (int i = 1; i < argc; i++)
    {
        if (argv[i] == NULL || strnlen(argv[i], FILENAME_MAX) >= FILENAME_MAX) // 检测文件名
        {
            fputs("ERROR: Invalid filename found.\n", stderr);
            exit(EXIT_FAILURE);
        }
    }

    FILE *fp_cur;
    FILE *fp_ret;

    for (int i = 1; i < argc; i++)
    {
        if ((fp_cur = fopen(argv[i], "r")) == NULL)
        {
            fprintf(stderr, "ERROR: Cannot open file %s.\n", argv[i]);
            exit(EXIT_FAILURE);
        }

        if ((fp_ret = print_file_text(fp_cur, argv[i])) == NULL)
            exit(EXIT_FAILURE);

        fclose(fp_ret);
    }

    return 0;
}

FILE *print_file_text(FILE *fp, const char *filename)
{

    if (filename == NULL || strnlen(filename, FILENAME_MAX) > (FILENAME_MAX - 1)) // 检测文件名
    {
        fputs("ERROR: Invalid filename.\n", stderr);
        return NULL;
    }
    else if (fp == NULL) // 检测文件指针
    {
        fprintf(stderr, "ERROR: Cannot open file %s.\n", filename);
        return NULL;
    }

    fprintf(stdout, "\n%s:\n", filename);

    int ch_temp;

    while ((ch_temp = getc(fp)) != EOF)
        putc(ch_temp, stdout);

    return fp;
}
