#include <stdio.h>

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
