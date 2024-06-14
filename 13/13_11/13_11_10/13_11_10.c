/**
 * 10.编写一个程序打开一个文本文件，通过交互方式获得文件名。
 * 通过一个循环，提示用户输入一个文件位置。
 * 然后该程序打印从该位置开始到下一个换行符之前的内容。
 * 用户输入负数或非数值字符可以结束输入循环。
 */
#include <stdio.h>
#include <stdlib.h>

char *s_gets(char *s, int n);

int main()
{
    char filename[FILENAME_MAX] = {};

    fputs("Enter name of source file:\n", stdout);
    if (s_gets(filename, FILENAME_MAX) == NULL)
    {
        fputs("ERROR: Failed to get filename.\n", stderr);
        exit(EXIT_FAILURE);
    }

    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: Cannot open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    long file_pos;
    char temp;
    size_t num_printed = 0ULL; // 存储当次循环打印了多少字符，主要用于辅助检测fseek()定位是否超出文件范围

    int ret;

    fputs("Enter a position of the file(negative or non-numeric to exit): ", stderr);
    while (scanf("%ld", &file_pos) == 1 && file_pos >= 0)
    {

        // 定位向左超越文件头时 fseek() 的返回值才不为 0
        if (fseek(fp, file_pos, SEEK_SET) != 0)
        {
            fputs("ERROR: This position is out of the file scope.\n", stderr);
            exit(EXIT_FAILURE);
        }

        num_printed = 0ULL;

        while ((temp = getc(fp)) != EOF && temp != '\n')
        {
            putc(temp, stdout);
            num_printed++;
        }
        if (temp == '\n')
            putc('\n', stdout);

        if (num_printed == 0ULL && file_pos > 0)
            fputs("WARN: This position might be out of the file scope.\n", stderr);

        // while ((temp = getc(fp)) != EOF)
        // {
        //     putc(temp, stdout);
        //     if (temp == '\n')
        //         break;
        // }

        rewind(fp);
        fputs("Enter a position of the file(negative or non-numeric to exit): ", stderr);
    }

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Error in closing file: %s\n", filename);
        return EXIT_FAILURE;
    }

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

    if (c == EOF && (p == s || ferror(stdin)))
        return NULL;

    *p = '\0';

    return s;
}
