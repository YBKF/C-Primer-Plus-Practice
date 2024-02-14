#include <stdio.h>

void printCharAndASCII(char ch_input);

void setLFwhen(int i_input);

int main(void)
{
    int i_ch;
    int i_count;

    printf("Please input something:\n");

    for (i_count = 0;
         (i_ch = getchar()) != EOF;
         i_count++, setLFwhen(i_count))
    {
        printCharAndASCII(i_ch);
    }
    return 0;
}

/**
 * 打印输入的字符及ASCII码，非打印字符将以脱出字符表示法表示。
 */
void printCharAndASCII(char ch_input)
{
    if ((ch_input >= ' ') && (ch_input <= '~'))
    {
        printf("/%2c %4d/ ", ch_input, ch_input);
    }
    else if (ch_input <= 31)
    {

        printf("/^%c %4d/ ", ch_input + 64, ch_input);
    }
    else if (ch_input == 127)
    {
        printf("/^? 127 / ");
    }
    else
    {
        printf("Error");
    }
}

/**
 * 当参数与10的模为0时打印一个换行符
 */
void setLFwhen(int i_input)
{
    if (0 == i_input % 10)
    {
        putchar('\n');
    }
}
