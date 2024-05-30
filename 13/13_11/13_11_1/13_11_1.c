/**
 * 1.修改程序清单13.1中的程序，要求提示用户输入文件名，
 * 并读取用户输入的信息，不使用命令行参数。
 */

#include <stdio.h>
#include <stdlib.h> // 提供 exit()的原型

char *s_gets(char *s, int n);

int main(int argc, char *argv[])
{
    int ch; // 读取文件时，储存每个字符的地方
    char file_name[FILENAME_MAX] = {};
    FILE *fp; // “文件指针”
    unsigned long count = 0;

    fputs("Enter name of file: ", stdout);

    s_gets(file_name, FILENAME_MAX);

    if ((fp = fopen(file_name, "r")) == NULL)
    {
        printf("Can't open %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(fp)) != EOF)
    {
        putc(ch, stdout); // 与 putchar(ch); 相同
        count++;
    }

    fclose(fp);
    printf("File %s has %lu characters\n", file_name, count);
    return 0;
}

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
