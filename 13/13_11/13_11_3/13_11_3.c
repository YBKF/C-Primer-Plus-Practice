/**
 * 3.编写一个文件拷贝程序，提示用户输入文本文件名，并以该文件名作为原始文件名和输出文件名。
 * 该程序要使用 ctype.h 中的 toupper()函数，在写入到输出文件时把所有文本转换成大写。
 * 使用标准I/O和文本模式。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *s_gets(char *s, int n);

int main(int argc, char const *argv[])
{
    FILE *fp_src, *fp_out;
    char filename_src[FILENAME_MAX] = {};
    char filename_out[FILENAME_MAX] = {};
    int ch_temp;

    fputs("Enter name of source file:", stdout);
    s_gets(filename_src, FILENAME_MAX);

    if ((fp_src = fopen(filename_src, "r")) == NULL)
    {
        fprintf(stderr, "Cannot open file: %s\n", filename_src);
        exit(EXIT_FAILURE);
    }

    strncpy(filename_out, filename_src, FILENAME_MAX - 5);
    filename_out[FILENAME_MAX - 5];
    strcat(filename_out, ".cpy"); // 为输出文件添加后缀 .cpy

    if ((fp_out = fopen(filename_out, "w")) == NULL)
    {
        fprintf(stderr, "Cannot open or create file: %s\n", filename_out);
        exit(EXIT_FAILURE);
    }

    while ((ch_temp = getc(fp_src)) != EOF)
        putc(toupper(ch_temp), fp_out);

    fclose(fp_src);
    fclose(fp_out);

    printf("File \"%s\" has copied to \"%s\".\n", filename_src, filename_out);

    return 0;
}

/**
 * 从标准输入中读取字符，并将读取到的字符存入 s，
 * 直到读到新的一行或读取了 n-1 个字符又或是读取到文件结尾（EOF），
 * 功能类似于 gets() 但可以设置最大读取字符数。
 * 读取结束后，在字符串结尾添加一个空字符并返回 s 的地址，
 * 如果还未向 s 存入任何字符便读到文件结尾（EOF）则返回NULL且不向字符串结尾添加空字符。
 * 一旦在读取过程中出现错误就返回NULL。
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
