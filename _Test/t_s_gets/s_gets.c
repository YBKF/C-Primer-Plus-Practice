#include <stdio.h>

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

    // (a ∧ b) ∨ (a ∧ c) == a ∧ (b ∨ c)
    // if (ferror(stream) || (feof(stream) && p == s))
    if (c == EOF && (p == s || ferror(stream)))
        return NULL;

    *p = '\0';

    return s;
}
