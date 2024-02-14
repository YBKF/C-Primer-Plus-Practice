#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i_outer, i_inner;
    char ch_ch;
    for (i_outer = 0, ch_ch = 'A'; i_outer < 6; i_outer++)
    {
        for (i_inner = 0; i_inner <= i_outer; i_inner++, ch_ch++)
        {
            printf("%c", ch_ch);
        }
        printf("\n");
    }

    return 0;
}
