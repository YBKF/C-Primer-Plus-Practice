#include <stdio.h>

char *str_reverse(char *str);
char *strrev(char *s);

int main(int argc, char const *argv[])
{

    char s[] = "Thisastring.";

    str_reverse(s);

    printf("*%s*", s);
    return 0;
}

char *str_reverse(char *str)
{
    /* h指向s的头部 */
    char *h = str;
    char *t = str;
    char ch;

    /* t指向s的尾部 */
    while (*(t + 1))
        t++;

    /* 当h和t未重合时，交换它们所指向的字符 */
    while (h < t)
    {
        ch = *h;
        *h++ = *t; /* h向尾部移动 */
        *t-- = ch; /* t向头部移动 */
    }

    return str;
}

// 原参考函数
char *strrev(char *s)
{
    /* h指向s的头部 */
    char *h = s;
    char *t = s;
    char ch;

    /* t指向s的尾部 */
    while (*t++)
    {
    };
    t--; // 如果可以不赋值，则尽量减少不必要的赋值，条件判断的效率更高 /* 与t++抵消 */
    t--; // 如果可以不赋值，则尽量减少不必要的赋值，条件判断的效率更高 /* 回跳过结束符'\0' */

    /* 当h和t未重合时，交换它们所指向的字符 */
    while (h < t)
    {
        ch = *h;
        *h++ = *t; /* h向尾部移动 */
        *t-- = ch; /* t向头部移动 */
    }

    return (s);
}
