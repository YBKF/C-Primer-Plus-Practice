/**
 * 8.编写一个名为string_in()的函数，接受两个指向字符串的指针作为参数。如果第2个字符串中包含第1个字符串，该函数将返回第1个字符串开始的地址。
 * 例如，string_in("hats", "at")将返回hats中a的地址。否则，该函数返回空指针。在一个完整的程序中测试该函数，使用一个循环给函数提供输入值。
 */
#include <stdio.h>
#include <stdbool.h>

char *string_in(char *str_source, char *str_isin);
char *s_gets(char *str, int maxCount);
bool printHead();

int main(int argc, char const *argv[])
{
    // printf("1 %s\n", string_in("zeus", "eh"));
    // printf("2 %s\n", string_in("zeus", "eu"));
    // printf("3 %s\n", string_in("zeu", "eu"));
    // printf("4 %s\n", string_in("uze", "eu"));
    // printf("5 %s\n", string_in("", ""));
    // printf("6 %s\n", string_in("abc", ""));
    // printf("7 %s\n", string_in("", "abc"));

    char str_source[20] = "";
    char str_isin[20] = "";
    char *ret_val = NULL;

    while (printHead() && s_gets(str_source, 20) && str_source[0] != EOF)
    {
        puts("Please enter what do you want to find:");
        s_gets(str_isin, 20);
        ret_val = string_in(str_source, str_isin);
        printf("finded: %s\n", ret_val);
    }

    return 0;
}

char *string_in(char *str_source, char *str_isin)
{
    char *pc_source = str_source;
    char *pc_isin = str_isin;
    char *pc_finded = NULL;

    if (*str_source != '\0' && *str_isin != '\0')
    {
        // 首先匹配第一个字母，如果匹配成功或匹配到source字符串结尾则结束循环
        while (*pc_source != *pc_isin && *pc_source != '\0')
            pc_source++;

        // 第一个字符匹配成功时，暂存souce字符串的首字符地址
        if (*pc_source == *pc_isin)
        {
            pc_finded = pc_source;

            // 匹配后续字母，直到匹配到isin字符串结尾，途中出现不匹配时则退出循环
            while (*pc_source == *pc_isin && *pc_isin != '\0')
            {
                pc_source++;
                pc_isin++;
            }

            // 如指向空字符则说明isin已成功匹配到结尾
            if (*pc_isin == '\0')
                return pc_finded;
        }
    }

    return NULL;
}

char *s_gets(char *str, int maxCount)
{
    char *ret_val;
    int i = 0;

    ret_val = fgets(str, maxCount, stdin);

    if (ret_val)
    {
        while (str[i] != '\0' && str[i] != '\n')
            i++;

        if (str[i] == '\n')
            str[i] = '\0';
        else
            while (getchar() == '\n')
                continue;
    }

    return ret_val;
}

bool printHead()
{
    puts("Please enter source string (Enter ^Z to exit):");
    return true;
}
