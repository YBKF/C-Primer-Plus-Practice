#include <stdio.h>

char *s_fgets(char *str, int maxCount)
{
    char *ret_val;
    int len = 0;

    ret_val = fgets(str, maxCount, stdin);

    if (ret_val)
    {
        len = (int)strlen(str) - 1;

        // 能检查到换行符则说明输入未超过字数限制
        if (str[len] == '\n')
            str[len] = '\0';
        else
            while (getchar() != '\n')
                continue;
    }

    return ret_val;
}
