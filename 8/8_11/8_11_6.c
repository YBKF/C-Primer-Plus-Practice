#include <stdio.h>
#include <ctype.h>

char get_first(void);

int main(int argc, char const *argv[])
{
    int i_ch;

    i_ch = get_first();
    printf("*%c* %d\n", i_ch, i_ch);

    return 0;
}

/**
 * 该函数返回读取的第1个非空白字符
 */
char get_first(void)
{
    char ch_buffer = 0;
    char ch_data = 0;

    // scanf(" %c", &ch);

    while (ch_buffer = getchar())
    {
        if (isalpha(ch_buffer))
        {
            ch_data = ch_buffer;
            break;
        }
    }
    // while (getchar() != '\n')
    //     continue;
    return ch_data;
}